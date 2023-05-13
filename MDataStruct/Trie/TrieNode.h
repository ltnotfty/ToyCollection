//
// Created by xOx on 2023/4/15.
//

#ifndef TESTME_TRIENODE_H
#define TESTME_TRIENODE_H



#define ALPHANUM_LIMIT 256
#define COMPRESS_LIMIT  16

#include <iostream>
#include <cstdint>

#include <type_traits>



#include "MDataStruct/MBitset.h"

enum {
    BINNODE = 1,
    WITHDATA = 2,
};
enum nodeType{
    GeneralNodeWithout = 0,
    BinaryNodeWithout = BINNODE,
    GeneralNode       = WITHDATA,
    BinaryNode = BINNODE | WITHDATA,
    InvalidNode,
};




template <typename charT>
class iNode
{
public:
    iNode(bool isEnd_ = false):isEnd(isEnd_)
    {}

    using UcharT = typename std::make_unsigned<charT>::type;
    virtual bool hasSonOf(charT c) = 0;
    virtual iNode<charT> * getSonOf(charT c) = 0;

    virtual enum nodeType getNodeType() const
    {return InvalidNode;}

    virtual UcharT getDataLen() const
    { return 0;}
    virtual const charT * getData();

    virtual void setData(const charT *, UcharT len)
    {return;}
    virtual void setDataLen(UcharT i)
    {
        return;
    }


    virtual iNode<charT> *getFirstSon() const
    { return nullptr; }


    virtual charT findKey(iNode<charT> *val) const
    { return 0;}


    virtual void copyNodeFrom(iNode<charT> *val)
    { return ; }
    virtual void setDataFrom(iNode<charT> *v, const charT *str, UcharT len)
    { return; }

    virtual bool getPos(UcharT pos)
    { return false; }

    virtual void setPos(UcharT pos, bool isTrue = true)
    {return; }


    bool isBinNode() const
    { return getNodeType() & 1;}
    bool isWithData() const
    { return getNodeType() & 2;}


    /// \brief return if node need transform to multi node.
    virtual bool set_node(charT c, iNode<charT> *) = 0;
    virtual void clr_node() = 0;

    virtual bool isPrefixOf(const charT *str, UcharT len) const =0 ;
    virtual bool isMatch(const charT *str, UcharT len) const = 0;

    virtual UcharT sonNum() const
    { return 0;}

    virtual bool isDataEmpty()
    { return true;}

    virtual bool isZombieNode() const
    {
        return !isEnd;
    }





    bool getIsEnd() const
    { return isEnd; }
    void setIsEnd(bool isEnd_)
    { isEnd = isEnd_;}
private:
    bool isEnd;
};

template<typename charT>
const charT *iNode<charT>::getData()
{
    return nullptr;
}

template <typename charT>
class bNode:public iNode<charT>{
public:
    explicit bNode(charT lc = 0, charT rc = 0,
                   iNode<charT> *ls = nullptr, iNode<charT> *rs = nullptr);
    ~bNode();

    bNode(const bNode<charT> &v) = default;
    bNode& operator=(const bNode<charT> &v) = default;

    using UcharT = typename iNode<charT>::UcharT;


    iNode<charT> *getFirstSon() const
    {
        if (lSon)
            return lSon;
        if (rSon)
            return rSon;
        return nullptr;
    }

    bool isZombieNode() const;

    bool hasSonOf(charT c) final;
    iNode<charT> *getSonOf(charT c) final;
    enum nodeType getNodeType() const
    { return BinaryNodeWithout; }

    virtual charT findKey(iNode<charT> *val) const;

    bool set_node(charT c,iNode<charT> *nNode);
    void clr_node() override;

    bool isFull() const
    { return lSon != nullptr && rSon != nullptr;}

    charT getLeftC() const
    {return leftC;}
    charT getRightC() const
    { return rightC; }
    iNode<charT>* getLeftSon() const
    { return lSon; }
    iNode<charT>* getRightSon() const
    { return rSon; }

