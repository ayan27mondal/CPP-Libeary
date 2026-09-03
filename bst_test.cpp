#include "BST.cpp"

int main()
{
    BSTNode<int>* root = nullptr;

    root = insertBST(root, 5);
    insertBST(root, 1);
    insertBST(root, 3);
    insertBST(root, 4);
    insertBST(root, 2);
    insertBST(root, 7);

    std::cout << "Preorder : ";
    preorder(root);
    std::cout << std::endl;

    std::cout << "Inorder : ";
    inorder(root);
    std::cout << std::endl;

    std::cout << "Postorder : ";
    postorder(root);
    std::cout << std::endl;

    deleteBST(root);
    return 0;
}