#include "avltree.h"

int AVLTree::height(AVLNode* n) 
{ 
    return n ? n->height : 0; 
}
int AVLTree::balance(AVLNode* n) 
{ 
    return n ? height(n->left) - height(n->right) : 0; 
}

AVLNode* AVLTree::rotateLeft(AVLNode* x) 
{
    AVLNode* y = x->right;
    x->right = y->left;
    y->left = x;

    x->height = std::max(height(x->left), height(x->right)) + 1;
    y->height = std::max(height(y->left), height(y->right)) + 1;
    return y;
}

AVLNode* AVLTree::rotateRight(AVLNode* y) 
{
    AVLNode* x = y->left;
    y->left = x->right;
    x->right = y;

    y->height = std::max(height(y->left), height(y->right)) + 1;
    x->height = std::max(height(x->left), height(x->right)) + 1;
    return x;
}

AVLNode* AVLTree::insert(AVLNode* node, int key, int value) 
{
    if (!node) return new AVLNode(key, value);

    if (key < node->key) node->left = insert(node->left, key, value);
    else if (key > node->key) node->right = insert(node->right, key, value);
    else node->value = value;

    node->height = 1 + std::max(height(node->left), height(node->right));
    int b = balance(node);

    if (b > 1 && key < node->left->key) return rotateRight(node);
    if (b < -1 && key > node->right->key) return rotateLeft(node);
    if (b > 1 && key > node->left->key) { node->left = rotateLeft(node->left); return rotateRight(node); }
    if (b < -1 && key < node->right->key) { node->right = rotateRight(node->right); return rotateLeft(node); }

    return node;
}

AVLNode* AVLTree::findMin(AVLNode* node) 
{
    return node->left ? findMin(node->left) : node;
}

AVLNode* AVLTree::remove(AVLNode* node, int key) 
{
    if (!node) return nullptr;

    if (key < node->key) node->left = remove(node->left, key);
    else if (key > node->key) node->right = remove(node->right, key);
    else 
    {
        if (!node->left || !node->right) 
        {
            AVLNode* temp = node->left ? node->left : node->right;
            delete node;
            return temp;
        }
        AVLNode* temp = findMin(node->right);
        node->key = temp->key;
        node->value = temp->value;
        node->right = remove(node->right, temp->key);
    }

    node->height = 1 + std::max(height(node->left), height(node->right));
    int b = balance(node);

    if (b > 1 && balance(node->left) >= 0) return rotateRight(node);
    if (b > 1 && balance(node->left) < 0) { node->left = rotateLeft(node->left); return rotateRight(node); }
    if (b < -1 && balance(node->right) <= 0) return rotateLeft(node);
    if (b < -1 && balance(node->right) > 0) { node->right = rotateRight(node->right); return rotateLeft(node); }

    return node;
}
