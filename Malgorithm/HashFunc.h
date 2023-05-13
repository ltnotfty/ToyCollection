//
// Created by xOx on 2023/3/31.
//

#ifndef TESTME_HASHFUNC_H
#define TESTME_HASHFUNC_H


class HashFunc
{
public:

    static unsigned int SDBMHash(char *str);

// RS Hash Function
    static unsigned int RSHash(char *str);


// JS Hash Function
    static unsigned int JSHash(char *str);


// P. J. Weinberger Hash Function
    static unsigned int PJWHash(char *str);


// ELF Hash Function
    static unsigned int ELFHash(char *str);


// BKDR Hash Function
    static unsigned int BKDRHash(char *str);

// DJB Hash Function
    static unsigned int DJBHash(char *str);

// AP Hash Function
    static unsigned int APHash(char *str);


};


#endif //TESTME_HASHFUNC_H