    virtual UcharT sonNum()  const
    {
        UcharT ret = 0;
        if (lSon)
            ++ret;
        if (rSon)
            ++ret;
        return ret;
    }

    virtual void copyNodeFrom(iNode<charT> *val);
    bool isPrefixOf(const charT *str, UcharT len) const
    {
        return str && !len && this->getIsEnd();
    }
    bool isMatch(const charT *str, UcharT len) const
    {
        return str && !len && this->getIsEnd();
    }


private:
    charT leftC;
    charT rightC;
    iNode<charT> *lSon;
    iNode<charT> *rSon;

};

template <typename charT>
class gNode: public iNode<charT> {
public:
    explicit gNode(bool isEnd_ = false);
    ~gNode();
    gNode(const gNode<charT> &v);
    gNode &operator=(const gNode<charT> &v);

    using UcharT = typename iNode<charT>::UcharT;

    bool isPrefixOf(const charT *str, UcharT len) const
    { return str && !len && this->getIsEnd(); }

    bool isMatch(const charT *str, UcharT len) const
    { return str && !len && this->getIsEnd(); }


    iNode<charT> *getFirstSon() const
    {
        for (UcharT i = 0; i < ALPHANUM_LIMIT; ++i)
            if (Son[i])
                return Son[i];
        return nullptr;
    }
    bool isZombieNode() const;
    bool hasSonOf(charT c) final ;
    iNode<charT> *getSonOf(charT c) final ;
    virtual charT findKey(iNode<charT> *val) const;

    void clr_node();
    bool set_node(charT c, iNode<charT> *sVal) ;
    UcharT sonNum() const;

    constexpr enum nodeType getNodeType() const
    { return GeneralNodeWithout;}


    virtual void copyNodeFrom(iNode<charT> *val);



    bool isSingleSon() const;
    bool isDoubleSon() const;

private:
    iNode<charT> *Son[ALPHANUM_LIMIT];
};







template <typename charT, std::size_t MaxDataLen = 16>
class cGNode:public gNode<charT>
{
public:
    using UcharT = typename iNode<charT>::UcharT;

    explicit cGNode(const charT * str = nullptr, UcharT len = 0);
    ~cGNode();

    /*cGNode(const cGNode<charT> &v);
    cGNode& operator=(cGNode<charT> &v) = default;

*/
    UcharT  getDataLen() const ;

    bool isDataEmpty()
    {return mBitSet.isEmpty();}
    bool isZombieNode() const;
    constexpr enum nodeType getNodeType() const
    {return GeneralNode; }

    bool isPrefixOf(const charT *str, UcharT len) const;

    bool isMatch(const charT *str, UcharT len) const;

    virtual void setData(const charT *, UcharT len);
    void setDataLen(UcharT i)
    {
        if (i > MaxDataLen)
            return;
        dataLen = i;
    }

    const charT *getData()
    { return cData;}

    void setPos(UcharT pos, bool isTrue = true) final
    {
        mBitSet.setPos(pos , isTrue);
    }
    bool getPos(UcharT pos)
    {
        return mBitSet.getPos(pos);
    }
    virtual void setDataFrom(iNode<charT> *v, const charT *str, UcharT len);


    const MBitSet<MaxDataLen>& getBitSet() const
    {return mBitSet; }

private:
    MBitSet<MaxDataLen> mBitSet;
    UcharT dataLen;
    charT cData[MaxDataLen];
};

template <typename charT, std::size_t MaxDataLen = 16>
class cBNode:public bNode<charT>
{
public:
    using UcharT = typename iNode<charT>::UcharT;

    explicit cBNode(const charT *str = nullptr, UcharT len = 0);

    ~cBNode();
    cBNode(const cBNode<charT> &v) ;
    cBNode& operator=(const cBNode<charT> &v) ;

    UcharT getDataLen() const;

    void setDataLen(UcharT i)
    {
        if (i > MaxDataLen)
            return;
        dataLen = i;
    }

    bool isPrefixOf(const charT *str, UcharT len) const;
    bool isMatch(const charT *str, UcharT len) const;


