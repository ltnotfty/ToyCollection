#include <cstdio>
#include <vector>

#include "ProjectConfig.h"
#include "MyTimeRecorder.h"


#include <iostream>
#include <string>
#include <list>


#include <cstring>
#include "MDataStruct/Trie//Trie.h"
#include "Malgorithm/BinaryTree.h"

#include "OSUtils.h"
#include <fstream>

#include <unordered_map>


#include <string>
#include <ostream>
#include <string>


#include <stdexcept>



bool normal_match(const char *text, const char * pattern)
{
    if (!*pattern)
        return true;
    if (!*text)
        return false;

    if (*text == *pattern)
        return normal_match(text + 1, pattern + 1);
    else
        return false;
}
bool normal_match_nrec(const char *text, const char *pattern)
{

        for ( ; *pattern && (*text); ++pattern, ++text)
            if (*text != *pattern)
                return false;

        return *text || !*pattern;
}
bool match_with_point(const char *text, const char *pattern)
{
    if (!*pattern)
        return true;
    if (!*text)
        return false;

    if (*text == *pattern || *pattern == '.')
        return normal_match(text + 1, pattern + 1);
    else
        return false;
}
bool match_with_point_nrec(const char *text, const char *pattern)
{

    for ( ; *pattern && (*text); ++pattern, ++text)
    {
        if (*text != *pattern && *pattern != '.')
            return false;
    }

    return *text || !*pattern;
}

bool match_with_star(const char *text, const char *pattern)
{
    if (!*pattern)
        return true;
    if (!*text)
        return false;

    if (*pattern != '*') {
        if (*pattern != *text)
            return false;
        return match_with_star(text + 1, pattern + 1);
    }
    else {
        char c = *(text - 1);
        int len = static_cast<int>(strlen(text) );


        for (int i = 0; i < len; ++i) {
            if (text[i] != c)
                break;
            if ( match_with_star(text + i + 1, pattern + i + 1) )
                return true;
        }
        return match_with_star(text, pattern + 1);
    }

    return false;
}




#include "MDataStruct/FixLenStr.h"

#include "Trie.h"
#include <cstring>


class m {
public:
    m(int a)
    {
        if (a)
            m(a-1);

    }


};

#include <MDataStruct/Trie/CompressTrie.h>

class CompanyA {
public:
    void sendClearText(const std::string &str)
    {
        clrText = str + 'a';
    }
    void sendEncryText(const std::string &str)
    {
        encText = str + 'a';
    }
    void echoClearText()
    {
        std::cout << clrText << std::endl;
    }
    void echoEncryText()
    {
        std::cout << encText << std::endl;
    }


private:
    std::string clrText;
    std::string encText;
};
class CompanyB {
public:
    void sendClearText(const std::string &str)
    {
        clrText = str + 'b';
    }
    void sendEncryText(const std::string &str)
    {
        encText = str + 'b';
    }
    void echoClearText()
    {
        std::cout << clrText << std::endl;
    }
    void echoEncryText()
    {
        std::cout << encText << std::endl;
    }

private:
    std::string clrText;
    std::string encText;
};




template<typename Company>
class tClass {
public:
    void sendClear(const std::string &str);
    void sendEncry(const std::string &str);
private:
    std::string m_Str;
};

class CompanyZ {
public:
    void sendClearText(const std::string &str)
    {
        clrText = str + 'z';
    }
    void sendEncryText(const std::string &str)
    {
        clrText = str + 'z';
    }
    void echoClearText()
    {
        std::cout << clrText << std::endl;
    }
    void echoEncryText()
    {
        std::cout << encText << std::endl;
    }
private:
    std::string clrText;
    std::string encText;
};

template<typename Company>
void tClass<Company>::sendClear(const std::string &str) {
    Company a;

    a.sendClearText(str);
    a.echoClearText();
}

template<typename Company>
void tClass<Company>::sendEncry(const std::string &str)
{
    Company b;
    b.sendEncryText(str);
    b.echoEncryText();
}

template<>
class tClass<CompanyZ>
{
public:
    void sendClear(const std::string &str) = delete;
    void sendEncry(const std::string &str)
    {
        CompanyZ z;
        z.sendEncryText(str);
        z.echoEncryText();
    }
};



template<typename Company>
class logTextCalss:public tClass<Company>
{
public:

    void sendClearMsg(const std::string &str)
    {
        // put log before send
        tClass<Company>::tCsendClear(str);
        // put log after send
    }


};



#include <memory>



#include <MDataStruct/MSharedPtr.h>


class SPtr {

public:

    SPtr(int *p = nullptr):m_Ptr(p)
    {

    }
    int& operator*();

private:
    int *m_Ptr;
};

int &SPtr::operator*()
{
    return *m_Ptr;
}


void increase(MSharedPtr<int> q)
{
    (*q)++;
}


int main (int argc, char *argv[])
{
   /*logTextCalss<CompanyA> lA;
   lA.sendClearMsg( std::string("abc") );*/

   MSharedPtr<int> q(nullptr);

   MSharedPtr<int> p = q;


    return 0;

}
