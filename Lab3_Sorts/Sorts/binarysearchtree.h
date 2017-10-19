#ifndef BINARYSEARCHTREE_H
#define BINARYSEARCHTREE_H

#include <queue>
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
    void widthWriteToArray(Array<T> &ar);

    void setAllowRepeat(bool bAllow);

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
    bool bAllowRepeat = true;
    size_t widthId;

    void _insertValue(const T &value, Node<T> *treeHead);
    void _deleteTree(Node<T> *treeHead);
    void _writeToArray(Array<T> &ar, Node<T> *treeHead);

};


template<typename T>
BinarySearchTree<T>::BinarySearchTree(): head(nullptr), arrayId(0), widthId(0)
{
}

template<typename T>
BinarySearchTree<T>::BinarySearchTree(const Array<T> &ar): head(nullptr), arrayId(0), widthId(0)
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
void BinarySearchTree<T>::widthWriteToArray(Array<T> &ar)
{
    std::queue<Node<T> *> q;
    q.push(head);
    while(!q.empty())
    {
        Node<T> *node = q.front();
        q.pop();

        ar[widthId++] = node->data;

        if(node->leftTree)
            q.push(node->leftTree);
        if(node->rightTree)
            q.push(node->rightTree);
    }
}

template<typename T>
void BinarySearchTree<T>::setAllowRepeat(bool _bAllow)
{
    bAllowRepeat = _bAllow;
}

template<typename T>
void BinarySearchTree<T>::_insertValue(const T &value, Node<T> *treeHead)
{
    if(!treeHead)
        return;

    if(!bAllowRepeat && value == treeHead->data)
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
