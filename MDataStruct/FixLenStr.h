//
// Created by xOx on 2023/4/24.
//

#ifndef TESTME_FIXSTR_H
#define TESTME_FIXSTR_H

#include <stdexcept>
#include <cstdint>
#include <iostream>
#include <algorithm>



template <typename Tp,std::size_t FixLen = 16>
class FixLenStr
{

public:

    using LenTp = typename std::make_unsigned<Tp>::type ;
    explicit FixLenStr():mSize(0)
    { }

    FixLenStr(const Tp *str, LenTp len);

    ~FixLenStr() = default;
    Tp& operator[](LenTp pos);
    FixLenStr<Tp, FixLen>& operator=(const FixLenStr<Tp,FixLen> &rhs);

    bool push(const Tp &val);
    bool pop();
    void clear();



    uint8_t Size() const
    { return  mSize; }

private:
    bool bound_check(LenTp pos) const;

    Tp mStr[FixLen]={};
    LenTp mSize{};
};
template <typename Tp, std::size_t FixLen>
Tp& FixLenStr<Tp, FixLen>::operator[](FixLenStr<Tp, FixLen>::LenTp pos)
{
    if (!bound_check(pos)) {
        exit(-1);
        // throw out_of_range("pos");
    }
    return mStr[pos];
}
template <typename Tp, std::size_t FixLen>
bool FixLenStr<Tp, FixLen>::bound_check(FixLenStr<Tp, FixLen>::LenTp pos) const
{
    return pos  < FixLen;
}


template <typename Tp, std::size_t FixLen>
bool FixLenStr<Tp, FixLen>::push(const Tp &val)
{
    if (!bound_check(mSize + 1))
        return false;

    mStr[mSize++] = val;
    return true;
}

template <typename Tp, std::size_t FixLen>
void FixLenStr<Tp, FixLen>::clear()
{
    mSize = 0;
}

template<typename Tp, std::size_t FixLen>
FixLenStr<Tp, FixLen> &FixLenStr<Tp, FixLen>::operator=(const FixLenStr<Tp, FixLen> &rhs)
{
    if (rhs != *this) {

        mSize = rhs.mSize;
        if (rhs.mSize) {
            memcpy(mStr, rhs.mStr, mSize * sizeof(Tp));
        }
    }
    return *this;
}

template<typename Tp, std::size_t FixLen>
bool FixLenStr<Tp, FixLen>::pop()
{
    if (!mSize)
        return false;
    --mSize;
    return true;
}

template<typename Tp, std::size_t FixLen>
FixLenStr<Tp, FixLen>::FixLenStr(const Tp *str, FixLenStr<Tp, FixLen>::LenTp len)
{
    mSize = std::min(len, FixLen);
    memcpy(mStr, str, mSize * sizeof(Tp));
}

template<typename Tp, std::size_t FixLen>
std::ostream &operator<<(std::ostream &ostrm, FixLenStr<Tp, FixLen> &mFstr)
{
    for (uint8_t i = 0; i < mFstr.Size();++i)
        ostrm << mFstr[i];


    return ostrm;
}




#endif //TESTME_FIXSTR_H
