//
// Created by xOx on 2023/4/26.
//

#ifndef TESTME_COMPRESSTRIE_H
#define TESTME_COMPRESSTRIE_H

#include "TrieNode.h"
#include "Trie.h"


class pair;

template<typename T>
class CompressTrie{

public:

    using UcharT = typename iNode<T>::UcharT;

    explicit CompressTrie();
    ~CompressTrie();


    bool insert(T c);
    bool insert(const T* str, uint8_t len);
    bool find(const T *str, uint8_t len);
    bool del(const T *str, uint8_t len);
    bool startWith(const T *str, uint8_t len);

    static constexpr std::size_t ObjSz = sizeof(T);
    static constexpr std::size_t MaxDataLen = 16;

private:
    using Cmp_Node_Info = std::pair<iNode<T>*, UcharT>;
    using Node_Info = std::pair<iNode<T>*, iNode<T>* >;

    using Ins_Info = std::pair<UcharT, bool>;

    bool insert_impl(const T *str, UcharT len);

    bool merge_aux(iNode<T> *parentNode ,iNode<T> *rootNode);

    void adjustLeafNode(iNode<T> *rootNode);


    bool del_aux(iNode<T> *root, const T *str, uint8_t len);

    /// \brief current node match with pattern str
    bool node_match(iNode<T> *root, const T *str, uint8_t len);


    /// \brief node data is prefix of str
    bool node_startWith(iNode<T> *root, const T *str, uint8_t len);


    std::pair<Node_Info, UcharT> find_misMatch(iNode<T> *root, const T *str, uint8_t len);


    std::pair<Node_Info, Ins_Info> find_misMatch_aux(iNode<T>*prev, iNode<T> *root, const T* str, uint8_t len);


    /// \brief return restLen and targetNode
    Cmp_Node_Info   find_match(iNode<T> *root, const T *str, uint8_t len);

    /// \brief safe set son of current Node
    iNode<T>* Set_Node(iNode<T> *parentNode, iNode<T> *cmpNode,  T c, iNode<T> *newNode);

    /// \brief convert two son node to multi son node
    iNode<T>* convert2mnode(iNode<T> *parentNode,iNode<T> *cmpNode);

    /// \brief convert multi son node to two son node
    iNode<T>* convert2dnode(iNode<T> *parentNode, iNode<T> *cmpNode);

    /// \brief according to str, make a link node list.
    iNode<T>* NewSingleNode(const T *str, UcharT len);

    /// \brief if dataNode partial match, split node to two section to add new feature node.
    iNode<T>* SplitNode(iNode<T> *parentNode, iNode<T> *targetNode, UcharT prefixLen);


    gNode<T> rootNode;
};


template <typename T>
bool CompressTrie<T>::insert(const T* str, uint8_t len)
{

    if (!str || !len)
        return false;


    // find first mismatch node and rest length of str
    std::pair<CompressTrie<T>::Node_Info, UcharT >
            info = find_misMatch(&rootNode, str, len);

    iNode<T> *parentNode = info.first.first;
    iNode<T> *cmpNode = info.first.second;
    UcharT rstLen = info.second;


    UcharT dataLen = cmpNode->getDataLen();
    // already have node
    if (!cmpNode) {
        return false;
    }

    // no related son node, need new one
 /*   if (indexIns) {

        iNode<T> * newNode = NewSingleNode(str + len - rstLen + 1, rstLen - 1);
        cmpNode = Set_Node(parentNode, cmpNode,  str[len - rstLen], newNode);
    }
    else {*/
    if (cmpNode == &rootNode && !cmpNode->hasSonOf(str[0])) {
        auto *nwNode = NewSingleNode(str + len - rstLen + 1, rstLen - 1);
        Set_Node(parentNode, cmpNode, str[len - rstLen], nwNode );
        return true;
    }


        UcharT matchLen = 0;
        const T *data = cmpNode->getData();
        for (UcharT i = 0; i < dataLen; ++i, ++matchLen)
            if (str[len - rstLen + i] != data[i])
                break;

        // not is end flag set
        if ( matchLen == rstLen && rstLen <= dataLen ) {
            if ( !matchLen )
                cmpNode->setIsEnd(true);
            else
                cmpNode->setPos(matchLen - 1);
        } else if (parentNode  && matchLen == dataLen && rstLen > dataLen ) {


            // set data
            cmpNode->setData( str + len - rstLen, MaxDataLen );


            if (rstLen > MaxDataLen) {
                UcharT sonPos = len - rstLen + MaxDataLen + 1;

                // new rest node
                auto *nwNode = NewSingleNode(str + sonPos, rstLen - MaxDataLen - 1);
                Set_Node(parentNode, cmpNode, str[sonPos - 1], nwNode);
            }

        } else {
            // node split
            cmpNode = SplitNode(parentNode, cmpNode, matchLen);
            if (!cmpNode) {
                fprintf(stderr, "split node failed\n");
                exit(EXIT_FAILURE);
            }


            // last rst len
            UcharT curPos = len - rstLen + matchLen;
            iNode<T> *newNode = NewSingleNode(str + curPos + 1, rstLen - matchLen - 1);
            Set_Node(parentNode, cmpNode, str[curPos], newNode);
        }


    return true;
}

