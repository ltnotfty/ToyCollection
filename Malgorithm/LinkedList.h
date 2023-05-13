//
// Created by xOx on 2023/3/8.
//

#ifndef TESTME_LINKEDLIST_H
#define TESTME_LINKEDLIST_H

#include <iostream>


template<typename T>
class LinkedList
{
public:

    struct LinkNode
    {
        explicit LinkNode(T data_=0):data(data_),next(nullptr)
        { }
        ~LinkNode()
        {
            delete next;
            next = nullptr;
        }
        void operator=(const LinkNode& ) = delete;
        LinkNode(const LinkNode& ) = delete;

        T data;
        LinkNode *next;
    };
    explicit LinkedList()
    {
        headNode = new LinkNode;
        tailNode = headNode;
    }
    ~LinkedList()
    {
        delete headNode;
        headNode = nullptr;
    }

    void operator=(const LinkedList<T> &) = delete;
    LinkedList<T>(const LinkedList<T> &) = delete;


    void print_all() const;
    void push_back(LinkNode *cur);
    LinkNode* find_val(T val);
    bool del_node(T val);


private:
    LinkNode *headNode;
    LinkNode *tailNode;
};

template<typename T>
void LinkedList<T>::push_back(LinkedList::LinkNode *cur)
{
    tailNode->next = cur;
    tailNode = cur;
}

template<typename T>
typename LinkedList<T>::LinkNode*
LinkedList<T>::find_val(T val)
{
    LinkNode *prev = headNode;
    for ( ; prev->next; prev = prev->next)
    {
        if (prev->next->data == val)
            return prev;
    }
    return nullptr;
}

template<typename T>
bool LinkedList<T>::del_node(T val)
{
    LinkNode *prev = find_val(val);
    LinkNode *cur  = prev->next;

    if (prev)
    {
        prev->next = cur->next;
        cur->next  = nullptr;
        delete cur;
        return true;
    }

    return false;
}

template<typename T>
void LinkedList<T>::print_all() const
{
    LinkedList<T>::LinkNode *cur = headNode->next;
    for ( ; cur; cur = cur->next)
        std::cout << cur->data << "\t";
    std::cout << std::endl;
}


#endif //TESTME_LINKEDLIST_H
