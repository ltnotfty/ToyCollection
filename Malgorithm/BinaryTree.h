//
// Created by xOx on 2023/3/9.
//

#ifndef TESTME_BINARYTREE_H
#define TESTME_BINARYTREE_H

#include <stack>
#include <queue>
#include <iostream>




template<typename T>
class binary_tree
{

public:
    struct binary_tree_node
    {
        explicit binary_tree_node(T data):data_(data),left(nullptr),right(nullptr)
        { }
        ~binary_tree_node()
        {
            if (left)
            {
                delete left;
                left = nullptr;
            }
            if (right)
            {
                delete right;
                right = nullptr;
            }
        }
        void echoNode() const
        { std::cout << this->data_ << " "; }




        bool isLeafNode() const
        { return left == nullptr && right == nullptr; }

        void operator=(const binary_tree_node & ) = delete;
        binary_tree_node(const binary_tree_node & ) = delete;

        T data_;
        struct binary_tree_node *left;
        struct binary_tree_node *right;
    };

    explicit binary_tree():rootNode_(nullptr)
    { }
    ~binary_tree()
    {
        if (rootNode_)
        {
            delete rootNode_;
            rootNode_ = nullptr;
        }
    }


    void push_back(binary_tree_node *curNode);
    void pop();


    void prevTrav();
    void inodTrav();
    void postTrav();
    void levelTrav();

    void prevTrav_aux(binary_tree_node *rootNode);
    void inodTrav_aux(binary_tree_node *rootNode);
    void postTrav_aux(binary_tree_node *rootNode);

private:

    binary_tree_node* getInsertPos();
    binary_tree_node* getDeletePos();

    binary_tree_node *rootNode_;
};

template<typename T>
void binary_tree<T>::push_back(binary_tree::binary_tree_node *curNode)
{
    if (nullptr == rootNode_)
    {
        rootNode_ = curNode;
        return;
    }

    binary_tree_node *insertNode = getInsertPos();
    if (!insertNode->left)
        insertNode->left = curNode;
    else
        insertNode->right = curNode;
}

template<typename T>
typename binary_tree<T>::binary_tree_node *binary_tree<T>::getInsertPos()
{
    std::queue<binary_tree_node *> prevQ;
    prevQ.push(rootNode_);
    binary_tree_node *topNode = prevQ.front();

    while (topNode->left && topNode->right)
    {
        prevQ.pop();
        prevQ.push(topNode->left);
        prevQ.push(topNode->right);

        topNode = prevQ.front();
    }

    return topNode;
}

template<typename T>
typename binary_tree<T>::binary_tree_node *binary_tree<T>::getDeletePos()
{
    std::queue<binary_tree_node *> prevQ;
    prevQ.push(rootNode_);

    binary_tree_node *topNode = prevQ.front();
    while (topNode->right)
    {
        prevQ.pop();
        prevQ.push(topNode->left);
        prevQ.push(topNode->right);

        if (prevQ.front()->isLeafNode())
            break;

        topNode = prevQ.front();
    }

    return topNode;
}

template<typename T>
void binary_tree<T>::pop()
{
    if (rootNode_ == nullptr)
        return;
    if (!rootNode_->left&& !rootNode_->right)
    {
        delete rootNode_;
        rootNode_ = nullptr;
    }


    binary_tree_node *delNode = getDeletePos();
    if (delNode->right)
    {
        delete delNode->right;
        delNode->right = nullptr;
    }
    else if (delNode->left)
    {
        delete delNode->left;
        delNode->left = nullptr;
    }
}

template<typename T>
void binary_tree<T>::prevTrav()
{
    prevTrav_aux(rootNode_);
}

template<typename T>
void binary_tree<T>::inodTrav() {
    inodTrav_aux(rootNode_);
}

template<typename T>
void binary_tree<T>::postTrav() {
    postTrav_aux(rootNode_);
}

template<typename T>
void binary_tree<T>::levelTrav()
{
    if (!rootNode_)
        return;
    std::queue<binary_tree_node*> nodeQ;
    nodeQ.push(rootNode_);

    binary_tree_node *topNode;
    while (!nodeQ.empty())
    {
        topNode = nodeQ.front();
        nodeQ.pop();

        topNode->echoNode();
        if (topNode->left)
            nodeQ.push(topNode->left);
        if (topNode->right)
            nodeQ.push(topNode->right);
    }

}

template<typename T>
void binary_tree<T>::prevTrav_aux(binary_tree::binary_tree_node *rootNode) {
    /*if (!rootNode)
        return;
    rootNode->echoNode();
    prevTrav_aux(rootNode->left);
    prevTrav_aux(rootNode->right);*/

    std::stack<binary_tree_node *> nodeStq;
    if (rootNode_)
    {
        nodeStq.push(rootNode_);
    }


    binary_tree_node *inNode = nullptr;
    while (!nodeStq.empty() )
    {
        binary_tree_node *topNode = nodeStq.top();
        nodeStq.pop();

        if (topNode)
        {
            topNode->echoNode();
            if (topNode->right)
                nodeStq.push(topNode->right);
            if (topNode->left)
                nodeStq.push(topNode->left);
        }


    }

}



template<typename T>
void binary_tree<T>::inodTrav_aux(binary_tree::binary_tree_node *rootNode) {
    /*if (!rootNode)
        return;
    inodTrav_aux(rootNode->left);
    rootNode->echoNode();
    inodTrav_aux(rootNode->right);*/

    std::stack<binary_tree_node *> nodeStq;
    if (rootNode_)
    {
        nodeStq.push(rootNode_);
    }


    binary_tree_node *parentNode = nullptr;

    while (!nodeStq.empty())
    {
        binary_tree_node *topNode = nodeStq.top();

        if (topNode->left && parentNode != topNode)
        {
            parentNode = topNode;
            nodeStq.push(topNode->left);
            continue;
        }
        topNode->echoNode();
        nodeStq.pop();
        if (!nodeStq.empty())
            parentNode = nodeStq.top();
        else
            parentNode = nullptr;

        if (topNode->right)
        {
            nodeStq.push(topNode->right);
        }
    }


}

template<typename T>
void binary_tree<T>::postTrav_aux(binary_tree::binary_tree_node *rootNode)
{

    std::stack<binary_tree_node *> nodeStq;
    if (rootNode_)
    {
        nodeStq.push(rootNode_);
    }


    binary_tree_node *rp;
    binary_tree_node *parentNode;

    while (!nodeStq.empty())
    {
        binary_tree_node *topNode = nodeStq.top();

        if (topNode->left && parentNode != topNode)
        {
            nodeStq.push(topNode->left);
            parentNode = topNode;
            continue;
        }
        else
        {
            if (rp == topNode->right || !topNode->right)
            {
                topNode->echoNode();
                nodeStq.pop();
            }
            else
            {
                nodeStq.push(topNode->right);
                rp = topNode;
            }
        }
    }

}


#endif //TESTME_BINARYTREE_H
