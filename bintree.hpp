#ifndef __BINTREE_HPP__
#define __BINTREE_HPP__

#include <vector>
#include <stdexcept>
#include <iostream>

template <class T>
int search(const std::vector<T>& vec, int start, int end, const T& value)
{
    for (int i = start; i <= end; i++)
    {
        if (vec[i] == value)
            return i;
    }
    return -1;
}

template <class T>
class BinaryTree
{
protected:
    class Node
    {
    public:
        T _data;
        Node* _left;
        Node* _right;
        Node* _parent;

        Node() : _data(), _left(nullptr), _right(nullptr), _parent(nullptr) {}
        explicit Node(const T& data) : _data(data), _left(nullptr), _right(nullptr), _parent(nullptr) {}
        Node(const T& data, Node* l, Node* r) : _data(data), _left(l), _right(r), _parent(nullptr)
        {
            if (l) l->_parent = this;
            if (r) r->_parent = this;
        }
    };

    Node* _root;

    static void deleteTree(Node* root)
    {
        if (root)
        {
            deleteTree(root->_left);
            deleteTree(root->_right);
            delete root;
        }
    }

    static Node* copyTree(Node* root, Node* parent = nullptr)
    {
        if (!root) return nullptr;
        Node* n = new Node(root->_data);
        n->_parent = parent;
        n->_left = copyTree(root->_left, n);
        n->_right = copyTree(root->_right, n);
        return n;
    }

    Node* constructFromInPre(const std::vector<T>& pre, int p_start, int p_end,
                              const std::vector<T>& in, int i_start, int i_end)
    {
        if (i_start > i_end || p_start > p_end)
            return nullptr;
        Node* n = new Node(pre[p_start]);
        int index = search(in, i_start, i_end, pre[p_start]);
        if (index == -1) throw std::invalid_argument("Value not found in inorder");
        if (i_start == i_end && p_start == p_end)
            return n;
        n->_left = constructFromInPre(pre, p_start + 1, p_start + index - i_start, in, i_start, index - 1);
        if (n->_left) n->_left->_parent = n;
        n->_right = constructFromInPre(pre, p_start + index - i_start + 1, p_end, in, index + 1, i_end);
        if (n->_right) n->_right->_parent = n;
        return n;
    }

    Node* constructFromInPost(const std::vector<T>& post, int p_start, int p_end,
                               const std::vector<T>& in, int i_start, int i_end)
    {
        if (i_start > i_end || p_start > p_end)
            return nullptr;
        Node* n = new Node(post[p_end]);
        int index = search(in, i_start, i_end, post[p_end]);
        if (index == -1) throw std::invalid_argument("Value not found in inorder");
        if (i_start == i_end && p_start == p_end)
            return n;
        n->_left = constructFromInPost(post, p_start, p_start + index - i_start - 1, in, i_start, index - 1);
        if (n->_left) n->_left->_parent = n;
        n->_right = constructFromInPost(post, p_start + index - i_start, p_end - 1, in, index + 1, i_end);
        if (n->_right) n->_right->_parent = n;
        return n;
    }

    void preOrder(Node* root, std::vector<T>& result) const
    {
        if (!root) return;
        result.push_back(root->_data);
        preOrder(root->_left, result);
        preOrder(root->_right, result);
    }

    void inOrder(Node* root, std::vector<T>& result) const
    {
        if (!root) return;
        inOrder(root->_left, result);
        result.push_back(root->_data);
        inOrder(root->_right, result);
    }

    void postOrder(Node* root, std::vector<T>& result) const
    {
        if (!root) return;
        postOrder(root->_left, result);
        postOrder(root->_right, result);
        result.push_back(root->_data);
    }

public:
    BinaryTree() : _root(nullptr) {}

    explicit BinaryTree(const T& data) : _root(new Node(data)) {}

    BinaryTree(const T& data, const BinaryTree<T>& leftsubtree, const BinaryTree<T>& rightsubtree)
        : _root(new Node(data, leftsubtree._root, rightsubtree._root))
    {
        if (_root->_left) _root->_left->_parent = _root;
        if (_root->_right) _root->_right->_parent = _root;
    }

    BinaryTree(const std::vector<T>& preorderorpostorder, const std::vector<T>& inorder, bool use_postorder)
    {
        if (preorderorpostorder.size() != inorder.size())
            throw std::invalid_argument("Preorder/Postorder and Inorder sizes must match");
        if (use_postorder)
            _root = constructFromInPost(preorderorpostorder, 0, static_cast<int>(preorderorpostorder.size()) - 1, inorder, 0, static_cast<int>(inorder.size()) - 1);
        else
            _root = constructFromInPre(preorderorpostorder, 0, static_cast<int>(preorderorpostorder.size()) - 1, inorder, 0, static_cast<int>(inorder.size()) - 1);
    }

    ~BinaryTree()
    {
        deleteTree(_root);
    }

    BinaryTree(const BinaryTree& other) : _root(copyTree(other._root)) {}

    BinaryTree& operator=(const BinaryTree& other)
    {
        if (this != &other)
        {
            deleteTree(_root);
            _root = copyTree(other._root);
        }
        return *this;
    }

    BinaryTree(BinaryTree&& other) noexcept : _root(other._root)
    {
        other._root = nullptr;
    }

    BinaryTree& operator=(BinaryTree&& other) noexcept
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

    T& root()
    {
        if (!_root) throw std::out_of_range("Tree is empty");
        return _root->_data;
    }

    const T& root() const
    {
        if (!_root) throw std::out_of_range("Tree is empty");
        return _root->_data;
    }

    BinaryTree<T> left() const
    {
        if (!_root || !_root->_left) return BinaryTree<T>();
        BinaryTree<T> leftsub;
        leftsub._root = copyTree(_root->_left);
        return leftsub;
    }

    BinaryTree<T> right() const
    {
        if (!_root || !_root->_right) return BinaryTree<T>();
        BinaryTree<T> rightsub;
        rightsub._root = copyTree(_root->_right);
        return rightsub;
    }

    void insert_leftchild(const T& data)
    {
        if (!_root) throw std::out_of_range("Tree is empty");
        _root->_left = new Node(data);
        _root->_left->_parent = _root;
    }

    void insert_rightchild(const T& data)
    {
        if (!_root) throw std::out_of_range("Tree is empty");
        _root->_right = new Node(data);
        _root->_right->_parent = _root;
    }

    void insert_leftchild(const BinaryTree<T>& l)
    {
        if (!_root) throw std::out_of_range("Tree is empty");
        deleteTree(_root->_left);
        _root->_left = copyTree(l._root, _root);
    }

    void insert_rightchild(const BinaryTree<T>& r)
    {
        if (!_root) throw std::out_of_range("Tree is empty");
        deleteTree(_root->_right);
        _root->_right = copyTree(r._root, _root);
    }

    std::vector<T> PreOrder() const
    {
        std::vector<T> result;
        preOrder(_root, result);
        return result;
    }

    std::vector<T> InOrder() const
    {
        std::vector<T> result;
        inOrder(_root, result);
        return result;
    }

    std::vector<T> PostOrder() const
    {
        std::vector<T> result;
        postOrder(_root, result);
        return result;
    }
};

#endif