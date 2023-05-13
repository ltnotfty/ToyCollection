//
// Created by xOx on 2023/4/28.
//

#ifndef TESTME_MBITSET_H
#define TESTME_MBITSET_H



template <std::size_t bitNum = 16>
class MBitSet
{
public:
    explicit MBitSet() = default;

    ~MBitSet() = default;

    MBitSet(const MBitSet<bitNum> &v)
    {
        if (*this != v)
            memcpy(this->bitSet, v.bitSet, sizeof(bitSet));
    }

    MBitSet& operator=(const MBitSet<bitNum> &v)
    {
        if (*this != v) {
            memcpy(this->bitSet, v.bitSet, sizeof(bitSet));
        }
        return *this;
    }


    bool isEmpty() const
    {
        uint8_t len = (bitNum + 7)/8;
        for (uint8_t i = 0;i < len; ++i)
            if (bitSet[i])
                return false;
        return true;
    }

    bool operator[](uint8_t pos);
    void reset();

    void setPos(uint8_t pos, bool isTrue);
    bool getPos(uint8_t pos)  const;

    void setPos(uint8_t pos);
    void unsetPos(uint8_t pos);



private:
    bool boundCheck(uint8_t pos) const;
    uint8_t bitSet[(bitNum + 7)/8];

};

template<std::size_t bitNum>
bool MBitSet<bitNum>::boundCheck(uint8_t pos) const
{
    return pos < bitNum;
}

template<std::size_t bitNum>
void MBitSet<bitNum>::setPos(uint8_t pos, bool isTrue)
{
    if (!boundCheck(pos))
        return ;

    if (isTrue)
        setPos(pos);
    else
        unsetPos(pos);
}

template<std::size_t bitNum>
bool MBitSet<bitNum>::operator[](uint8_t pos)
{
    if (getPos(pos))
        return true;
    return false;
}

template<std::size_t bitNum>
void MBitSet<bitNum>::reset()
{
    memset(bitSet, 0, sizeof(bitSet));
}

template<std::size_t bitNum>
bool MBitSet<bitNum>::getPos(uint8_t pos) const
{
    if (!boundCheck(pos))
        return false;

    uint8_t index = pos / 8;
    uint8_t offset = pos - index * 8;
    uint v = 1 << offset;

    return v & bitSet[index];
}

template<std::size_t bitNum>
void MBitSet<bitNum>::setPos(uint8_t pos)
{
    if (!boundCheck(pos))
        return;
    uint8_t idx = pos / 8;
    uint8_t ofs = pos - idx * 8;
    uint8_t v = 1 << ofs;

    bitSet[idx] |= v;

}

template<std::size_t bitNum>
void MBitSet<bitNum>::unsetPos(uint8_t pos)
{
    if (!boundCheck(pos))
        return;
    uint8_t idx = pos / 8;
    uint8_t ofs = pos - idx * 8;
    uint8_t v = 1 << ofs;

    bitSet[idx] &= (~v);

}

#endif //TESTME_MBITSET_H
