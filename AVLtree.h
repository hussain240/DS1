#include <iostream>
// Created by hussa on 7/14/2024.
//

#ifndef DS1_AVLTREE_H
#define DS1_AVLTREE_H
#include <iostream>
#include "iostream"
#include "pair.h"


template<class T>
class node {
public:
    pair key;
    node<T>* left;
    node<T>* right;
    int height;
    T value;

    node(T value, pair key);
    ~node();
};

template<class T>
node<T>::node(T value, pair key) : value(value), key(key), left(nullptr), right(nullptr), height(1) {}

template<class T>
node<T>::~node() {
    delete left;
    delete right;
}
template<class T>
class AVLtree {
    node<T>* head;
    int sizeOfTree;
    int maxData;
    int minData;
    int maxId;
    int minId;

    int max(int first, int second);
    node<T>* insertHelp(node<T>* head, T value, pair key);
    node<T>* gelgolLL(node<T>* head);
    node<T>* gelgolRR(node<T>* head);
    int calculateBF(node<T>* head) const;
    node<T>* removeHelp(node<T>* head, pair key);
    void checkMax(int key, int id);
    void checkMin(int key, int id);
    node<T>* findMin(node<T>* head) const;
    node<T>* findMax(node<T>* head) const;

public:
    AVLtree();
    void insert(T value, int key, int id);
    void remove(T value, int key, int id);
    int size() const;
    node<T>* find(pair key) const;
    int getMax() const;
    int getMin() const;
    int getMaxId() const;
    int getMinId() const;
    ~AVLtree();
    void printTree(node<T>* node1, int space) const;
    void print() const;
};

template<class T>
AVLtree<T>::AVLtree() : head(nullptr), sizeOfTree(0), maxData(0), minData(0), maxId(0), minId(0) {}

template<class T>
int AVLtree<T>::getMinId() const {
    return this->minId;
}

template<class T>
int AVLtree<T>::getMaxId() const {
    return this->maxId;
}

template<class T>
int AVLtree<T>::size() const {
    return this->sizeOfTree;
}

template<class T>
AVLtree<T>::~AVLtree() {
    delete this->head;
}

template<class T>
void AVLtree<T>::insert(T value, int key, int id) {
    pair a(key, id);
    this->head = insertHelp(this->head, value, a);
    if (this->sizeOfTree == 1) {
        this->maxData = key;
        this->minData = key;
        this->maxId = id;
        this->minId = id;
    } else {
        if (this->maxData < key) {
            this->maxData = key;
            this->maxId = id;
        }
        if (this->minData > key) {
            this->minData = key;
            this->minId = id;
        }
        if (this->maxData == key && this->maxId < id) {
            this->maxId = id;
        }
        if (this->minData == key && this->minId > id) {
            this->minId = id;
            }
        }
}

template<class T>
int AVLtree<T>::max(int first, int second) {
    if(first > second)
    {
        return first;
    }
    return second;
}

template<class T>
node<T>* AVLtree<T>::insertHelp(node<T>* head, T value, pair key) {
    if (head == nullptr) {
        this->sizeOfTree++;
        return new node<T>(value, key);
    }
    if (key < head->key)
    {
        head->left = insertHelp(head->left, value, key);
    }
    else if (key > head->key)
    {
        head->right = insertHelp(head->right, value, key);
    }
    else
    {
        return head;
    }

    int leftHeight = 0;
    if (head->left != nullptr) {
        leftHeight = head->left->height;
    }

    int rightHeight = 0;
    if (head->right != nullptr) {
        rightHeight = head->right->height;
    }

    head->height = 1 + max(leftHeight, rightHeight);
    int balance = calculateBF(head);
    int leftBF=calculateBF(head->left);
    int rightBF=calculateBF(head->right);
    if (balance > 1 && leftBF >= 0) {
        return gelgolLL(head);
    }
    if (balance > 1 && leftBF < 0) {
        head->left = gelgolRR(head->left);
        return gelgolLL(head);
    }
    if (balance < -1 && rightBF <= 0) {
        return gelgolRR(head);
    }
    if (balance < -1 && rightBF > 0) {
        head->right = gelgolLL(head->right);
        return gelgolRR(head);
    }

    return head;
}

template<class T>
int AVLtree<T>::calculateBF(node<T>* head) const {
    if (head == nullptr) {
        return 0;
    }

    int leftHeight = 0;
    if (head->left != nullptr) {
        leftHeight = head->left->height;
    }

    int rightHeight = 0;
    if (head->right != nullptr) {
        rightHeight = head->right->height;
    }

    return leftHeight - rightHeight;
}

template<class T>
node<T>* AVLtree<T>::find(pair key) const {
    node<T>* current = this->head;
    while (current != nullptr) {
        if (current->key > key)
        {
            current = current->left;
        }
        else if (current->key < key)
        {
            current = current->right;
        }
        else
        {
            return current;
        }
    }
    return nullptr;
}


template<class T>
node<T>* AVLtree<T>::gelgolLL(node<T>* head) {
    node<T>* newHead = head->left;
    head->left = newHead->right;
    newHead->right = head;

    int leftHeight = 0;
    int rightHeight = 0;

    if (head->left) {
        leftHeight = head->left->height;
    }
    if (head->right) {
        rightHeight = head->right->height;
    }
    head->height = max(leftHeight, rightHeight) + 1;

    leftHeight = 0;
    rightHeight = 0;

    if (newHead->left) {
        leftHeight = newHead->left->height;
    }
    if (newHead->right) {
        rightHeight = newHead->right->height;
    }
    newHead->height = max(leftHeight, rightHeight) + 1;

    return newHead;
}



