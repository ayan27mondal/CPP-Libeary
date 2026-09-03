#ifndef __AVLTREE_HPP__
#define __AVLTREE_HPP__

#include <algorithm>
#include <string>
#include <iostream>

template <typename T>
class AVLNode
{
public:
    T _data;
    AVLNode* _left;
    AVLNode* _right;
    AVLNode* _parent;
    int height;

    explicit AVLNode(const T& data) : _data(data), _left(nullptr), _right(nullptr), _parent(nullptr), height(1) {}
};

template <typename T>
class AVLTree
{
private:
    AVLNode<T>* _root;

    static int height(AVLNode<T>* node)
    {
        return node ? node->height : 0;
    }

    static void updateHeight(AVLNode<T>* node)
    {
        if (node) node->height = 1 + std::max(height(node->_left), height(node->_right));
    }

    static AVLNode<T>* rightRotate(AVLNode<T>* y)
    {
        AVLNode<T>* x = y->_left;
        AVLNode<T>* T2 = x->_right;

        x->_right = y;
        y->_left = T2;

        if (T2) T2->_parent = y;
        x->_parent = y->_parent;
        y->_parent = x;

        updateHeight(y);
        updateHeight(x);
        return x;
    }

    static AVLNode<T>* leftRotate(AVLNode<T>* x)
    {
        AVLNode<T>* y = x->_right;
        AVLNode<T>* T2 = y->_left;

        y->_left = x;
        x->_right = T2;

        if (T2) T2->_parent = x;
        y->_parent = x->_parent;
        x->_parent = y;

        updateHeight(x);
        updateHeight(y);
        return y;
    }

    static int getBalance(AVLNode<T>* node)
    {
        return node ? height(node->_left) - height(node->_right) : 0;
    }

    AVLNode<T>* insertNode(AVLNode<T>* root, const T& data)
    {
        if (!root) return new AVLNode<T>(data);

        if (data < root->_data)
        {
            root->_left = insertNode(root->_left, data);
            root->_left->_parent = root;
        }
        else if (data > root->_data)
        {
            root->_right = insertNode(root->_right, data);
            root->_right->_parent = root;
        }
        else
        {
            return root; // Duplicate not allowed
        }

        updateHeight(root);
        int balance = getBalance(root);

        // Left Left
        if (balance > 1 && data < root->_left->_data)
            return rightRotate(root);

        // Right Right
        if (balance < -1 && data > root->_right->_data)
            return leftRotate(root);

        // Left Right
        if (balance > 1 && data > root->_left->_data)
        {
            root->_left = leftRotate(root->_left);
            return rightRotate(root);
        }

        // Right Left
        if (balance < -1 && data < root->_right->_data)
        {
            root->_right = rightRotate(root->_right);
            return leftRotate(root);
        }

        return root;
    }

    bool searchNode(AVLNode<T>* root, const T& data) const
    {
        if (!root) return false;
        if (data == root->_data) return true;
        return data < root->_data ? searchNode(root->_left, data) : searchNode(root->_right, data);
    }

    AVLNode<T>* minValueNode(AVLNode<T>* root) const
    {
        while (root && root->_left) root = root->_left;
        return root;
    }

    AVLNode<T>* deleteNode(AVLNode<T>* root, const T& data)
    {
        if (!root) return nullptr;

        if (data < root->_data)
        {
            root->_left = deleteNode(root->_left, data);
            if (root->_left) root->_left->_parent = root;
        }
        else if (data > root->_data)
        {
            root->_right = deleteNode(root->_right, data);
            if (root->_right) root->_right->_parent = root;
        }
        else
        {
            if (!root->_left || !root->_right)
            {
                AVLNode<T>* temp = root->_left ? root->_left : root->_right;
                if (!temp)
                {
                    temp = root;
                    root = nullptr;
                }
                else
                {
                    *root = *temp; // Copy contents
                }
                delete temp;
            }
            else
            {
                AVLNode<T>* temp = minValueNode(root->_right);
                root->_data = temp->_data;
                root->_right = deleteNode(root->_right, temp->_data);
                if (root->_right) root->_right->_parent = root;
            }
        }

        if (!root) return nullptr;

        updateHeight(root);
        int balance = getBalance(root);

        // Left Left
        if (balance > 1 && getBalance(root->_left) >= 0)
            return rightRotate(root);

        // Left Right
        if (balance > 1 && getBalance(root->_left) < 0)
        {
            root->_left = leftRotate(root->_left);
            return rightRotate(root);
        }

        // Right Right
        if (balance < -1 && getBalance(root->_right) <= 0)
            return leftRotate(root);

        // Right Left
        if (balance < -1 && getBalance(root->_right) > 0)
        {
            root->_right = rightRotate(root->_right);
            return leftRotate(root);
        }

        return root;
    }