template <typename Tp>
CompressTrie<Tp>::CompressTrie()
{
    rootNode.setIsEnd(false);
}

template <typename Tp>
CompressTrie<Tp>::~CompressTrie()
{
}

template <typename Tp>
bool CompressTrie<Tp>::find(const Tp *str, uint8_t len)
{
    if (!str || !len)
        return false;

    std::pair<iNode<Tp> *, UcharT> ret = find_match(&rootNode, str, len);
    iNode<Tp> *tgNode = ret.first;
    UcharT resLen = ret.second;


    return  tgNode && tgNode->isMatch(str + len - resLen, resLen);
}

template <typename Tp>
std::pair<iNode<Tp>*, typename CompressTrie<Tp>::UcharT>
CompressTrie<Tp>::find_match(iNode<Tp> *root, const Tp *str, uint8_t len)
{
    if (!root)
        return std::pair<iNode<Tp> *, UcharT> { nullptr, 0};

    if (!str)
        return std::pair<iNode<Tp> *, UcharT> { nullptr, 0};

    UcharT dataLen = root->getDataLen();
    if (len <= dataLen) {
        return std::pair < iNode<Tp> * , UcharT > {root, len};
    }
    else {

        // if no data, or data match and ,there are more char in str.
        if (node_startWith(root, str, len)) {
            return find_match(root->getSonOf(str[dataLen]), str + dataLen + 1, len - dataLen - 1);
        }
        else {
                return std::pair < iNode<Tp> * , UcharT > {nullptr, 0};
        }
    }
}


template<typename T>
bool CompressTrie<T>::node_match(iNode<T> *root, const T *str, uint8_t len)
{
    if (!root)
        return false;

    UcharT dataLen = root->getDataLen();
    if (len > dataLen)
        return false;

    if (!dataLen) {
        return root->getIsEnd();
    }

    return root->getPos(len - 1) && !memcmp(root->getData(), str, ObjSz*len);
}

template<typename T>
bool CompressTrie<T>::node_startWith(iNode<T> *root, const T *str, uint8_t len)
{
    if (!root)
        return false;

    UcharT dataLen = root->getDataLen();
    if (!dataLen)
        return true;

    if (!root->getData() || len < dataLen)
        return false;


    return !memcmp(root->getData(), str, ObjSz * dataLen);
}







template<typename T>
iNode<T>* CompressTrie<T>::Set_Node(iNode<T> *parentNode, iNode<T> *cmpNode,  T c, iNode<T> *newNode)
{
    iNode<T> *ret = cmpNode;

    if ( ret->isBinNode() && ((bNode<T>*) ret)->isFull()) {
        ret = convert2mnode(parentNode, cmpNode);
    }
    ret->set_node(c, newNode);

    return ret;
}

template<typename T>
iNode<T> * CompressTrie<T>::convert2mnode(iNode<T> *parentNode, iNode<T> *cmpNode)
{

    iNode<T> *ret = new cGNode<T>(cmpNode->getData(), cmpNode->getDataLen());

    // new node point to son of cmpNode
    bNode<T> *m_bNode = static_cast< bNode<T>* > (cmpNode);


    // connect new node to original son node
    ret->copyNodeFrom(cmpNode);

    // disconnect old node to son node
    cmpNode->clr_node();


    // according to val, to find key.
    T c = parentNode->findKey(cmpNode);
    // connect parent node to new node
    parentNode->set_node(c, ret);

    // free old node
    delete cmpNode;

    return ret;
}


