//
// Created by hussa on 7/14/2024.
//

#ifndef DS1_AVLTREE_H
#define DS1_AVLTREE_H
template<class T>
class node{
    int key;
    T data;
    int height;
    node *left;
    node *right;
public:
    node()=default;
    node(T data,int key);
    ~node();
    void setData(T data);
    T getData()const;
    void setLeft(node *left);
    void setright(node *right);
    node* getleft()const;
    node* getright()const;
    int getHeight()const;
    void setHeight(int height);
    int getKey()const;
};
template<class T>
class AVLtree{
    node<T>* head;
    int sizeOfTree;
    T maxData;
    T minData;
    int max(int first,int second);
    node<T>* insertHelp(node<T>* head,T value,int key);
    node<T>* gelgolLL(node<T>* head);
    node<T>* gelgolRR(node<T>*head);
    int calculateBF(node<T>*head)const;
    node<T>* removeHelp(node<T>* head,T value);
    void checkmax(T value);
    void checkmin(T value);

public:
    AVLtree();
    void insert(T value,int key);
    void remove(T value);
    int size()const;
    node<T>* find(int key)const;
    node<T>* findmin(node<T>* head)const;
    node<T>* findmax(node<T>* head)const;
    T getmax()const;
    T getmin()const;
    ~AVLtree();
};


//
// Created by hussa on 7/1/2024.
//
//node cpp
template<class T>
node<T>::node(T data,int key) {
    this->data=data;
    this->height=1;
    this->left= nullptr;
    this->right= nullptr;
    this->key=key;
}
template<class T>
int node<T>::getKey() const {
    return this->key;
}
template<class T>
node<T>::~node() {
    if (left != nullptr) {
        delete left;
    }
    if (right != nullptr) {
        delete right;
    }
    //delete (&this->data);
}
template<class T>
void node<T>::setLeft(node<T> *left) {
    this->left=left;
}
template<class T>
void node<T>::setright(node<T> *right) {
    this->right=right;
}
template<class T>
node<T> *node<T>::getleft() const {
    return this->left;
}
template<class T>
node<T> *node<T>::getright() const {
    return this->right;
}
template<class T>
void node<T>::setData(T data) {
    this->data=data;
}
template<class T>
T node<T>::getData() const {
    return this->data;
}
template<class T>
int node<T>::getHeight() const {
    if(this== nullptr)return 0;
    return this->height;
}
template<class T>
void node<T>::setHeight(int height) {
    this->height=height;
}




