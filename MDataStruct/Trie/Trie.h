//
// Created by xOx on 2023/4/15.
//

#ifndef TESTME_TRIE_H
#define TESTME_TRIE_H


#include <cstdint>
#include <string>


#include "TrieNode.h"

#define CHAR_SET_NUM 256

template<typename T>
class Trie
{
public:


    explicit Trie(bool isEnd_ = false);
    ~Trie();


    void operator=(const Trie &) = delete;
    Trie(const Trie &) = delete;



//    void print_all() const;
    bool insert(const T *str, std::size_t len);
    bool find(const T *str, std::size_t len);

    bool del(const T *str,std::size_t len);

    bool startWith(const T *str, std::size_t len);

    void echoAll();


    static std::size_t getIdx(T val)
    { return val - 'a';}

private:

    void echo_aux( gNode<T> *rootNode, std::string &str);
    gNode<T>* find_aux(const T *str, std::size_t len);
    bool del_aux(gNode<T> *rootNode, const T *str, std::size_t len);

    gNode<T> root;
};

template<typename T >

Trie<T>::Trie(bool isEnd_)
{
    root.setIsEnd(isEnd_);
    for (int i = 0; i < 256; ++i)
        root.set_node(i, nullptr);

}
template<typename T>
Trie<T>::~Trie()
{
}



template<typename T>
bool Trie<T>::insert(const T *str, std::size_t len)
{
    gNode<T> *cur = &root;
    gNode<T> *nxt = nullptr;

    bool isNew = false;
    for (std::size_t i = 0;i < len; ++i) {


        // there is no son, new one
        nxt = (gNode<T> *) cur->getSonOf(str[i]) ;
        if ( !nxt) {

            nxt = new gNode<T>(i + 1 == len);
            cur->set_node(str[i], (iNode<T> *) nxt);
            isNew = true;
        }

        // if  prefix exists, but no isEnd flag do it
        if (i + 1 == len)
            nxt->setIsEnd(true);

        cur = nxt;
    }

    return isNew;
}

template<typename T>
bool Trie<T>::find(const T *str, std::size_t len)
{
    gNode<T> *lstNode = find_aux(str, len);
    return lstNode && lstNode->isEnd;
}

template<typename T>
bool Trie<T>::startWith(const T *str, std::size_t len)
{
    return find_aux(str, len) != nullptr;
}

template<typename T>
gNode<T> *Trie<T>::find_aux(const T *str, std::size_t len)
{

    gNode<T> *cur = &root;
    gNode<T> *nxt = nullptr;


    for (std::size_t i = 0;i < len; ++i) {
        nxt = (gNode<T> *) ( cur->getSonOf(str[i]) );
        if (!nxt)
            return nullptr;

        cur = nxt;
    }

    return cur;
}

template<typename T>
bool Trie<T>::del(const T *str, std::size_t len) {

    gNode<T> * hPar = find_aux(str, len);
    if (!hPar)
        return false;


    del_aux(&this->root, str, len);

    return true;
}

template<typename T>
bool Trie<T>::del_aux(gNode<T> *rootNode, const T *str, std::size_t len)
{

    if (!rootNode || !str || !len)
        return false;

    std::size_t sNum = rootNode->sonNum();
    if (!sNum)
        return false;

    iNode<T> *nxt = rootNode->getSonOf(str[0]);
    if (!nxt)
        return false;


    auto *finalSon = (gNode<T>*) (nxt);
    if (len == 1)
    {
        if (!finalSon->sonNum())
        {
            delete finalSon;
            rootNode->set_node(str[0], nullptr);
            return !rootNode->getIsEnd() && rootNode->sonNum() == 0 ;
        }
        else
        {
            finalSon->setIsEnd(false);
            return false;
        }
    }


    bool needDel = del_aux((gNode<T> *)(finalSon), str + 1, len - 1);
    if (needDel)
    {
        delete finalSon;
        rootNode->set_node(str[0], nullptr);
    }


    return rootNode->sonNum() == 0 && !rootNode->getIsEnd();

}

template<typename T>
void Trie<T>::echoAll()
{

    std::cout << "here all rule\n";
    std::string tmpStr;

    echo_aux( &root, tmpStr);
}

template<typename T>
void Trie<T>::echo_aux(gNode<T> *rootNode, std::string &str)
{

    if (!rootNode)
        return ;

    if (rootNode->getIsEnd()) {
        std::cout << str << std::endl;
    }

    gNode<T> *tmpNode = nullptr;
    for (int i = 0; i < CHAR_SET_NUM; ++i)
    {
        // tmpNode = (decltype(tmpNode)) (nullptr);
        if (rootNode->getSonOf(i))

        tmpNode = (decltype(tmpNode))( rootNode->getSonOf(i) );
        if (tmpNode)
        {
            str.push_back(i);
            echo_aux(tmpNode, str);
            str.pop_back();
        }
        tmpNode = nullptr;
    }

    return ;
}



#endif //TESTME_TRIE_H

