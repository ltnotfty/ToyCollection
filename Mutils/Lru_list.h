//
// Created by xOx on 2023/4/24.
//

#ifndef TESTME_LRU_LIST_H
#define TESTME_LRU_LIST_H

#include <list>
#include <unordered_map>



/// LRU: list + hashMap

template<typename T>
class Lru_list
{

public:
    explicit Lru_list()
    {}

    typedef typename std::list<T>::iterator Lru_ListNode;

    bool push(const T &);
    bool pop();

    void clear();

    bool isEmpty();
    T getLRElement() const;
    std::size_t size() const;


private:
    std::list<T> mList;
    std::unordered_map< T, Lru_ListNode > mListNodeIndex;
 };



template<typename T>
bool Lru_list<T>::push(const T &v)
{

    bool ret = true;
    auto iter = mListNodeIndex.find(v);
    if (iter != mListNodeIndex.end()) {
        mListNodeIndex.erase(iter->first);
        ret = false;
    }

    mList.push_front(v);
    mListNodeIndex[v] = mList.begin();

    return ret;
}

template <typename T>
bool Lru_list<T>::isEmpty()
{
    return mList.empty();
}

template <typename T>
T Lru_list<T>::getLRElement() const
{
    return mList.front();
}
template <typename T>
bool Lru_list<T>::pop()
{
    if (!isEmpty())
        return false;

    mListNodeIndex.erase(mList.back());
    mList.pop_back();
}

template<typename T>
std::size_t Lru_list<T>::size() const
{
    return mList.size();
}

template<typename T>
void Lru_list<T>::clear()
{
    mListNodeIndex.clear();
    mList.clear();
}


#endif //TESTME_LRU_LIST_H