template<typename T>
iNode<T> * CompressTrie<T>::convert2dnode(iNode<T> *parentNode, iNode<T> *cmpNode)
{
    if (!parentNode || !cmpNode)
        return nullptr;


    // new cBNode
    iNode<T> *newNode = new cBNode<T>(cmpNode->getData(), cmpNode->getDataLen() );
    newNode->setIsEnd(cmpNode->getIsEnd() );

    // connect newNode to cmpNode's son node
    for (UcharT i = 0; i < ALPHANUM_LIMIT; ++i) {
        iNode<T> *son = cmpNode->getSonOf(i);
        if (son) {
            newNode->set_node(i, son);
            cmpNode->set_node(i, nullptr);
        }
    }

    // connect newNode and parentNode
    T c = parentNode->getKey(cmpNode);
    parentNode->set_son(c, newNode);
    delete cmpNode;

    return newNode;
}

template<typename T>
iNode<T>* CompressTrie<T>::NewSingleNode(const T *str, UcharT len)
{
    if (!str)
        return nullptr;

    iNode<T> *head = nullptr;
    iNode<T> *cur  = nullptr;
    iNode<T> *nw   = nullptr;
    UcharT indexC = 0;

    while (len) {

        if (MaxDataLen >= len) {
            nw = new cBNode<T>(str, len);
            nw->setPos(len - 1, true);
            // last node set is End;

            if (cur)
                cur->set_node(indexC, nw);
            else
                head = nw;
            break;
        }
        else {
            nw = new cBNode<T>(str, MaxDataLen);
            nw->setDataLen(MaxDataLen);
            if (cur) {
                cur->set_node(indexC, nw);
                cur = nw;
            }
            else
                cur = head = nw;
            len -= MaxDataLen;
            str += MaxDataLen;
        }

        if (0 == len)
            break;
        if (1 == len) {
            nw = new cBNode<T>( str, 0 );
            nw -> setIsEnd(true);
            nw -> setDataLen(0);
            // last node set is end

            cur -> set_node( str[0], nw );
            break;
        }
        indexC = str[0];
        ++str, --len;
    }

    return head;

}


template <typename T>
iNode<T>* CompressTrie<T>::SplitNode(iNode<T> *parentNode, iNode<T> *targetNode, UcharT prefixLen)
{
    if (!targetNode  || targetNode->getDataLen() <= prefixLen)
        return nullptr;

    // get data info
    const T *data = targetNode->getData();
    UcharT dataLen = targetNode->getDataLen();

    // new trunk node and branch node
    iNode<T> *nNode = new cBNode<T>(data, prefixLen);
    iNode<T> *rstNode = nullptr;

    // new branch node and connect it to rst node, and disconnect  targetNode and rest node
    if (targetNode->isBinNode()) {
        rstNode = new cBNode<T>( data + prefixLen + 1, dataLen - prefixLen - 1 );
    }
    else {
        rstNode = new cGNode<T>( data + prefixLen + 1, dataLen - prefixLen - 1 );
    }

    rstNode->setIsEnd( targetNode->getPos(prefixLen) );
    for (UcharT i = prefixLen + 1; i < dataLen; ++i)
        rstNode->setPos(i - prefixLen - 1, targetNode->getPos(i) );

    rstNode->copyNodeFrom(targetNode);
    targetNode->clr_node();



    // connect branch node and trunk node
    nNode->set_node( data[prefixLen], rstNode );
    // nNode->setData( data, prefixLen );
    nNode->setIsEnd( targetNode->getIsEnd() );
    for (UcharT i = 0; i < prefixLen; ++i)
        nNode->setPos( i, targetNode->getPos(i) );


    // connect parent node to body node
    T indexC = parentNode->findKey(targetNode);
    parentNode->set_node(indexC, nNode);

    // free targetNode
    delete targetNode;


    return nNode;
}

