//
// Created by xOx on 2023/5/13.
//

#ifndef TESTME_MUNIQUEPTR_H
#define TESTME_MUNIQUEPTR_H

template<typename Tp>
class MUniquePtr
{
    explicit MUniquePtr();


private:
    Tp *m_rawPtr;
};


#endif //TESTME_MUNIQUEPTR_H
