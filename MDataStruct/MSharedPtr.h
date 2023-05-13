//
// Created by xOx on 2023/5/13.
//

#ifndef TESTME_MSHAREDPTR_H
#define TESTME_MSHAREDPTR_H

template <typename Tp>
class MSharedPtr
{

public:

    explicit MSharedPtr(Tp *ptr = nullptr);

    ~MSharedPtr();


    MSharedPtr(const MSharedPtr<Tp> &sPtr);

    MSharedPtr& operator=(const MSharedPtr<Tp> &sPtr);


    Tp& operator*();



private:
    Tp * m_rawPtr;
    std::size_t * m_refCnt;
};


template<typename Tp>
MSharedPtr<Tp>::MSharedPtr(Tp *ptr):m_rawPtr(ptr)
{
    if (!ptr) {
        m_refCnt = new std::size_t(0);
    }
    else {
        m_refCnt = new std::size_t(1);
    }
}


template <typename Tp>
MSharedPtr<Tp>&
MSharedPtr<Tp>::operator=(const MSharedPtr<Tp> &sPtr)
{
    if (*this != sPtr) {

        if (m_rawPtr) {
            --(*m_refCnt);

            if (*m_refCnt == 0)
                delete m_rawPtr;
        }
        else {
            m_rawPtr = sPtr.m_rawPtr;
            m_refCnt = sPtr.m_refCnt;

            ++(*m_refCnt);


            std::cout << m_refCnt << std::endl;
        }
    }


    return *this;
}

template <typename Tp>
MSharedPtr<Tp>::MSharedPtr(const MSharedPtr<Tp> &sPtr)
{
    if (sPtr.m_rawPtr) {
        m_rawPtr = sPtr.m_rawPtr;
        m_refCnt = sPtr.m_refCnt;

        *m_refCnt++;
    }
    else {
        m_refCnt = new std::size_t(0);
        m_rawPtr = nullptr;
    }


    std::cout << *m_refCnt << std::endl;
}
template <typename Tp>
MSharedPtr<Tp>::~MSharedPtr()
{
    if (this->m_rawPtr) {
        --(*m_refCnt);

        std::cout << *m_refCnt << std::endl;
        if ( 0 == *m_refCnt )
            delete m_rawPtr;


    }
}

template<typename Tp>
Tp& MSharedPtr<Tp>::operator*()
{
    return *m_rawPtr;
}


#endif //TESTME_MSHAREDPTR_H