    bool isDataEmpty()
    {return mBitSet.isEmpty();}
    bool isZombieNode() const;
    const charT * getData()
    { return cData; }
    enum nodeType getNodeType() const
    { return BinaryNode; }

    virtual void setData(const charT *, UcharT len);

    void setPos(UcharT pos, bool isTrue = true) final
    {
        mBitSet.setPos(pos , isTrue);
    }
    bool getPos(UcharT pos) final
    { return mBitSet.getPos(pos); }

    const MBitSet<MaxDataLen>& getBitSet() const
    { return mBitSet; }

private:

    MBitSet<MaxDataLen> mBitSet;
    UcharT dataLen;
    charT cData[MaxDataLen];
};




/* bNode */
template<typename charT>
bool bNode<charT>::hasSonOf(charT c)
{
    return   ( leftC == c  && lSon) ||
             ( rightC == c && rSon);
}

template<typename charT>
bNode<charT>::bNode(charT lc, charT rc , iNode<charT> *ls, iNode<charT> *rs):
        leftC(lc), rightC(rc),lSon(ls),rSon(rs)
{

}

template<typename charT>
bNode<charT>::~bNode()
{
    if (lSon) {
        delete lSon;
        lSon = nullptr;
    }
    if (rSon) {
        delete rSon;
        rSon = nullptr;
    }
}

template<typename charT>
iNode<charT> *bNode<charT>::getSonOf(charT c)
{
    if (!hasSonOf(c))
        return nullptr;

    return c == leftC ? lSon : rSon;
}

template<typename charT>
bool bNode<charT>::set_node(charT c, iNode<charT> *nNode)
{
    if (isFull())
        return false;

    if (hasSonOf(c)) {
        if (leftC == c) {
            lSon = nNode;
        }
        else {
            rSon = nNode;
        }
        fprintf(stderr, "already have son of %c\n", c);
        return false;
    }
    else {
        if (!lSon)
            leftC = c, lSon = nNode;
        else
            rightC = c, rSon = nNode;
    }

    return true;
}

template<typename charT>
charT bNode<charT>::findKey(iNode<charT> *val) const
{
    if (lSon == val)
        return leftC;
    else
        return rightC;
}

template<typename charT>
bool bNode<charT>::isZombieNode() const
{
    return !iNode<charT>::getIsEnd() && !sonNum();
}

template<typename charT>
void bNode<charT>::copyNodeFrom(iNode<charT> *val)
{
    if ( !val->sonNum() )
        return;
    if (this->sonNum())
        return;

    if (val->isBinNode()) {

        bNode<charT> *srcNode = (bNode<charT> *) val;
        this->set_node(srcNode->getLeftC(), srcNode->getLeftSon() );
        this->set_node(srcNode->getRightC(), srcNode->getRightSon() );
    }
    else {
        if (val->sonNum() > 2 )
            return ;

        gNode<charT> *srcNode = (gNode<charT> *) val;
        for (UcharT i = 0; i < ALPHANUM_LIMIT; ++i)
            if (srcNode->getSonOf(i))
                srcNode->set_node(i, srcNode->getSonOf(i) );
    }

}

template<typename charT>
void bNode<charT>::clr_node()
{
    this->lSon = this->rSon = nullptr;
}

/* End of bNode implemention. *./


/* gNode */
template <typename charT>
gNode<charT>::gNode(bool isEnd_):iNode<charT>(isEnd_)
{
    for (int i = 0;i < ALPHANUM_LIMIT; ++i)
        Son[i] = nullptr;

    std::size_t i = 0;
}

template <typename  charT>
gNode<charT>::~gNode()
{
    for (int i = 0; i < ALPHANUM_LIMIT;++i) {
        if (Son[i]) {
            delete Son[i];
            Son[i] = nullptr;
        }
    }
}


template <typename charT>
bool gNode<charT>::isDoubleSon() const
{
    return sonNum() == 2;
}

template <typename charT>
bool gNode<charT>::isSingleSon() const
{
    return sonNum() == 1;
}


