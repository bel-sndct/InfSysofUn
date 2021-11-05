#ifndef RGBTREE_H
#define RGBTREE_H
#include "Node.h"

template <typename T, typename K>
class RBIterator;

template <typename T, typename K>
class RBTree
{
private:
    //Node<T, K>* root;
    Node<T, K>* rotateLeft(Node<T, K>*);
    Node<T, K>* rotateRight(Node<T, K>*);
    Node<T, K>* find(Node<T, K>*, K);
    Node<T, K>* insert(Node<T, K>*, K, T&);
    void flipColors(Node<T, K>*);
    void displayTree(Node<T, K>*, int);
    bool isRed(Node<T, K>*);

public:
    Node<T, K>* root;
    RBTree() : root(nullptr) {}
    Node<T, K>* find(K);
    void displayTree();
    void insert(T&, K);
    void deleteNode(K);
    Node<T, K>* createNewTree(RBTree<T, K>*);
    inline Node<T, K>* getRoot() { return this->root; }
    ~RBTree() = default;
};

template <typename T, typename K>
Node<T, K>* RBTree<T, K>::rotateLeft(Node<T, K>* current) {
    Node<T, K>* rotating = current->right;

    current->right = rotating->left;

    if (rotating->left != nullptr)
        rotating->left->parent = current;

    rotating->left = current;

    if (current->parent == nullptr)
        rotating->parent = nullptr;
    else rotating->parent = current->parent;

    current->parent = rotating;

    rotating->isRed = current->isRed;
    current->isRed = true;

    return rotating;
}

template <typename T, typename K>
Node<T, K>* RBTree<T, K>::rotateRight(Node<T, K>* current) {
    Node<T, K>* rotating = current->left;

    current->left = rotating->right;

    if (rotating->right != nullptr)
        rotating->right->parent = current;

    rotating->right = current;

    if (current->parent == nullptr)
        rotating->parent = nullptr;
    else rotating->parent = current->parent;

    current->parent = rotating;

    rotating->isRed = current->isRed;
    current->isRed = true;

    return rotating;
}

template <typename T, typename K>
Node<T, K>* RBTree<T, K>::find(Node<T, K>* current, K key) {
    if (current == nullptr)
        return nullptr;
    if (key == current->key) {
        return current;
    }
    if (key < current->key) {
        return find(current->left, key);
    }
    return find(current->right, key);
}

template <typename T, typename K>
Node<T, K>* RBTree<T, K>::insert(Node<T, K>* current, K key, T& value) {
    if (current == nullptr) {
        Node<T, K>* newNode = new Node<T, K>;
        newNode->key = key;
        newNode->value = value;
        return newNode;
    }
    if (key < current->key) {
        current->left = insert(current->left, key, value);
        current->left->parent = current;
    }
    else if (key > current->key) {
        current->right = insert(current->right, key, value);
        current->right->parent = current;
    }
    else current->value = value;

    if (isRed(current->right) && !isRed(current->left))
        current = rotateLeft(current);
    if (isRed(current->left) && isRed(current->left->left))
        current = rotateRight(current);

    if (isRed(current->left) && isRed(current->right))
        flipColors(current);

    return current;
}

template <typename T, typename K>
void RBTree<T, K>::flipColors(Node<T, K>* current) {
    current->isRed = true;
    current->left->isRed = false;
    current->right->isRed = false;
}

template <typename T, typename K>
void RBTree<T, K>::displayTree(Node<T, K>* current, int order) {
    if (current != NULL)
        displayTree(current->right, order + 1);
    for (int i = 0; i < order; ++i)
        cout << "\t";
    if (current != NULL) {
        current->DisplayNode();
        cout << "\n";
    }
    else cout << "-\n";
    if (current != NULL)
        displayTree(current->left, order + 1);
}

template <typename T, typename K>
bool RBTree<T, K>::isRed(Node<T, K>* node) {
    if (node == nullptr) return false;
    return node->isRed == true;
}

template <typename T, typename K>
Node<T, K>* RBTree<T, K>::find(K key) {
    return find(root, key);
}

template <typename T, typename K>
void RBTree<T, K>::displayTree() {
    displayTree(root, 0);
}

template <typename T, typename K>
void RBTree<T, K>::insert(T& value, K key) {
    Node<T, K>* node = find(root, key);
    if (node != nullptr) {
        node->value = value;
    }
    else {
        root = insert(root, key, value);
        root->isRed = false;
    }
}

template<typename T, typename K>
void RBTree<T, K>::deleteNode(K _key) {

    Node<T, K>* limb1 = root; Node<T, K>* limb2 = root; Node<T, K>* limb3 = nullptr;

    if (root == nullptr) return;
    if (_key == root->key) return;

    while (limb1->key != _key)
    {
        if (_key > limb1->key)
        {
            if (limb1->right != nullptr)
            {
                limb2 = limb1;
                limb1 = limb1->right;
            }
            else return;
        }
        else
        {
            if (limb1->left != nullptr)
            {
                limb2 = limb1;
                limb1 = limb1->left;
            }
            else return;
        }
    }

    limb3 = limb1;

    if (limb1->key < limb2->key)
    {

        if (limb1->right != nullptr)
        {
            limb3 = limb1->right;
            while (limb3->left != nullptr)
                limb3 = limb3->left;
            limb2->left = limb1->right;
            limb1->right->parent = limb2;
            limb3->left = limb1->left;
            if (limb1->left != nullptr)
                limb1->left->parent = limb3;
        }
        else
        {
            limb2->left = limb1->left;
            if (limb1->left != nullptr)
                limb1->left->parent = limb2;
        }
    }
    else
    {
        if (limb1->left != nullptr)
        {
            limb3 = limb1->left;
            while (limb3->right != nullptr)
                limb3 = limb3->right;
            limb2->right = limb1->left;
            limb1->left->parent = limb2;
            limb3->right = limb1->right;
            if (limb1->right != nullptr)
                limb1->right->parent = limb3;
        }
        else
        {
            limb2->right = limb1->right;
            if (limb1->right != nullptr)
                limb1->right->parent = limb2;
        }
    }
    return;
}

template <typename T, typename K>
Node<T, K>* RBTree<T, K>::createNewTree(RBTree<T, K>* _tree) {

    if (_tree->getRoot() == nullptr) return nullptr;
    if ((_tree->getRoot()->right == nullptr && _tree->getRoot()->left == nullptr)) {
        return nullptr;
    }
    else {
        RBTree<T, K>* new_tree = new RBTree<T, K>;
        RBIterator<T, K> new_it;
        new_it = new_it.begin(_tree, _tree->getRoot());
        while (new_it != new_it.end(_tree, _tree->getRoot())) {
            if (new_it.getNode()->key != _tree->root->key)
                new_tree->insert(*new_it, new_it.getNode()->key);
            new_it++;
        }
        return new_tree->root;
    }
}

#endif // RGBTREE_H
