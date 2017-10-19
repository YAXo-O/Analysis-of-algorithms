#ifndef AVLTREE_H
#define AVLTREE_H

/*
  4_2. Порядковые статистики.​
Дано число N и N строк. Каждая строка содержит команду
добавления или удаления натуральных чисел, а также запрос на получение k-ой
порядковой статистики. Команда добавления числа A задается положительным числом A,
команда удаления числа A задается отрицательным числом “-A”. Запрос на получение
k-ой порядковой статистики задается числом k. Требуемая скорость выполнения запроса -
O(log n).
*/

#include <iostream>
#include <queue>
#include "array.h"

// AVL-tree
// Taken from my lab for TP

template<typename T>
struct node
{
    T key;
    node *left = nullptr;
    node *right = nullptr;

    unsigned char getHeight();
    unsigned char getBalanceFactor();

    node(T _key): key(_key){}
    ~node();
};

template<typename T>
std::ostream &operator<<(std::ostream &out, const node<T> &n)
{
    if(n.left)
        operator<<(out, *(n.left));

    out << n.key << " ";

    if(n.right)
        operator<<(out, *(n.right));

    return out;
}

template<typename T>
unsigned char node<T>::getHeight()
{
    unsigned char leftHeight = left ? left->getHeight() : 0;
    unsigned char rightHeight = right ? right->getHeight() : 0;

    return leftHeight > rightHeight ? leftHeight + 1 : rightHeight + 1;
}

template<typename T>
unsigned char node<T>::getBalanceFactor()
{
    if(this == nullptr)
        return 0;

    unsigned char leftHeight = left ? left->getHeight() : 0;
    unsigned char rightHeight = right ? right->getHeight() : 0;

    return leftHeight - rightHeight;
}

template<typename T>
node<T>::~node()
{
    if(left)
        delete left;
    if(right)
        delete right;
}

template<typename T>
class AVLtree
{
public:
    AVLtree(): root(nullptr), currentStat(0) {}
    AVLtree(const Array<T> &arr);
    ~AVLtree() {delete root;}

    void insert(T key);
    void remove(T key);
    T findStatistics(size_t stat);
    void writeToArray(Array<T> &arr);

    template<typename R>
    friend std::ostream &operator<<(std::ostream &out, const AVLtree<R> &tree);

private:
    node<T> *root;
    size_t currentStat;
    T stat;
    size_t arrId;

    node<T> *turnRight(node<T> *root);
    node<T> *turnLeft(node<T> *root);
    node<T> *fixBalance(node<T> *root);

    node<T> *insert(node<T> *root, T key);
    node<T> *remove(node<T> *root, T key);
    node<T> *findMin(node<T> *root);
    node<T> *extractMin(node<T> *root);

    void findStats(size_t stat, node<T> *root);
};

template<typename T>
std::ostream &operator<<(std::ostream &out, const AVLtree<T> &tree)
{
    out << *(tree.root);

    return out;
}

template<typename T>
AVLtree<T>::AVLtree(const Array<T> &arr): root(nullptr), currentStat(0)
{
    for(auto i : arr)
        insert(i);
}

template<typename T>
void AVLtree<T>::insert(T key)
{
    root = insert(root, key);
}

template<typename T>
void AVLtree<T>::remove(T key)
{
    if(!root)
        return;

    remove(root, key);
}

template<typename T>
T AVLtree<T>::findStatistics(size_t _stat)
{
    currentStat = 0;
    findStats(_stat, root);

    return stat;
}

template<typename T>
void AVLtree<T>::writeToArray(Array<T> &arr)
{
    if(!root)
        return;

    std::cout << int(root->getHeight()) << std::endl;

    arrId = 0;
    std::queue<node<T> *> q;
    q.push(root);
    while(!q.empty())
    {
        node<T> *cur = q.front();
        q.pop();

        arr[arrId++] = cur->key;

        if(cur->left)
            q.push(cur->left);
        if(cur->right)
            q.push(cur->right);
    }
}

template<typename T>
node<T> *AVLtree<T>::turnRight(node<T> *root)
{
    if(!root)
        return nullptr;

    node<T> *lowerChild = root->left;
    root->left = lowerChild->right;
    lowerChild->right = root;

    return lowerChild;
}

template<typename T>
node<T> *AVLtree<T>::turnLeft(node<T> *root)
{
    if(!root)
        return nullptr;

    node<T> *greaterChild = root->right;
    root->right = greaterChild->left;
    greaterChild->left = root;

    return greaterChild;
}

template<typename T>
node<T> *AVLtree<T>::fixBalance(node<T> *root)
{
    if(!root)
        return nullptr;

    if(root->getBalanceFactor() == 2)
    {
        if(root->right->getBalanceFactor() < 0)
            root->right = turnRight(root->right);

        return turnLeft(root);
    }

    if(root->getBalanceFactor() == -2)
    {
        if(root->left->getBalanceFactor() > 0)
            root->left = turnLeft(root->left);

        return turnRight(root);
    }

    return root;
}

template<typename T>
node<T> *AVLtree<T>::insert(node<T> *root, T key)
{
    if(!root)
        root = new node<T>(key);
    else
    {
        if(key >= root->key)
            root->right = insert(root->right, key);
        else
            root->left = insert(root->left, key);
    }

    return fixBalance(root);

}

template<typename T>
node<T> *AVLtree<T>::remove(node<T> *root, T key)
{
    if(!root)
        return nullptr;

    if(key < root->key)
        root->left = remove(root->left, key);
    else if(key > root->key)
        root->right = remove(root->right, key);
    else
    {
        node<T> *leftSubroot = root->left;
        node<T> *rightSubroot = root->right;
        delete root;

        if(!rightSubroot)
            return leftSubroot;

        node<T> *min = findMin(rightSubroot);
        min->right = extractMin(rightSubroot);
        min->left = leftSubroot;

        return fixBalance(min);
    }

    return fixBalance(root);

}


template<typename T>
node<T> *AVLtree<T>::findMin(node<T> *root)
{
    if(!root)
        return nullptr;

    if(root->left)
        return findMin(root->left);
    else
        return root;
}

template<typename T>
node<T> *AVLtree<T>::extractMin(node<T> *root)
{
    if(!root)
        return nullptr;

    if(!root->left)
        return root->right;

    root->left = extractMin(root->left);

    return fixBalance(root);
}

template<typename T>
void AVLtree<T>::findStats(size_t _stat, node<T> *root)
{
    if(!root)
        std::invalid_argument("incorrect root");

    if(root->left)
        findStats(_stat, root->left);

    if(currentStat > _stat)
        return;

    if(_stat == currentStat)
    {
        stat = root->key;

        return;
    }
    currentStat++;;

    if(root->right)
        findStats(_stat, root->right);
}

#endif // AVLTREE_H