template<typename  T>
bool CompressTrie<T>::del(const T *str, uint8_t len)
{
    if (!find(str,len))
        return false;

    del_aux(&rootNode, str, len);

    return true;
}

template<typename T>
bool CompressTrie<T>::startWith(const T *str, uint8_t len)
{

    return false;
}

template<typename T>
void CompressTrie<T>::adjustLeafNode(iNode<T> *rootNode)
{

    if (rootNode == nullptr)
        return;
    // need be a leaf node
    if (rootNode->sonNum())
        return ;
    // need have data
    UcharT curLen = rootNode->getDataLen();
    if (!curLen)
        return ;

    UcharT nLen = 0;
    for (UcharT i = curLen - 1; i != -1; --i) {
        if (rootNode->getPos(i)) {
            nLen = i + 1;
            break;
        }
    }

    rootNode->setDataLen(nLen);
}

template<typename T>
bool CompressTrie<T>::merge_aux(iNode<T> *parentNode ,iNode<T> *rootNode)
{
    if (!rootNode)
        return false;
    if (rootNode->sonNum() != 1)
        return false;


    iNode<T> *sonNode = rootNode->getFirstSon();

    UcharT rDataLen = rootNode->getDataLen();
    UcharT sDataLen = sonNode->getDataLen();

    if (  rDataLen + sDataLen + 1
          > MaxDataLen )
        return false;

    // bufData for cpy
    T bufData[MaxDataLen];
    if (rDataLen)
        memcpy(bufData, rootNode->getData(), rDataLen );

    T key = rootNode->findKey(sonNode);
    bufData[rDataLen] = key;
    rootNode->setPos(rDataLen, sonNode->getIsEnd() );

    const T* sData = sonNode->getData();
    for (UcharT i = rDataLen + 1; i < rDataLen + sDataLen + 1; ++i ) {
        bufData[i] = sData[i - rDataLen - 1];
        rootNode->setPos(i, sonNode->getPos(i - rDataLen - 1) );
    }
    rootNode->setData(bufData, rDataLen + sDataLen + 1);


    iNode<T> *bodyNode = rootNode;
    // judge if need to transform node
    if (sonNode->sonNum() > 2 && rootNode->isBinNode()) {
        bodyNode = convert2mnode(parentNode, rootNode);
        bodyNode->set_son(key, nullptr);
    }


    // copy sonNode's node info
    for (UcharT i = 0; i < ALPHANUM_LIMIT; ++i) {
        auto *tSon = sonNode->getSonOf(i);
        if (tSon)
            bodyNode->set_node(i, sonNode->getSonOf(i) );
    }



    // delete son of node
    delete sonNode;

    return true;
}

template<typename T>
bool CompressTrie<T>::del_aux(iNode<T> *root, const T *str, uint8_t len)
{
    if ( !root|| !str)
        return false;

    UcharT dataLen = root->getDataLen();
    if ( dataLen >= len) {
        if (!len) {
            root->setIsEnd(false);
        }
        else {
            root->setPos(len - 1, false);
            adjustLeafNode(root);
        }
    }
    else {
        iNode<T> *nxtNode = root->getSonOf(str[0]);
        bool need_del = del_aux(nxtNode, str + dataLen + 1, len - dataLen - 1);
        if (need_del) {
            delete nxtNode;
            root->set_node(str[0], nullptr);
        }
    }

    return root->isZombieNode();
}


template<typename T>
std::pair<typename CompressTrie<T>::Node_Info, typename CompressTrie<T>::UcharT >
CompressTrie<T>::find_misMatch(iNode<T> *root, const T *str, uint8_t len)
{
    Node_Info retNodePair{nullptr, nullptr};
    UcharT  rstLen = len;


    std::pair<Node_Info, UcharT> retVal{ retNodePair, rstLen};
    if (!root)
        return retVal;

    iNode<T> *prev = nullptr ;
    iNode<T> *cur  = root ;



    for ( UcharT i = 0; i < len; ++i) {

        if ( !cur->isPrefixOf( str + i, len - i ) ) {
            retVal.first.first  = prev;
            retVal.first.second = cur ;
            retVal.second       = len - i;
            break;
        }
        i += cur->getDataLen();

        if ( i >= len || !cur->getSonOf(str[i]) ) {
            retVal.first.first  = prev;
            retVal.first.second = cur ;
            retVal.second       = len - i + cur->getDataLen();
            break;
        }

        prev = cur;
        cur  = cur->getSonOf( str[i] );
    }



    return retVal;
}

