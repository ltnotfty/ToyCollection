//
// Created by xOx on 2023/4/11.
//

#ifndef TESTME_MSLINKEDLIST_H
#define TESTME_MSLINKEDLIST_H

#include <cstdint>
#include <iostream>


template<typename T>
class MSLinkedList
{
public:
    explicit MSLinkedList(bool tailIns = false):M_tailInsert(tailIns),M_head(nullptr)
    {}

    ~MSLinkedList()
    {
        if (M_head) {
            delete M_head;
        }
        M_head = nullptr;
    }
    bool Insert(const T &data);
    bool Delete(const T &data);
    bool Find(const T &data);

    struct SLinkedNode * Find(const T &data) const;

    void echoAll() const;

    bool isEmpty() const
    { return M_head == nullptr; }

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
    SLinkedNode *M_head;
};

template<typename T>
bool MSLinkedList<T>::Delete(const T &data)
{
    if (!M_head)
        return false;


    MSLinkedList<T>::SLinkedNode *trav = M_head;
    if (M_head->data == data) {
        M_head = M_head->next;

        trav->next = nullptr;
        delete trav;
        return true;
    }

    while(trav->next && trav->next->data != data)
        trav = trav->next;

    if (!trav->next)
        return false;

    MSLinkedList<T>::SLinkedNode *target = trav->next;
    trav->next = target->next;
    target->next = nullptr;
    delete target;

    return true;
}
template<typename  T>
bool MSLinkedList<T>::Insert(const T &data)
{

    if (Find(data))
        return false;

    auto *newNode = new MSLinkedList::SLinkedNode(data);
    if (!M_head) {
        M_head = newNode;
        return true;
    }

    if (M_tailInsert) {
        MSLinkedList<T>::SLinkedNode *cur = M_head;
        while (cur->next)
             cur = cur->next;
        cur->next = newNode;
    }
    else {
        newNode->next = M_head;
        M_head = newNode;
    }

    return true;
}

template<typename  T>
struct SLinkedNode * MSLinkedList<T>::Find(const T &data) const
{
    MSLinkedList<T>::SLinkedNode *ret = M_head;
    if (ret) {
        while (ret && ret->data != data)
            ret = ret->next;
    }

    return ret;
}

template<typename T>
void MSLinkedList<T>::echoAll() const
{
    if (!M_head)
        return ;
    MSLinkedList<T>::SLinkedNode *cur = M_head;

    for ( ; cur ; cur = cur->next) {
        if (cur != M_head)
            std::cout << " -> ";
        std::cout << cur->data;
    }
    std::cout << std::endl;
}

template<typename T>
bool MSLinkedList<T>::Find(const T &data)
{
    MSLinkedList<T>::SLinkedNode *cur = M_head;
    if (!cur)
        return false;


    while (cur && cur->data != data)
        cur = cur->next;

    return cur && cur->data == data;
}


#endif //TESTME_MSLINKEDLIST_H
