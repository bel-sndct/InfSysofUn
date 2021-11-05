#ifndef RBITERATOR_H
#define RBITERATOR_H
#include "RBTree.h"

template <typename T, typename K>
class RBIterator {
    friend class RBTree<T, K>;
public:
    RBIterator();
    RBIterator(const RBTree<T, K>*, Node<T, K>*);
    RBIterator(const RBIterator&);
    RBIterator(RBIterator&&);
    ~RBIterator() = default;

    RBIterator<T, K>& operator=(const RBIterator<T, K>&);
    RBIterator<T, K>& operator=(RBIterator<T, K>&&) noexcept;
    RBIterator<T, K>& operator++();
    RBIterator<T, K>& operator++(int);
    T& operator*();
    T* operator->();
    const T* operator->() const;

    bool operator==(const RBIterator<T, K>&) const;
    bool operator!=(const RBIterator<T, K>&) const;

    Node<T, K>* getNode();
    static RBIterator<T, K> begin(RBTree<T, K>*, Node<T, K>*);
    static RBIterator<T, K> end(RBTree<T, K>*, Node<T, K>*);

private:
    const RBTree<T, K>* instance;
    Node<T, K>* currentNode;
};

template <typename T, typename K>
RBIterator<T, K>::RBIterator()
    : instance(nullptr)
    , currentNode(nullptr) {
}

template <typename T, typename K>
RBIterator<T, K>::RBIterator(const RBTree<T, K>* _instance, Node<T, K>* _initialNode)
    : instance(_instance)
    , currentNode(_initialNode) {
}

template <typename T, typename K>
RBIterator<T, K>::RBIterator(const RBIterator& _other)    //???
    : instance(_other.instance)
    , currentNode(_other.currentNode) {
}

template <typename T, typename K>
RBIterator<T, K>::RBIterator(RBIterator&& _other)
    : instance(_other.instance)
    , currentNode(_other.currentNode) {
    _other.instance = nullptr;
    _other.currentNode = nullptr;
}

template <typename T, typename K>
RBIterator<T, K>& RBIterator<T, K>::operator=(const RBIterator<T, K>& _other) {
    this->instance = _other.instance;
    this->currentNode = _other.currentNode;
    return *this;
}

template <typename T, typename K>
RBIterator<T, K>& RBIterator<T, K>::operator=(RBIterator<T, K>&& _other) noexcept {
    this->instance = _other.instance;
    this->currentNode = _other.currentNode;

    _other.instance = nullptr;
    _other.currentNode = nullptr;
    return *this;
}

template <typename T, typename K>
RBIterator<T, K>& RBIterator<T, K>::operator++() {

    Node<T, K>* parent;

    if (this->currentNode == nullptr) return *this;

    parent = this->currentNode->parent;

    if (parent == nullptr) {
        this->currentNode = nullptr;
        return *this;
    }

    if ((this->currentNode == parent->left) && (parent->right != nullptr)) {
        this->currentNode = parent->right;
    }
    else {
        this->currentNode = this->currentNode->parent;
        return *this;
    }
    while (true) {
        if (this->currentNode->left != nullptr) {
            this->currentNode = this->currentNode->left;
        }
        else if (this->currentNode->right != nullptr) {
            this->currentNode = this->currentNode->right;
        }
        else return *this;
    }
}

template <typename T, typename K>
RBIterator<T, K>& RBIterator<T, K>::operator++(int _value) {
    RBIterator<T, K> old_Iterator = *this;
    ++(*this);
    return old_Iterator;
}

template <typename T, typename K>
T& RBIterator<T, K>::operator*() {
    return this->currentNode->getData();
}

template <typename T, typename K>
T* RBIterator<T, K>::operator->() {
    return &(this->currentNode->getData());
}

template <typename T, typename K>
const T* RBIterator<T, K>::operator->() const {
    return &(this->currentNode->getData());
}

template <typename T, typename K>
Node<T, K>* RBIterator<T, K>::getNode() {
    return this->currentNode;
}

template <typename T, typename K>
bool RBIterator<T, K>::operator==(const RBIterator<T, K>& _other) const {
    return (this->instance == _other.instance && this->currentNode == _other.currentNode);
}

template <typename T, typename K>
bool RBIterator<T, K>::operator!=(const RBIterator<T, K>& _other) const {
    return !((*this) == _other);
}

template <typename T, typename K>
RBIterator<T, K> RBIterator<T, K>::begin(RBTree<T, K>* _instance, Node<T, K>* _root) {
    if (_root == nullptr) {
        return RBIterator(_instance, _root);
    }

    while (true) {
        if (_root->left != nullptr) {
            _root = _root->left;
        }
        else if (_root->right != nullptr) {
            _root = _root->right;
        }
        else {
            return RBIterator(_instance, _root);
        }
    }
}

template <typename T, typename K>
RBIterator<T, K> RBIterator<T, K>::end(RBTree<T, K>* _instance, Node<T, K>* _root) {
    return RBIterator(_instance, _root->parent);
}

#endif // RBITERATOR_H