template<class T>
node<T>* AVLtree<T>::gelgolRR(node<T>* head) {
    node<T>* newHead = head->right;
    head->right = newHead->left;
    newHead->left = head;

    int leftHeightHead = 0;
    int rightHeightHead = 0;

    if (head->left != nullptr) {
        leftHeightHead = head->left->height;
    } else {
        leftHeightHead = 0;
    }

    if (head->right != nullptr) {
        rightHeightHead = head->right->height;
    } else {
        rightHeightHead = 0;
    }

    head->height = max(leftHeightHead, rightHeightHead) + 1;

    int leftHeightNewHead = 0;
    int rightHeightNewHead = 0;

    if (newHead->left != nullptr) {
        leftHeightNewHead = newHead->left->height;
    } else {
        leftHeightNewHead = 0;
    }

    if (newHead->right != nullptr) {
        rightHeightNewHead = newHead->right->height;
    } else {
        rightHeightNewHead = 0;
    }

    newHead->height = max(leftHeightNewHead, rightHeightNewHead) + 1;

    return newHead;
}

template<class T>
node<T>* AVLtree<T>::findMin(node<T>* head) const {
    node<T>* current = head;
    while (current->left != nullptr) {
        current = current->left;
    }
    return current;
}

template<class T>
node<T>* AVLtree<T>::findMax(node<T>* head) const {
    node<T>* current = head;
    while (current->right != nullptr) {
        current = current->right;
    }
    return current;
}

template<class T>
void AVLtree<T>::checkMax(int key, int id) {
    if (head != nullptr) {
        if (this->maxData == key && this->maxId == id) {
            node<T>* toget = findMax(this->head);
            this->maxData = toget->key.getKey();
            this->maxId = toget->key.getId();
        }
    }
}

template<class T>
void AVLtree<T>::checkMin(int key, int id) {
    if (head != nullptr) {
        if (this->minData == key && this->minId == id) {
            node<T>* toget = findMin(this->head);
            this->minData = toget->key.getKey();
            this->minId = toget->key.getId();
        }
    }
}

template<class T>
void AVLtree<T>::remove(T value, int key, int id) {
    pair a(key, id);
    this->head = removeHelp(this->head, a);
    checkMax(key, id);
    checkMin(key, id);
}

template<class T>
node<T>* AVLtree<T>::removeHelp(node<T>* head, pair key) {
    if (head == nullptr) {
        return head;
    }
    if (key < head->key)
    {
        head->left = removeHelp(head->left, key);
    }
    else if (key > head->key)
    {
        head->right = removeHelp(head->right, key);
    }
    else
    {
        if (head->left == nullptr || head->right == nullptr) {
            node<T>* temp;
            if (head->left != nullptr) {
                temp = head->left;
            } else {
                temp = head->right;
            }

            if (temp == nullptr) {
                temp = head;
                head = nullptr;
            } else {
                *head = *temp;
            }
            delete temp;
        } else {
            node<T>* temp = findMin(head->right);
            head->key = temp->key;
            head->value = temp->value;
            head->right = removeHelp(head->right, temp->key);
        }
        this->sizeOfTree--;
    }
    if (head == nullptr) {
        return head;
    }

    if (head->left != nullptr && head->right != nullptr)
    {
        if (head->left->height > head->right->height)
        {
            head->height = 1 + head->left->height;
        }
        else
        {
            head->height = 1 + head->right->height;
        }
    }
    else if (head->left != nullptr)
    {
        head->height = 1 + head->left->height;
    }
    else if (head->right != nullptr) {
        head->height = 1 + head->right->height;
    }
    else {
        head->height = 1;
    }

    int balance = calculateBF(head);

    if (balance > 1 && calculateBF(head->left) >= 0) {
        return gelgolLL(head);
    }
    if (balance > 1 && calculateBF(head->left) < 0) {
        head->left = gelgolRR(head->left);
        return gelgolLL(head);
    }
    if (balance < -1 && calculateBF(head->right) <= 0) {
        return gelgolRR(head);
    }
    if (balance < -1 && calculateBF(head->right) > 0) {
        head->right = gelgolLL(head->right);
        return gelgolRR(head);
    }
    return head;
}

template<class T>
int AVLtree<T>::getMax() const {
    return this->maxData;
}

template<class T>
int AVLtree<T>::getMin() const {
    return this->minData;
}

template<class T>
void AVLtree<T>::printTree(node<T>* node1, int space) const {
    if (node1 == nullptr) return;
    space += 10;
    printTree(node1->right, space);
    std::cout << std::endl;
    for (int i = 10; i < space; i++) {
        std::cout << " ";
    }
    std::cout << node1->key.getKey() << " (ID: " << node1->key.getId() << ")" << std::endl;
    printTree(node1->left, space);
}

template<class T>
void AVLtree<T>::print() const {
    printTree(this->head, 0);
}
/*
#include "memory"
int main()
{
    std::shared_ptr<int>s(new int (10));
    AVLtree<std::shared_ptr<int>>tree= AVLtree<std::shared_ptr<int>>();
    tree.insert(s,10,10);
    std::shared_ptr<int>s2(new int (5));
    //std::cout<<"gothere"<<std::endl;
    tree.insert(s2,5,5);
    std::shared_ptr<int>s3(new int (7));
    //std::cout<<"gothere"<<std::endl;
    tree.insert(s3,7,7);
    std::shared_ptr<int>s4(new int (12));
    //std::cout<<"gothere"<<std::endl;
    tree.insert(s4,12,12);
    // tree.remove(s4,12,12);
    std::shared_ptr<int>s5(new int (20));
    tree.insert(s5,20,20);
    std::shared_ptr<int>s6(new int (25));
    tree.insert(s6,25,25);
    std::cout<<tree.getMaxId()<<std::endl;


    //std::cout<<"gothere"<<std::endl;
    tree.print();

}
 */
#endif //DS1_AVLTREE_H