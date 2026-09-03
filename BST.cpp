#ifndef __BST_HPP__
#define __BST_HPP__

#include <iostream>

template <typename T>
struct BSTNode
{
    T data;
    BSTNode* left;
    BSTNode* right;
    BSTNode(const T& val) : data(val), left(nullptr), right(nullptr) {}
};

template <typename T>
BSTNode<T>* insertBST(BSTNode<T>* root, const T& val)
{
    if (!root) return new BSTNode<T>(val);
    if (val < root->data)
        root->left = insertBST(root->left, val);
    else if (val > root->data)
        root->right = insertBST(root->right, val);
    return root;
}

template <typename T>
void inorder(BSTNode<T>* root)
{
    if (!root) return;
    inorder(root->left);
    std::cout << root->data << " ";
    inorder(root->right);
}

template <typename T>
void preorder(BSTNode<T>* root)
{
    if (!root) return;
    std::cout << root->data << " ";
    preorder(root->left);
    preorder(root->right);
}

template <typename T>
void postorder(BSTNode<T>* root)
{
    if (!root) return;
    postorder(root->left);
    postorder(root->right);
    std::cout << root->data << " ";
}

template <typename T>
void deleteBST(BSTNode<T>* root)
{
    if (!root) return;
    deleteBST(root->left);
    deleteBST(root->right);
    delete root;
}

#endif