template<typename T>
std::pair<typename CompressTrie<T>::Node_Info, typename CompressTrie<T>::Ins_Info>
CompressTrie<T>::find_misMatch_aux(iNode<T>*prev, iNode<T> *root, const T* str, uint8_t len)
{
    Node_Info nodePair{nullptr, nullptr};
    Ins_Info insInfo {0, false};
    std::pair<Node_Info, Ins_Info> retVal{nodePair, insInfo };

    if (!str || !len || !root)
        return retVal;

    UcharT curDataLen;
    UcharT indexC;
    iNode<T> *nxt = nullptr;

    while (len) {
        curDataLen = root->getDataLen();

        // if  rule str less than cur node or not match cur node
        if (len  <= curDataLen || !node_startWith(root, str, len)) {
            nodePair.first = prev;
            nodePair.second = root;
            insInfo.first = len;
            insInfo.second = false;
            break;
        }

        len -= curDataLen;
        str += curDataLen;

        nxt = root->getSonOf(str[0]);
        // if no related son, flag it
        if (!nxt) {
            nodePair.first = prev;
            nodePair.second = root;
            insInfo.first = len + curDataLen;
            insInfo.second = true;
            break;
        }

        prev = root;
        root = nxt;
        ++str, --len;
    }


    // if it is a head flag
    if (!len && !root->getIsEnd()) {
        nodePair.first = prev;
        nodePair.second = root;
    }

    retVal.first = nodePair;
    retVal.second = insInfo;

    return retVal;

}

template<typename T>
bool CompressTrie<T>::insert_impl(const T *str, CompressTrie::UcharT len)
{
    if (!str || !len)
        return false;


    // find first mismatch node and rest length of str
    std::pair<CompressTrie<T>::Node_Info, CompressTrie<T>::Ins_Info>
            info = find_misMatch(&rootNode, str, len);

    iNode<T> *parentNode = info.first.first;
    iNode<T> *cmpNode = info.first.second;
    UcharT rstLen = info.second.first;
    bool indexIns = info.second.second;

    UcharT dataLen = cmpNode->getDataLen();
    // already have node
    if (!cmpNode) {
        return false;
    }

    // no related son node, need new one
    if (indexIns) {


        iNode<T> * newNode = NewSingleNode(str + len - rstLen + 1, rstLen - 1);
        cmpNode = Set_Node(parentNode, cmpNode,  str[len - rstLen], newNode);
    }
    else {

        UcharT matchLen = 0;
        const T *data = cmpNode->getData();
        for (UcharT i = 0; i < dataLen; ++i, ++matchLen)
            if (str[len - rstLen + i] != data[i])
                break;

        // not is end flag set
        if (matchLen == rstLen && rstLen <= dataLen) {
            if (!matchLen)
                cmpNode->setIsEnd(true);
            else
                cmpNode->setPos(matchLen - 1);
        } else if ( rstLen > dataLen) {

            // maybe_to_do?: what if already have str[0]'s branch ?
            // find_misMatch_aux ensure there will not occur this situation.
            cmpNode->setData(str + len - rstLen, MaxDataLen);

            rstLen -= MaxDataLen - dataLen;
            str += MaxDataLen - dataLen;

            iNode<T> *newNode = NewSingleNode(str + 1, rstLen - 1);
            Set_Node(parentNode, cmpNode, str[0], newNode);
        } else {
            // node split
            cmpNode = SplitNode(parentNode, cmpNode, matchLen);
            if (!cmpNode) {
                fprintf(stderr, "split node failed\n");
                exit(EXIT_FAILURE);
            }


            // last rst len
            UcharT curPos = len - rstLen + matchLen;
            iNode<T> *newNode = NewSingleNode(str + curPos + 1, rstLen - matchLen - 1);
            Set_Node(parentNode, cmpNode, str[curPos], newNode);
        }

    }

    return true;
}


#endif //TESTME_COMPRESSTRIE_H