template<typename charT>
typename gNode<charT>::UcharT gNode<charT>::
        sonNum() const
{
    UcharT sNum = 0;
    for (int i = 0; i < ALPHANUM_LIMIT; ++i) {
        if (Son[i] != nullptr)
            sNum++;
    }
    return sNum;
}
template <typename charT>
bool gNode<charT>::hasSonOf(charT c)
{
    return getSonOf(c) != nullptr;
}
template<typename charT>
iNode<charT>* gNode<charT>::getSonOf(charT c)
{
    return Son[static_cast<UcharT>(c)];
}
template <typename charT>
bool gNode<charT>::set_node( charT c, iNode<charT> *sVal )
{
    bool ret = true;
    iNode<charT> *son = getSonOf(c);
    if (son) {
        ret =  false;
    }
    Son[static_cast<UcharT>(c)] = sVal;

    return ret;
}

template<typename charT>
charT gNode<charT>::findKey(iNode<charT> *val) const {

    for (UcharT i = 0;i <ALPHANUM_LIMIT; ++i) {
        if (Son[i] == val)
            return i;
    }
    return 0;
}

template<typename charT>
bool gNode<charT>::isZombieNode() const
{
    return !iNode<charT>::getIsEnd() && !sonNum();
}

template<typename charT>
gNode<charT> &gNode<charT>::operator=(const gNode<charT> &v)
{
    if (v != *this) {
        this->setIsEnd(v.getIsEnd());
        for (UcharT i = 0; i < ALPHANUM_LIMIT; ++i) {
            iNode<charT> *tSon = v.getSonOf(i);
            set_node(i, tSon);
        }
    }

    return *this;
}

template<typename charT>
void gNode<charT>::copyNodeFrom(iNode<charT> *val)
{
    if (this->sonNum())
        return ;
    if (!val->sonNum() )
        return;

    if (val->isBinNode()) {

        bNode<charT> *srcNode = (bNode<charT> *) val;
        this->set_node(srcNode->getLeftC(), srcNode->getLeftSon() );
        this->set_node(srcNode->getRightC(), srcNode->getRightSon() );
    }
    else {


        gNode<charT> *srcNode = (gNode<charT> *) val;
        for (UcharT i = 0; i < ALPHANUM_LIMIT; ++i)
            if (srcNode->getSonOf(i))
                srcNode->set_node(i, srcNode->getSonOf(i) );
    }


}

template<typename charT>
void gNode<charT>::clr_node()
{
    for (UcharT i = 0; i < ALPHANUM_LIMIT; ++i)
        this->Son[i] = nullptr;
}


/*End of gNode implemention*/


/*cGNode*/

template <typename charT, std::size_t MaxDataLen>
cGNode<charT, MaxDataLen>::~cGNode()
{

}
template <typename charT, std::size_t MaxDataLen>
typename cGNode<charT, MaxDataLen>::UcharT cGNode<charT, MaxDataLen>::getDataLen() const
{
    return dataLen;
}

template<typename charT, std::size_t MaxDataLen>
void cGNode<charT, MaxDataLen>::setData(const charT * str, cGNode::UcharT len)
{
    if (len > MaxDataLen)
        return;
    if (!len) {
        this->setIsEnd(true);
        return;
    }


    memcpy(cData, str, len * sizeof(charT));
}

template<typename charT, std::size_t MaxDataLen>
cGNode<charT, MaxDataLen>::cGNode(const charT *str, cGNode::UcharT len)
:gNode<charT>()
{
    if (len) {

        if (len > MaxDataLen)
            len = MaxDataLen;

        memcpy(cData, str, sizeof(charT) * len );
    }
    dataLen = len;
}

template<typename charT, std::size_t MaxDataLen>
bool cGNode<charT, MaxDataLen>::isZombieNode() const
{
    return gNode<charT>::isZombieNode();
}

template<typename charT, std::size_t MaxDataLen>
void cGNode<charT, MaxDataLen>::setDataFrom(iNode<charT> *v, const charT *str, cGNode::UcharT len)
{
    if (!v->isWithData() || !str || !len || getDataLen() )
        return;


}

