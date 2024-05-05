#include <iostream>
#include <cstdlib>
#include <ctime>

using namespace std;

template <class T>
class cTree {
protected:
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
    template <class U>
    friend  class ImplicitKeycTree;
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



template <class T>
class ImplicitKeycTree : public cTree<T> {
private:
    using Node = typename cTree<T>::Node;

    int size(Node* node);

    void merge(Node*& result, Node* left, Node* right);

    void split(Node* node, int index, Node*& left, Node*& right);

    void propagateLazy(Node* node);

    void updateLazy(Node* node, T lazy);

    T queryMaxOnRange(Node* node, int start, int end);

public:
    ImplicitKeycTree() : cTree<T>() {}

    // Определение числа элементов в поддереве с корнем в текущем узле
    int size();

    // Слияние двух деревьев
    void merge(ImplicitKeycTree<T>& other);

    // Разделение дерева на два по значению размера
    void split(int index, ImplicitKeycTree<T>& left, ImplicitKeycTree<T>& right);

    // Поддержка групповой функции максимума на отрезке массива
    T queryMaxOnRange(int start, int end);

    // Задание значения элементу в заданной позиции
    void set(int index, T value);

    // Вывод дерева
    void print();
};

template <class T>
int ImplicitKeycTree<T>::size(Node* node) {
    return node ? node->size : 0;
}

template <class T>
int ImplicitKeycTree<T>::size() {
    return size(this->root);
}

template <class T>
void ImplicitKeycTree<T>::merge(Node*& result, Node* left, Node* right) {
    result = cTree<T>::merge(left, right);  // Создаем новый узел слиянием left и right
    updateLazy(result, 0);
}

template <class T>
void ImplicitKeycTree<T>::merge(ImplicitKeycTree<T>& other) {
    merge(this->root, this->root, other.root);
}

template <class T>
void ImplicitKeycTree<T>::split(Node* node, int index, Node*& left, Node*& right) {
    if (!node) {
        left = nullptr;
        right = nullptr;
        return;
    }

    propagateLazy(node);

    int leftSize = size(node->left);

    if (index <= leftSize) {
        split(node->left, index, left, node->left);
        right = node;
        updateLazy(right, 0);
    }
    else {
        split(node->right, index - leftSize - 1, node->right, right);
        left = node;
        updateLazy(left, 0);
    }

    node->size = size(node->left) + size(node->right) + 1;
}

template <class T>
void ImplicitKeycTree<T>::split(int index, ImplicitKeycTree<T>& left, ImplicitKeycTree<T>& right) {
    split(this->root, index, left.root, right.root);
}

template <class T>
void ImplicitKeycTree<T>::propagateLazy(Node* node) {
    if (node->lazy != 0) {
        updateLazy(node->left, node->lazy);
        updateLazy(node->right, node->lazy);
        node->lazy = 0;
    }
}

template <class T>
void ImplicitKeycTree<T>::updateLazy(Node* node, T lazy) {
    if (node) {
        node->key += lazy;
        node->lazy += lazy;
    }
}

template <class T>
T ImplicitKeycTree<T>::queryMaxOnRange(Node* node, int start, int end) {
    if (!node || start >= size(node) || end < 0) {
        return numeric_limits<T>::min();
    }

    propagateLazy(node);

    int currentSize = size(node->left);

    if (start <= 0 && end >= currentSize) {
        return node->key;
    }
    else if (end < currentSize) {
        return queryMaxOnRange(node->left, start, end);
    }
    else if (start >= currentSize) {
        return queryMaxOnRange(node->right, start - currentSize - 1, end - currentSize - 1);
    }
    else {
        T leftMax = queryMaxOnRange(node->left, start, currentSize - 1);
        T rightMax = queryMaxOnRange(node->right, 0, end - currentSize - 1);
        return max(leftMax, rightMax);
    }
}

template <class T>
T ImplicitKeycTree<T>::queryMaxOnRange(int start, int end) {
    return queryMaxOnRange(this->root, start, end);
}

template <class T>
void ImplicitKeycTree<T>::set(int index, T value) {
    ImplicitKeycTree<T> left, right;
    split(index, left, right);

    Node* newNode = new Node(value, rand());
    merge(left.root, left.root, newNode);
    merge(this->root, left.root, right.root);
}

template <class T>
void ImplicitKeycTree<T>::print() {
    cout << "ImplicitKeycTree: ";
    cTree<T>::inorderTraversal();
    cout << endl;
}

int main() {
  

    ImplicitKeycTree<double> implicitKeycTree;

    // Вставка значений в дерево
    implicitKeycTree.insert(1);
    implicitKeycTree.insert(2);
    implicitKeycTree.insert(3);
    implicitKeycTree.insert(4);
    implicitKeycTree.insert(5);

    // Вывод дерева
    implicitKeycTree.print();

    // Выполнение групповой операции (например, запрос максимума на отрезке)
    double maxInRange = implicitKeycTree.queryMaxOnRange(2, 4);
    cout << "Max on range [2, 4]: " << maxInRange << endl;

    // Задание нового значения элементу
    implicitKeycTree.set(3, 10);

    // Вывод измененного дерева
    implicitKeycTree.print();

    return 0;
}
