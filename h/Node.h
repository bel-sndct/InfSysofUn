#ifndef NODE_H
#define NODE_H
#include <iostream>
using namespace std;

template <typename T, typename K>
class Node {
public:
    T value;
    K key;
    Node<T, K>* left;
    Node<T, K>* right;
    Node<T, K>* parent;
    bool isRed;

    Node()
        : left(nullptr)
        , right(nullptr)
        , parent(nullptr)
        , isRed(true) {
    }

    Node(const T& _data, const K& _key)
        : left(nullptr)
        , right(nullptr)
        , parent(nullptr)
        , value(_data)
        , key(_key)
        , isRed(true) {
    }

    inline T& getData() { return this->value; }
    inline const T& getData() const { return this->value; }

    void displayNode() {
        cout << value << " " << key;
        if (isRed) cout << "_red";
        else cout << "_black";
    }

    ~Node() = default;
};
#endif // NODE_H
