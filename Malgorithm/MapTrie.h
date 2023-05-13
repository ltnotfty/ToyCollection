//
// Created by xOx on 2023/4/7.
//

#ifndef TESTME_MAPTRIE_H
#define TESTME_MAPTRIE_H



#include <iostream>
#include <cstdint>
# include <string>
# include <unordered_map>


#define CHAR_SET_NUM 26


template<typename T>
class MapTrie
{
public:
    explicit MapTrie(bool isEnd_ = false);
    ~MapTrie()
    {
        for (auto &v:son)
        {
            delete v.second;
            v.second = nullptr;
        }

    }
    std::size_t sonNum() const
    {
        return this->son.size();
    }

    void operator=(const MapTrie &) = delete;
    MapTrie(const MapTrie &) = delete;


//    void print_all() const;
    bool insert(const T *str, std::size_t len);
    bool find(const T *str, std::size_t len);

    bool del(const T *str,std::size_t len);

    bool startWith(const T *str, std::size_t len);

    void echoAll() const;


    static std::size_t getIdx(T val)
    { return val;}

private:


    void echo_aux(const MapTrie<T> *rootNode, std::string &str) const;
    MapTrie<T>* find_aux(const T *str, std::size_t len);
    bool del_aux(MapTrie<T> *rootNode, const T *str, std::size_t len);


    bool isEnd;
    std::unordered_map<T, MapTrie<T> * > son;
};

template<typename T >
MapTrie<T>::MapTrie(bool isEnd_):isEnd(isEnd_)
{
}

template<typename T>
bool MapTrie<T>::insert(const T *str, std::size_t len)
{
    MapTrie<T> *cur = this;
    std::size_t idx;
    bool isNew = false;

    for (std::size_t i = 0;i < len; ++i)
    {
        idx = MapTrie<T>::getIdx(str[i]);
        if ( cur->son.find(idx) == cur->son.end())
        {
            cur->son[idx] = new MapTrie<T>(i + 1 == len);
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
bool MapTrie<T>::find(const T *str, std::size_t len)
{
    MapTrie<T> *lstNode = find_aux(str, len);
    return lstNode && lstNode->isEnd;
}

template<typename T>
bool MapTrie<T>::startWith(const T *str, std::size_t len)
{
    return find_aux(str, len) != nullptr;
}

template<typename T>
MapTrie<T> *MapTrie<T>::find_aux(const T *str, std::size_t len)
{

    MapTrie<T> *cur = this;
    std::size_t idx;

    for (std::size_t i = 0;i < len; ++i)
    {
        idx = MapTrie<T>::getIdx(str[i]);

        if (cur->son.find(idx) == cur->son.end())
        {
            return nullptr;
        }
        if (i + 1 != len)
            cur = cur->son[idx];
    }

    return cur;
}

template<typename T>
bool MapTrie<T>::del(const T *str, std::size_t len) {

    MapTrie<T> * hPar = find_aux(str, len);
    if (!hPar)
        return false;


    bool need_del = del_aux(this, str, len);
    if (need_del)
    {
        delete this->son[getIdx(str[0])];
        this->son[getIdx(str[0])] = nullptr;
    }

    return true;
}

template<typename T>
bool MapTrie<T>::del_aux(MapTrie<T> *rootNode, const T *str, std::size_t len)
{

    if (!rootNode || !str || !len)
        return false;

    std::size_t sNum = rootNode->sonNum();
    if (!sNum)
        return false;
    std::size_t idx = MapTrie<T>::getIdx(str[0]);
    if (rootNode->son.find(idx) == rootNode->son.end())
        return false;


    if (len == 1)
    {
        MapTrie<T> *finalSon = rootNode->son[idx];
        if (!finalSon->sonNum())
        {
            delete finalSon;
            rootNode->son[idx] = nullptr;
            return !rootNode->isEnd && rootNode->sonNum() == 0 ;
        }
        else
        {
            finalSon->isEnd = false;
            return false;
        }
    }

    bool needDel = del_aux(rootNode->son[idx], str + 1, len - 1);
    if (needDel)
    {
        delete rootNode->son[idx];
        rootNode->son[idx] = nullptr;
    }


    return rootNode->sonNum() == 0 && !isEnd;

}

template<typename T>
void MapTrie<T>::echoAll() const
{

    std::cout << "here all rule\n";
    std::string tmpStr;

    echo_aux(this, tmpStr);
}

template<typename T>
void MapTrie<T>::echo_aux(const MapTrie<T> *rootNode, std::string &str) const
{

    if (!rootNode)
        return ;

    if (rootNode->isEnd)
        std::cout << str << std::endl;

    for (auto iter = rootNode->son.begin(); iter != rootNode->son.end(); ++iter)
    {
        str.push_back(iter->first);
        echo_aux(iter->second, str);
        str.pop_back();
    }
}

#endif //TESTME_MAPTRIE_H
