#include "ds/ds_list.h"
#include <stdlib.h>
#include <string.h>

struct ds_list_node {
    struct ds_list_node *next;
    struct ds_list_node *prev;
    char data[];
};

struct ds_list {
    ds_list_node_t *head;
    ds_list_node_t *tail;
    size_t size;
    size_t element_size;

    void (*destructor)(void *);
    ds_malloc_fn allocator;
    ds_free_fn deallocator;
};

ds_list_t *ds_list_create(
    size_t element_size,
    void (*destructor)(void *),
    ds_malloc_fn malloc_fn,
    ds_free_fn free_fn)
{
    if (element_size == 0) return NULL;

    ds_malloc_fn alloc = malloc_fn ? malloc_fn : malloc;
    ds_free_fn dealloc = free_fn ? free_fn : free;

    ds_list_t *l = (ds_list_t *)alloc(sizeof(ds_list_t));
    if (!l) return NULL;

    l->head = NULL;
    l->tail = NULL;
    l->size = 0;
    l->element_size = element_size;
    l->destructor = destructor;
    l->allocator = alloc;
    l->deallocator = dealloc;

    return l;
}

void ds_list_destroy(ds_list_t *l) {
    if (!l) return;
    ds_list_clear(l);
    l->deallocator(l);
}

static ds_list_node_t *ds_list_create_node(ds_list_t *l, const void *value) {
    ds_list_node_t *node = (ds_list_node_t *)l->allocator(sizeof(ds_list_node_t) + l->element_size);
    if (!node) return NULL;

    node->next = NULL;
    node->prev = NULL;
    memcpy(node->data, value, l->element_size);
    return node;
}

ds_error_t ds_list_push_front(ds_list_t *l, const void *value) {
    if (!l || !value) return DS_ERR_INVALID_ARG;

    ds_list_node_t *node = ds_list_create_node(l, value);
    if (!node) return DS_ERR_ALLOC;

    if (l->head) {
        node->next = l->head;
        l->head->prev = node;
        l->head = node;
    } else {
        l->head = node;
        l->tail = node;
    }

    l->size++;
    return DS_SUCCESS;
}

ds_error_t ds_list_push_back(ds_list_t *l, const void *value) {
    if (!l || !value) return DS_ERR_INVALID_ARG;

    ds_list_node_t *node = ds_list_create_node(l, value);
    if (!node) return DS_ERR_ALLOC;

    if (l->tail) {
        node->prev = l->tail;
        l->tail->next = node;
        l->tail = node;
    } else {
        l->head = node;
        l->tail = node;
    }

    l->size++;
    return DS_SUCCESS;
}

ds_error_t ds_list_pop_front(ds_list_t *l, void *out_value) {
    if (!l) return DS_ERR_INVALID_ARG;
    if (l->size == 0) return DS_ERR_EMPTY;

    ds_list_node_t *node = l->head;
    
    if (out_value) {
        memcpy(out_value, node->data, l->element_size);
    } else if (l->destructor) {
        l->destructor(node->data);
    }

    l->head = node->next;
    if (l->head) {
        l->head->prev = NULL;
    } else {
        l->tail = NULL;
    }

    l->deallocator(node);
    l->size--;
    return DS_SUCCESS;
}

ds_error_t ds_list_pop_back(ds_list_t *l, void *out_value) {
    if (!l) return DS_ERR_INVALID_ARG;
    if (l->size == 0) return DS_ERR_EMPTY;

    ds_list_node_t *node = l->tail;
    
    if (out_value) {
        memcpy(out_value, node->data, l->element_size);
    } else if (l->destructor) {
        l->destructor(node->data);
    }

    l->tail = node->prev;
    if (l->tail) {
        l->tail->next = NULL;
    } else {
        l->head = NULL;
    }

    l->deallocator(node);
    l->size--;
    return DS_SUCCESS;
}

ds_list_node_t *ds_list_begin(const ds_list_t *l) {
    return l ? l->head : NULL;
}

ds_list_node_t *ds_list_end(const ds_list_t *l) {
    return l ? l->tail : NULL;
}

ds_list_node_t *ds_list_next(const ds_list_node_t *node) {
    return node ? node->next : NULL;
}

ds_list_node_t *ds_list_prev(const ds_list_node_t *node) {
    return node ? node->prev : NULL;
}

void *ds_list_node_data(ds_list_node_t *node) {
    return node ? node->data : NULL;
}

ds_error_t ds_list_insert_after(ds_list_t *l, ds_list_node_t *node, const void *value) {
    if (!l || !value) return DS_ERR_INVALID_ARG;
    if (!node) return ds_list_push_front(l, value);

    ds_list_node_t *new_node = ds_list_create_node(l, value);
    if (!new_node) return DS_ERR_ALLOC;

    new_node->next = node->next;
    new_node->prev = node;
    
    if (node->next) {
        node->next->prev = new_node;
    } else {
        l->tail = new_node;
    }
    node->next = new_node;

    l->size++;
    return DS_SUCCESS;
}

ds_error_t ds_list_remove(ds_list_t *l, ds_list_node_t *node, void *out_value) {
    if (!l || !node) return DS_ERR_INVALID_ARG;

    if (out_value) {
        memcpy(out_value, node->data, l->element_size);
    } else if (l->destructor) {
        l->destructor(node->data);
    }

    if (node->prev) {
        node->prev->next = node->next;
    } else {
        l->head = node->next;
    }

    if (node->next) {
        node->next->prev = node->prev;
    } else {
        l->tail = node->prev;
    }

    l->deallocator(node);
    l->size--;
    return DS_SUCCESS;
}

size_t ds_list_size(const ds_list_t *l) {
    return l ? l->size : 0;
}

bool ds_list_is_empty(const ds_list_t *l) {
    return l ? l->size == 0 : true;
}

void ds_list_clear(ds_list_t *l) {
    if (!l) return;
    ds_list_node_t *curr = l->head;
    while (curr) {
        ds_list_node_t *next = curr->next;
        if (l->destructor) {
            l->destructor(curr->data);
        }
        l->deallocator(curr);
        curr = next;
    }
    l->head = NULL;
    l->tail = NULL;
    l->size = 0;
}
