#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

template <class T>
class cTree {
private:
    struct Node {
        T key;
        int priority;
        Node* left;
        Node* right;
        Node* parent;

        Node(const T& k, int p) : key(k), priority(p), left(nullptr), right(nullptr), parent(nullptr) {}
    };

    Node* root;

    void split(Node* node, T key, Node*& left, Node*& right);
    Node* merge(Node* left, Node* right);
    void inorderTraversal(Node* node);

public:
    cTree() : root(nullptr) {}

    void insert(const T& key);
    void split(T key, cTree<T>& left, cTree<T>& right);
    void inorderTraversal();
};

template <class T>
void cTree<T>::split(Node* node, T key, Node*& left, Node*& right) {
    if (node == nullptr) {
        left = nullptr;
        right = nullptr;
    }
    else if (node->key <= key) {
        split(node->right, key, node->right, right);
        left = node;
        if (node->right != nullptr) {
            node->right->parent = node;
        }
    }
    else {
        split(node->left, key, left, node->left);
        right = node;
        if (node->left != nullptr) {
            node->left->parent = node;
        }
    }
}

template <class T>
typename cTree<T>::Node* cTree<T>::merge(Node* left, Node* right) {
    if (left == nullptr) return right;
    if (right == nullptr) return left;

    if (left->priority > right->priority) {
        left->right = merge(left->right, right);
        if (left->right != nullptr) {
            left->right->parent = left;
        }
        return left;
    }
    else {
        right->left = merge(left, right->left);
        if (right->left != nullptr) {
            right->left->parent = right;
        }
        return right;
    }
}

template <class T>
void cTree<T>::insert(const T& key) {
    int priority = rand(); 
    Node* newNode = new Node(key, priority);
        if (newNode == NULL)
            throw exception("empty  node");
    root = merge(root, newNode);
}

template <class T>
void cTree<T>::split(T key, cTree<T>& left, cTree<T>& right) {
    Node* leftNode;
    Node* rightNode;
    split(root, key, leftNode, rightNode);
    left.root = leftNode;
    right.root = rightNode;
}

template <class T>
void cTree<T>::inorderTraversal() {
    inorderTraversal(root);
    cout << endl;
}

template <class T>
void cTree<T>::inorderTraversal(Node* node) {
    if (node != nullptr) {
        inorderTraversal(node->left);
        cout << node->key << " ";
        inorderTraversal(node->right);
    }
}

int main() {
    cTree<int> tree;

    tree.insert(5);
    tree.insert(2);
    tree.insert(8);
    tree.insert(1);
    tree.insert(3);
    tree.insert(7);

    cTree<int> leftTree;
    cTree<int> rightTree;
    tree.split(4, leftTree, rightTree);

 
    cout << "Original Tree: ";
    tree.inorderTraversal();

    cout << "Left Tree: ";
    leftTree.inorderTraversal();

    cout << "Right Tree: ";
    rightTree.inorderTraversal();

    return 0;
}
