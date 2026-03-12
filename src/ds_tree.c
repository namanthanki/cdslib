#include "ds/ds_tree.h"
#include <stdlib.h>
#include <string.h>

struct ds_tree_node {
    struct ds_tree_node *left;
    struct ds_tree_node *right;
    char data[];
};

struct ds_tree {
    ds_tree_node_t *root;
    size_t size;
    size_t element_size;

    ds_cmp_fn cmp_fn;
    void (*destructor)(void *);
    ds_malloc_fn allocator;
    ds_free_fn deallocator;
};

ds_tree_t *ds_tree_create(
    size_t element_size,
    ds_cmp_fn cmp_fn,
    void (*destructor)(void *),
    ds_malloc_fn malloc_fn,
    ds_free_fn free_fn)
{
    if (element_size == 0 || !cmp_fn) return NULL;

    ds_malloc_fn alloc = malloc_fn ? malloc_fn : malloc;
    ds_free_fn dealloc = free_fn ? free_fn : free;

    ds_tree_t *tree = (ds_tree_t *)alloc(sizeof(ds_tree_t));
    if (!tree) return NULL;

    tree->root = NULL;
    tree->size = 0;
    tree->element_size = element_size;
    tree->cmp_fn = cmp_fn;
    tree->destructor = destructor;
    tree->allocator = alloc;
    tree->deallocator = dealloc;

    return tree;
}

static void ds_tree_destroy_node(ds_tree_t *tree, ds_tree_node_t *node) {
    if (!node) return;
    ds_tree_destroy_node(tree, node->left);
    ds_tree_destroy_node(tree, node->right);
    if (tree->destructor) {
        tree->destructor(node->data);
    }
    tree->deallocator(node);
}

void ds_tree_destroy(ds_tree_t *tree) {
    if (!tree) return;
    ds_tree_destroy_node(tree, tree->root);
    tree->deallocator(tree);
}

static ds_tree_node_t *ds_tree_create_node(ds_tree_t *tree, const void *value) {
    ds_tree_node_t *node = (ds_tree_node_t *)tree->allocator(sizeof(ds_tree_node_t) + tree->element_size);
    if (!node) return NULL;

    node->left = NULL;
    node->right = NULL;
    memcpy(node->data, value, tree->element_size);
    return node;
}

ds_error_t ds_tree_insert(ds_tree_t *tree, const void *value) {
    if (!tree || !value) return DS_ERR_INVALID_ARG;

    ds_tree_node_t **curr = &tree->root;
    while (*curr) {
        int cmp = tree->cmp_fn(value, (*curr)->data);
        if (cmp < 0) {
            curr = &(*curr)->left;
        } else if (cmp > 0) {
            curr = &(*curr)->right;
        } else {
            return DS_SUCCESS; // Already exists
        }
    }

    *curr = ds_tree_create_node(tree, value);
    if (!*curr) return DS_ERR_ALLOC;

    tree->size++;
    return DS_SUCCESS;
}

static ds_tree_node_t *ds_tree_min_node(ds_tree_node_t *node) {
    ds_tree_node_t *curr = node;
    while (curr && curr->left) {
        curr = curr->left;
    }
    return curr;
}

static ds_tree_node_t *ds_tree_remove_node(ds_tree_t *tree, ds_tree_node_t *root, const void *value, void *out_value, ds_error_t *err) {
    if (!root) {
        *err = DS_ERR_OUT_OF_RANGE;
        return NULL;
    }

    int cmp = tree->cmp_fn(value, root->data);
    if (cmp < 0) {
        root->left = ds_tree_remove_node(tree, root->left, value, out_value, err);
    } else if (cmp > 0) {
        root->right = ds_tree_remove_node(tree, root->right, value, out_value, err);
    } else {
        *err = DS_SUCCESS;
        if (out_value) {
            memcpy(out_value, root->data, tree->element_size);
        } else if (tree->destructor) {
            tree->destructor(root->data);
        }

        if (!root->left) {
            ds_tree_node_t *temp = root->right;
            tree->deallocator(root);
            return temp;
        } else if (!root->right) {
            ds_tree_node_t *temp = root->left;
            tree->deallocator(root);
            return temp;
        }

        ds_tree_node_t *temp = ds_tree_min_node(root->right);
        memcpy(root->data, temp->data, tree->element_size);
        root->right = ds_tree_remove_node(tree, root->right, temp->data, NULL, err);
    }
    return root;
}

ds_error_t ds_tree_remove(ds_tree_t *tree, const void *value, void *out_value) {
    if (!tree || !value) return DS_ERR_INVALID_ARG;

    ds_error_t err = DS_ERR_OUT_OF_RANGE;
    tree->root = ds_tree_remove_node(tree, tree->root, value, out_value, &err);
    if (err == DS_SUCCESS) {
        tree->size--;
    }
    return err;
}

ds_error_t ds_tree_find(const ds_tree_t *tree, const void *value, void *out_value) {
    if (!tree || !value || !out_value) return DS_ERR_INVALID_ARG;

    ds_tree_node_t *curr = tree->root;
    while (curr) {
        int cmp = tree->cmp_fn(value, curr->data);
        if (cmp < 0) {
            curr = curr->left;
        } else if (cmp > 0) {
            curr = curr->right;
        } else {
            memcpy(out_value, curr->data, tree->element_size);
            return DS_SUCCESS;
        }
    }

    return DS_ERR_OUT_OF_RANGE;
}

static void ds_tree_inorder_impl(ds_tree_node_t *node, void (*callback)(const void *)) {
    if (!node) return;
    ds_tree_inorder_impl(node->left, callback);
    callback(node->data);
    ds_tree_inorder_impl(node->right, callback);
}

void ds_tree_inorder(const ds_tree_t *tree, void (*callback)(const void *)) {
    if (!tree || !callback) return;
    ds_tree_inorder_impl(tree->root, callback);
}

static void ds_tree_preorder_impl(ds_tree_node_t *node, void (*callback)(const void *)) {
    if (!node) return;
    callback(node->data);
    ds_tree_preorder_impl(node->left, callback);
    ds_tree_preorder_impl(node->right, callback);
}

void ds_tree_preorder(const ds_tree_t *tree, void (*callback)(const void *)) {
    if (!tree || !callback) return;
    ds_tree_preorder_impl(tree->root, callback);
}

static void ds_tree_postorder_impl(ds_tree_node_t *node, void (*callback)(const void *)) {
    if (!node) return;
    ds_tree_postorder_impl(node->left, callback);
    ds_tree_postorder_impl(node->right, callback);
    callback(node->data);
}

void ds_tree_postorder(const ds_tree_t *tree, void (*callback)(const void *)) {
    if (!tree || !callback) return;
    ds_tree_postorder_impl(tree->root, callback);
}

size_t ds_tree_size(const ds_tree_t *tree) {
    return tree ? tree->size : 0;
}

bool ds_tree_is_empty(const ds_tree_t *tree) {
    return tree ? tree->size == 0 : true;
}

void ds_tree_clear(ds_tree_t *tree) {
    if (!tree) return;
    ds_tree_destroy_node(tree, tree->root);
    tree->root = NULL;
    tree->size = 0;
}
