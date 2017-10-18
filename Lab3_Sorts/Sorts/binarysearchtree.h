#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include "array.h"

template<typename T>
class BinarySearchTree
{
public:
    BinarySearchTree();
    BinarySearchTree(const Array<T> &ar);
    ~BinarySearchTree();

    void insertValue(const T &value);
    void writeToArray(Array<T> &ar);

private:
    template<typename>
    struct Node
    {
        T data;
        Node *leftTree = nullptr;
        Node *rightTree = nullptr;

        Node(const T &value): data(value)
        {
        }
    };

    Node<T> *head;
    size_t arrayId;

    void _insertValue(const T &value, Node<T> *treeHead);
    void _deleteTree(Node<T> *treeHead);
    void _writeToArray(Array<T> &ar, Node<T> *treeHead);

};


template<typename T>
BinarySearchTree<T>::BinarySearchTree(): head(nullptr), arrayId(0)
{
}

template<typename T>
BinarySearchTree<T>::BinarySearchTree(const Array<T> &ar): head(nullptr), arrayId(0)
{
    for(auto i : ar)
        insertValue(i);
}

template<typename T>
BinarySearchTree<T>::~BinarySearchTree()
{
    if(head)
        _deleteTree(head);
}

template<typename T>
void BinarySearchTree<T>::_deleteTree(Node<T> *treeHead)
{
    if(!treeHead)
        return;

    if(treeHead->leftTree)
        _deleteTree(treeHead->leftTree);

    if(treeHead->rightTree)
        _deleteTree(treeHead->rightTree);

    delete treeHead;
}

template<typename T>
void BinarySearchTree<T>::insertValue(const T &value)
{
    if(!head)
    {
        head = new Node<T>(value);

        return;
    }

    _insertValue(value, head);
}

template<typename T>
void BinarySearchTree<T>::writeToArray(Array<T> &ar)
{
    arrayId = 0;
    _writeToArray(ar, head);
}

template<typename T>
void BinarySearchTree<T>::_insertValue(const T &value, Node<T> *treeHead)
{
    if(!treeHead)
        return;

    if(value >= treeHead->data)
    {
        if(treeHead->rightTree)
            _insertValue(value, treeHead->rightTree);
        else
            treeHead->rightTree = new Node<T>(value);
    }
    else
    {
        if(treeHead->leftTree)
            _insertValue(value, treeHead->leftTree);
        else
            treeHead->leftTree = new Node<T>(value);
    }
}

template<typename T>
void BinarySearchTree<T>::_writeToArray(Array<T> &ar, Node<T> *treeHead)
{
    if(!treeHead)
        return;

    if(treeHead->leftTree)
        _writeToArray(ar, treeHead->leftTree);

    ar[arrayId++] = treeHead->data;

    if(treeHead->rightTree)
        _writeToArray(ar, treeHead->rightTree);
}

#endif // BINARYSEARCHTREE_H