template<typename charT, std::size_t MaxDataLen>
bool cGNode<charT, MaxDataLen>::isPrefixOf(const charT *str, cGNode::UcharT len) const
{
    if (!str)
        return false;
    if (!len)
        return this->getIsEnd();

    if (len < dataLen)
        return false;

    return !memcmp(cData, str, dataLen * sizeof(charT) );
}

template<typename charT, std::size_t MaxDataLen>
bool cGNode<charT, MaxDataLen>::isMatch(const charT *str, cGNode::UcharT len) const
{
    if (!str)
        return false;
    if (!len)
        return this->getIsEnd();

    if (len > dataLen)
        return false;

    return !memcmp(str, cData, len * sizeof(charT) ) && mBitSet.getPos(len - 1);

}

/*End of cGNode implemention*/

/*cBNode*/
template <typename charT, std::size_t MaxDataLen>
cBNode<charT, MaxDataLen>::cBNode(const charT *str, UcharT sz)
:bNode<charT>()
{
    mBitSet.reset();
    if (sz && str) {
        this->dataLen = sz;
        if (sz > MaxDataLen)
            dataLen = MaxDataLen;

        memcpy(cData, str, sizeof(charT) * dataLen);
    }
    else {
        this->dataLen = 0;
    }

}

template <typename charT, std::size_t MaxDataLen>
cBNode<charT, MaxDataLen>::~cBNode()
{


}

template <typename charT, std::size_t MaxDataLen>
typename iNode<charT>::UcharT  cBNode<charT, MaxDataLen>::getDataLen() const
{
    return dataLen;
}

template<typename charT, std::size_t MaxDataLen>
void cBNode<charT, MaxDataLen>::setData(const charT *str, cBNode::UcharT len) {

    if (!str|| len  > MaxDataLen)
        return ;
    if (!len) {
        this->setIsEnd(true);
        return;
    }

    memcpy(this->cData, str, sizeof(charT) * len);
    mBitSet.setPos(len - 1);
    dataLen = len;
}

template<typename charT, std::size_t MaxDataLen>
cBNode<charT, MaxDataLen>::cBNode(const cBNode<charT> &v) {

    this->dataLen = v.dataLen;
    this->mBitSet = v.mBitSet;
    for (UcharT i = 0;i < v.dataLen; ++i)
        cData[i] = v.cData[i];

    this->set_node(v.getLeftC(), v.getSonOf(v.getLeftC()) );
    this->set_node(v.getRightC(), v.getSonOf(v.getRightC()) );
}

template<typename charT, std::size_t MaxDataLen>
cBNode<charT, MaxDataLen> &cBNode<charT, MaxDataLen>::operator=(const cBNode<charT> &v) {

    if (v == *this) {
        this->dataLen = v.dataLen;
        this->mBitSet = v.mBitSet;
        for (UcharT i = 0;i < v.dataLen; ++i)
            cData[i] = v.cData[i];
    }

    return *this;
}

template<typename charT, std::size_t MaxDataLen>
bool cBNode<charT, MaxDataLen>::isZombieNode() const
{
    return this->getIsEnd() && this->sonNum() && mBitSet.isEmpty();
}

template<typename charT, std::size_t MaxDataLen>
bool cBNode<charT, MaxDataLen>::isPrefixOf(const charT *str, UcharT len) const
{
    if (!str)
        return false;
    if (!len)
        return this->getIsEnd();

    if (len < dataLen)
        return false;

    return !memcmp(cData, str, dataLen * sizeof(charT) );
}

template<typename charT, std::size_t MaxDataLen>
bool cBNode<charT, MaxDataLen>::isMatch(const charT *str, cBNode::UcharT len) const
{
    if (!str)
        return false;
    if (!len)
        return this->getIsEnd();

    if (len > dataLen)
        return false;

    return !memcmp(str, cData, sizeof(charT) * len) && mBitSet.getPos(len - 1);
}

/*End of cBNode implemention*/


#endif //TESTME_TRIENODE_H
