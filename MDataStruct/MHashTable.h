//
// Created by xOx on 2023/4/11.
//

#ifndef TESTME_MHASHTABLE_H
#define TESTME_MHASHTABLE_H

#include <cstdint>
#include <iostream>

#include "MSLinkedList.h"



constexpr static uint32_t primeTable[26] =
{
        53, 97, 193, 389, 769, 1543, 3079, 6151, 12289,
        24593, 49157, 98317,196613,	393241,	786433, 1572869,
        3145739, 6291469,12582917,25165843,50331653,100663319,
        201326611,402653189,805306457,1610612741
};

template<typename T>
class MHashTable
{
public:
    explicit MHashTable(std::size_t tblSz):M_TblSz(0),M_EleCnt(0),M_Tbl(nullptr)
    {
       InitializeTable(tblSz);
    }
    ~MHashTable()
    {
        DestroyTable();
    }

    MHashTable& operator=(const MHashTable&) = delete;
    MHashTable(const MHashTable<T> &) =delete;

    bool Insert(const T& key);
    bool Delete(const T& key);



    uint32_t getPrimeSz(std::size_t tblSz);


    bool Find(const T &val) const ;

    void echoAll() const;
private:
    MSLinkedList<T> * InitializeTable(std::size_t TblSz);

    std::size_t getPos(const T &val) const;

    void DestroyTable() ;


    std::size_t M_TblSz;
    std::size_t M_EleCnt;

    MSLinkedList<T> *M_Tbl;
};

template<typename T>
MSLinkedList<T> *MHashTable<T>::InitializeTable(std::size_t TblSz)
{
    M_TblSz = this->getPrimeSz(TblSz);
    M_Tbl = new MSLinkedList<T>[M_TblSz];

    return M_Tbl;
}

template<typename T>
uint32_t MHashTable<T>::getPrimeSz(std::size_t tblSz)
{
    uint32_t ret;

    for (int i = 0; i < 26; ++i) {
        if (tblSz <= primeTable[i])
            return primeTable[i];
    }

    return primeTable[25];
}

template<typename T>
void MHashTable<T>::DestroyTable()
{
    if (M_Tbl != nullptr)
        delete[] M_Tbl;

    M_TblSz = 0;
    M_Tbl = nullptr;
}

template<typename T>
bool MHashTable<T>::Insert(const T &key)
{
    if (!M_Tbl)
        return false;

    bool insOk = M_Tbl[getPos(key)].Insert(key);
    if (insOk)
        ++M_EleCnt;

    return insOk;
}

template<typename T>
std::size_t MHashTable<T>::getPos(const T& val) const
{ return val % M_TblSz; }

template<typename T>
bool MHashTable<T>::Find(const T &val) const
{
    return M_Tbl[getPos(val)].Find(val) ;
}

template<typename T>
bool MHashTable<T>::Delete(const T &key)
{
    bool ret =  M_Tbl[getPos(key)].Delete(key);
    if (ret)
        --M_EleCnt;

    return ret;
}

template<typename T>
void MHashTable<T>::echoAll() const
{


    for (int i = 0; i < M_TblSz; ++i) {
        if (!M_Tbl[i].isEmpty()) {
            std::cout << "Key" << i << ": ";
            M_Tbl[i].echoAll();
        }
    }

}

#endif //TESTME_MHASHTABLE_H
