//
// Created by xOx on 2023/4/12.
//

#ifndef TESTME_MSHLINKEDLIST_H
#define TESTME_MSHLINKEDLIST_H


#include <cstdint>
#include <iostream>


template<typename T>
class MSHLinkedList
{
public:
    explicit MSHLinkedList(bool tailIns = false):M_tailInsert(tailIns),M_head(0)
    {}

    ~MSHLinkedList()
    {
        if (M_head.next) {
            delete M_head.next;
        }
        M_head.next = nullptr;
    }
    bool Insert(const T &data);
    bool Delete(const T &data);
    bool Find(const T &data);

    struct SLinkedNode * Find(const T &data) const;

    void echoAll() const;

    bool isEmpty() const
    { return M_head.next == nullptr; }

private:


    struct SLinkedNode {
        explicit SLinkedNode(const T &data_):data(data_),next(nullptr)
        {}
        ~SLinkedNode()
        {
            if (next)
            {
                delete next;
                next = nullptr;
            }
        }
        T data;
        SLinkedNode *next;
    };
    bool M_tailInsert;
    SLinkedNode M_head;
};

template<typename T>
bool MSHLinkedList<T>::Delete(const T &data)
{

    MSHLinkedList<T>::SLinkedNode *trav = M_head;
    if (!trav)
        return false;

    while(trav->next && trav->next->data != data)
        trav = trav->next;

    if (!trav->next)
        return false;

    MSHLinkedList<T>::SLinkedNode *target = trav->next;
    trav->next = target->next;
    target->next = nullptr;
    delete target;

    return true;
}
template<typename  T>
bool MSHLinkedList<T>::Insert(const T &data)
{

    if (Find(data))
        return false;

    MSHLinkedList<T>::SLinkedNode *newNode = new MSHLinkedList::SLinkedNode(data);
    if (M_tailInsert) {
        MSHLinkedList<T>::SLinkedNode *cur = M_head;
        while (cur->next)
            cur = cur->next;
        cur->next = newNode;
    }
    else {
        newNode->next = M_head.next;
        M_head.next = newNode;
    }

    return true;
}

template<typename  T>
struct SLinkedNode * MSHLinkedList<T>::Find(const T &data) const
{
    MSHLinkedList<T>::SLinkedNode *ret = M_head;

    while (ret->next && ret->next->data != data)
        ret = ret->next;

    return ret->next;
}

template<typename T>
void MSHLinkedList<T>::echoAll() const
{
    if (!M_head)
        return ;
    MSHLinkedList<T>::SLinkedNode *cur = M_head;

    for ( ; cur->next ; cur = cur->next) {
        if (cur != M_head)
            std::cout << " -> ";
        std::cout << cur->next->data;
    }
    std::cout << std::endl;
}

template<typename T>
bool MSHLinkedList<T>::Find(const T &data)
{
    MSHLinkedList<T>::SLinkedNode *cur = M_head;

    while (cur->next && cur->next->data != data)
        cur = cur->next;

    return cur->next && cur->next->data == data;
}
#endif //TESTME_MSHLINKEDLIST_H