    void deleteTree(AVLNode<T>* root)
    {
        if (root)
        {
            deleteTree(root->_left);
            deleteTree(root->_right);
            delete root;
        }
    }

    AVLNode<T>* copyTree(AVLNode<T>* root, AVLNode<T>* parent = nullptr)
    {
        if (!root) return nullptr;
        AVLNode<T>* n = new AVLNode<T>(root->_data);
        n->_parent = parent;
        n->_left = copyTree(root->_left, n);
        n->_right = copyTree(root->_right, n);
        n->height = root->height;
        return n;
    }

    void inorder(AVLNode<T>* root, std::vector<T>& result) const
    {
        if (!root) return;
        inorder(root->_left, result);
        result.push_back(root->_data);
        inorder(root->_right, result);
    }

    void preorder(AVLNode<T>* root, std::vector<T>& result) const
    {
        if (!root) return;
        result.push_back(root->_data);
        preorder(root->_left, result);
        preorder(root->_right, result);
    }

    void postorder(AVLNode<T>* root, std::vector<T>& result) const
    {
        if (!root) return;
        postorder(root->_left, result);
        postorder(root->_right, result);
        result.push_back(root->_data);
    }

    void printTree(AVLNode<T>* root, const std::string& indent, bool last) const
    {
        if (root)
        {
            std::cout << indent;
            if (last)
            {
                std::cout << "R----";
                printTree(root->_left, indent + "   ", false);
                printTree(root->_right, indent + "   ", true);
            }
            else
            {
                std::cout << "L----";
                printTree(root->_left, indent + "|  ", false);
                printTree(root->_right, indent + "|  ", true);
            }
            std::cout << root->_data << std::endl;
        }
    }

public:
    AVLTree() : _root(nullptr) {}

    explicit AVLTree(AVLNode<T>* root) : _root(root) {}

    ~AVLTree()
    {
        deleteTree(_root);
    }

    AVLTree(const AVLTree& other) : _root(copyTree(other._root)) {}

    AVLTree& operator=(const AVLTree& other)
    {
        if (this != &other)
        {
            deleteTree(_root);
            _root = copyTree(other._root);
        }
        return *this;
    }

    AVLTree(AVLTree&& other) noexcept : _root(other._root)
    {
        other._root = nullptr;
    }

    AVLTree& operator=(AVLTree&& other) noexcept
    {
        if (this != &other)
        {
            deleteTree(_root);
            _root = other._root;
            other._root = nullptr;
        }
        return *this;
    }

    bool empty() const { return _root == nullptr; }

    void insert(const T& data)
    {
        _root = insertNode(_root, data);
    }

    bool search(const T& data) const
    {
        return searchNode(_root, data);
    }

    void remove(const T& data)
    {
        _root = deleteNode(_root, data);
    }

    std::vector<T> inorder() const
    {
        std::vector<T> result;
        inorder(_root, result);
        return result;
    }

    std::vector<T> preorder() const
    {
        std::vector<T> result;
        preorder(_root, result);
        return result;
    }

    std::vector<T> postorder() const
    {
        std::vector<T> result;
        postorder(_root, result);
        return result;
    }

    void printTree() const
    {
        printTree(_root, "", true);
    }
};

#endif