//AVLtree cpp
template<class T>
AVLtree<T>::AVLtree() {
    this->head= nullptr;
    this->sizeOfTree=0;
    this->maxData= T();
    this->minData=T();
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
void AVLtree<T>::insert(T value,int key) {
    ///need to do
    this->head=insertHelp(this->head,value,key);
    if(this->maxData<value)
    {
        this->maxData=value;
    }
    if(this->minData>value)
    {
        this->minData=value;
    }

}
template<class T>
int AVLtree<T>::max(int first, int second) {
    if(first>second)
    {
        return first;
    }
    return second;
}
template<class T>
node<T>* AVLtree<T>::insertHelp(node<T> *head, T value,int key)  {
    if(head== nullptr)
    {
        this->sizeOfTree++;
        head= new node<T>(value,key);
        return head;
    }
    if(value<head->getData())
    {
        head->setLeft(insertHelp(head->getleft(), value,key));
    }
    else if(value>head->getData())
    {
        head->setright(insertHelp(head->getright(), value,key));
    }
    else
    {
        return head;
    }
    head->setHeight(AVLtree<T>::max(head->getleft()->getHeight(),head->getright()->getHeight())+1);
    //need to do gelgol
    if(head!=nullptr) {
        int BF ,BFL,BFR;
        if(head->getleft()!= nullptr) {
            BFL = AVLtree<T>::calculateBF(head->getleft());
        }
        else{
            BFL=0;
        }
        if(head->getright()!= nullptr) {
            BFR = AVLtree<T>::calculateBF(head->getright());
        }
        else{
            BFR=0;
        }
        BF= calculateBF(head);
        if (BF == 2 && BFL >= 0) {
            return AVLtree<T>::gelgolLL(head);
        }
        if (BF == 2 && BFL == -1) {
            head->setLeft(gelgolRR(head->getleft()));
            return gelgolLL(head);
        }
        if (BF == -2 && BFR <= 0) {
            return AVLtree<T>::gelgolRR(head);
        }
        if (BF == -2 && BFR == 1) {
            head->setright(gelgolLL(head->getright()));
            return gelgolRR(head);
        }
    }
    return head;

}
template<class T>
int AVLtree<T>::calculateBF(node<T> *head) const {
    if (head == nullptr) {
        return 0;
    }
    int leftHeight = 0;
    int rightHeight = 0;
    if (head->getleft() != nullptr) {
        leftHeight = head->getleft()->getHeight();
    }
    if (head->getright() != nullptr) {
        rightHeight = head->getright()->getHeight();
    }
    return leftHeight - rightHeight;
}
template<class T>
node<T>* AVLtree<T>::find(int key)const {
    node<T>* current= this->head;
    while(current!= nullptr)
    {
        if(current->getKey()==key)
        {
            return current;
        }
        if (key > current->getKey()) {
            current = current->getright();
        }
        if (key < current->getKey()) {
            current = current->getleft();
        }
    }
    return nullptr;
}
template<class T>
node<T> *AVLtree<T>::gelgolLL(node<T> *head) {
    node<T> *newHead = head->getleft();
    head->setLeft(newHead->getright());
    newHead->setright(head);

    head->setHeight(max(head->getleft()->getHeight(), head->getright()->getHeight()) + 1);
    newHead->setHeight(max(newHead->getleft()->getHeight(), newHead->getright()->getHeight()) + 1);

    return newHead;
}

template<class T>
node<T> *AVLtree<T>::gelgolRR(node<T> *head) {
    node<T> *newHead = head->getright();
    head->setright(newHead->getleft());
    newHead->setLeft(head);

    head->setHeight(max(head->getleft()->getHeight(), head->getright()->getHeight()) + 1);
    newHead->setHeight(max(newHead->getleft()->getHeight(), newHead->getright()->getHeight()) + 1);

    return newHead;
}
template<class T>
node<T> *AVLtree<T>::findmin(node<T>*head) const {
    if (head == nullptr) {
        return nullptr;
    }
    node<T> *tmp=head;
    while(tmp->getleft()!= nullptr)
    {
        tmp=tmp->getleft();
    }
    return tmp;
}
template<class T>
node<T> *AVLtree<T>::findmax(node<T>*head) const {
    if (head == nullptr) {
        return nullptr;
    }
    node<T> *tmp=head;
    while(tmp->getright()!= nullptr)
    {
        tmp=tmp->getright();
    }
    return tmp;
}
template<class T>
void AVLtree<T>::checkmax(T value) {
    if(head!= nullptr) {
        if (this->maxData < value)
        {
            return;
        }
        else if (this->maxData > value)
        {
            return;
        }
        else
        {
            this->maxData = findmax(this->head)->getData();
        }
    }
    else
    {
        this->maxData=T();
    }
}
template<class T>
void AVLtree<T>::checkmin(T value) {
    if(head!= nullptr) {
        if (this->minData < value)
        {
            return;
        }
        else if (this->minData > value)
        {
            return;
        }
        else
        {
            this->minData = findmin(this->head)->getData();
        }
    }
    else
    {
        this->minData=T();
    }
}
template<class T>
T AVLtree<T>::getmin() const {
    return this->minData;
}
template<class T>
void AVLtree<T>::remove(T value) {
    this->head=removeHelp(this->head,value);
    checkmin(value);
    checkmax(value);

}
template<class T>
node<T>* AVLtree<T>::removeHelp(node<T> *head, T value){
    //need to implement this
    if (head == nullptr)
    {
        return head;
    }

    if (value < head->getData())
    {
        head->setLeft(removeHelp(head->getleft(), value));
    }
    else if (value > head->getData())
    {
        head->setright(removeHelp(head->getright(), value));
    }
    else
    {
        if (head->getleft() == nullptr || head->getright() == nullptr)
        {
            node<T>* tmp= nullptr;
            if(head->getleft()!= nullptr){
                tmp=head->getleft();
            }
            if(head->getright()!= nullptr)
            {
                tmp=head->getright();
            }
            if (tmp == nullptr)
            {
                tmp = head;
                head = nullptr;
            }
            else
            {
                *head = *tmp;
            }

            delete tmp;
            sizeOfTree--;
        }
        else
        {
            node<T>* tmp = findmin(head->getright());
            head->setData(tmp->getData());
            head->setright(removeHelp(head->getright(), tmp->getData()));
        }
    }

    if (head == nullptr) {
        return head;
    }
    head->setHeight(max(head->getleft()->getHeight(), head->getright()->getHeight()) + 1);


//gelgol
    if(head!=nullptr) {
        int BF ,BFL,BFR;
        if(head->getleft()!= nullptr) {
            BFL = AVLtree<T>::calculateBF(head->getleft());
        }
        else{
            BFL=0;
        }
        if(head->getright()!= nullptr) {
            BFR = AVLtree<T>::calculateBF(head->getright());
        }
        else{
            BFR=0;
        }
        BF= calculateBF(head);
        if (BF == 2 && BFL >= 0) {
            return AVLtree<T>::gelgolLL(head);
        }
        if (BF == 2 && BFL == -1) {
            head->setLeft(gelgolRR(head->getleft()));
            return gelgolLL(head);
        }
        if (BF == -2 && BFR <= 0) {
            return AVLtree<T>::gelgolRR(head);
        }
        if (BF == -2 && BFR == 1) {
            head->setright(gelgolLL(head->getright()));
            return gelgolRR(head);
        }
    }
    return head;

}
template<class T>
T AVLtree<T>::getmax() const {
    return this->maxData;
}
/*int main()
{
    AVLtree<int> tree;
    tree.insert(5,5);
    tree.insert(10,10);
    tree.insert(15,15);
    tree.insert(5,5);
    tree.insert(16,16);
    tree.insert(17,17);
    tree.insert(1,1);
    tree.insert(2,2);
    tree.insert(2,2);
    tree.insert(2,2);
    tree.insert(2,2);
    tree.insert(0,0);
    for(int i=0;i<1000;i++)
    {
        tree.insert(1000-i,1000-i);
        tree.insert(i,i);
        tree.insert(2*i,2*i);
    }
    std::cout<<"get to here"<<std::endl;
    tree.remove(1998);
    std::cout<<tree.getmax()<<std::endl;
    tree.remove(0);
    std::cout<<tree.getmin()<<std::endl;
    tree.remove(5);
    tree.remove(0);
    tree.remove(15);
    tree.remove(17);
    tree.remove(3);
    tree.remove(2);
    if (tree.find(100)!= nullptr)
    {
        std::cout<<"find"<<std::endl;
    }
    for(int i=1999;i>=0;i--)
        tree.remove(i);

    std::cout<<tree.getmax()<<std::endl;
    std::cout<<"sucsess"<<std::endl;
}*/

#endif //DS1_AVLTREE_H
