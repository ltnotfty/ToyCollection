//
// Created by xOx on 2023/3/8.
//

#ifndef TESTME_TRIE_H
#define TESTME_TRIE_H

#include <cstdint>


#define CHAR_SET_NUM 26


template<typename T>
class Trie
{
public:
    explicit Trie(bool isEnd_ = false);
    ~Trie()
    {
        for (auto &v:son)
        {
            delete v;
            v = nullptr;
        }

    }
    std::size_t sonNum() const
    {
        std::size_t ret = 0;
        for (auto &v:son)
            if (v)
                ++ret;
        return ret;
    }

    void operator=(const Trie &) = delete;
    Trie(const Trie &) = delete;


//    void print_all() const;
    bool insert(const T *str, std::size_t len);
    bool find(const T *str, std::size_t len);

    bool del(const T *str,std::size_t len);

    bool startWith(const T *str, std::size_t len);

    void echoAll() const;


    static std::size_t getIdx(T val)
    { return val - 'a';}

private:


    void echo_aux(Trie<T> *rootNode, std::string &str) const;
    Trie<T>* find_aux(const T *str, std::size_t len);
    bool del_aux(Trie<T> *rootNode, const T *str, std::size_t len);


    bool isEnd;
    Trie<T> *son[CHAR_SET_NUM];
};

template<typename T >
Trie<T>::Trie(bool isEnd_):isEnd(isEnd_)
{
    for (auto &v:son)
        v = nullptr;
}

template<typename T>
bool Trie<T>::insert(const T *str, std::size_t len)
{
    Trie<T> *cur = this;
    std::size_t idx;
    bool isNew = false;

    for (std::size_t i = 0;i < len; ++i)
    {
        idx = Trie<T>::getIdx(str[i]);

        if (idx >= CHAR_SET_NUM)
        {
            std::cout << "Trie Index Out Of Range" << std::endl;
            exit(EXIT_FAILURE);
        }


        if ( !cur->son[idx])
        {
            cur->son[idx] = new Trie<T>(i + 1 == len);
            isNew = true;
        }

        if (i == len - 1)
        {
            cur->son[idx]->isEnd = true;
        }

        cur = cur->son[idx];
    }

    return isNew;
}

template<typename T>
bool Trie<T>::find(const T *str, std::size_t len)
{
    Trie<T> *lstNode = find_aux(str, len);
    return lstNode && lstNode->isEnd;
}

template<typename T>
bool Trie<T>::startWith(const T *str, std::size_t len)
{
    return find_aux(str, len) != nullptr;
}

template<typename T>
Trie<T> *Trie<T>::find_aux(const T *str, std::size_t len)
{

    Trie<T> *cur = this;
    std::size_t idx;


    for (std::size_t i = 0;i < len; ++i)
    {
        idx = Trie<T>::getIdx(str[i]);
        if (!cur->son[idx])
        {
            return nullptr;
        }
        if (i + 1 != len)
            cur = cur->son[idx];
    }

    return cur;
}

template<typename T>
bool Trie<T>::del(const T *str, std::size_t len)
{

    Trie<T> * hPar = find_aux(str, len);
    if (!hPar)
        return false;


    bool need_del = del_aux(this, str, len);
    if (need_del) {
        delete this->son[getIdx(str[0])];
        this->son[getIdx(str[0])] = nullptr;
    }

    return true;
}

template<typename T>
bool Trie<T>::del_aux(Trie<T> *rootNode, const T *str, std::size_t len)
{

    if (!rootNode || !str || !len)
        return false;

    std::size_t sNum = rootNode->sonNum();
    if (!sNum)
        return false;
    std::size_t idx = Trie<T>::getIdx(str[0]);
    if (!rootNode->son[idx])
        return false;


    if (len == 1) {
        Trie<T> *finalSon = rootNode->son[idx];
        if (!finalSon->sonNum()) {
            delete finalSon;
            rootNode->son[idx] = nullptr;
            return !rootNode->isEnd && rootNode->sonNum() == 0 ;
        }
        else {
            finalSon->isEnd = false;
            return false;
        }
    }

    bool needDel = del_aux(rootNode->son[idx], str + 1, len - 1);
    if (needDel) {
        delete rootNode->son[idx];
        rootNode->son[idx] = nullptr;
    }


    return rootNode->sonNum() == 0 && !isEnd;

}

template<typename T>
void Trie<T>::echoAll() const
{

    std::cout << "here all rule\n";
    std::string tmpStr;

    echo_aux(this, tmpStr);
}

template<typename T>
void Trie<T>::echo_aux(Trie<T> *rootNode, std::string &str) const
{

    if (!rootNode)
        return ;

    if (rootNode->isEnd)
        std::cout << str << std::endl;

    for (int i = 0; i < CHAR_SET_NUM; ++i)
    {
        if (rootNode->son[i])
        {
            str.push_back('a' + i);
            echo_aux(rootNode->son[i], str);
            str.pop_back();
        }
    }

    return ;
}


#endif //TESTME_TRIE_H
