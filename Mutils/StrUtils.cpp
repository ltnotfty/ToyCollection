//
// Created by xOx on 2023/4/4.
//

#include "StrUtils.h"

bool StrUtils::getLong(const std::string &str, long &val)
{
    return getLongBase(str, val, 10);
}

bool StrUtils::getLongLong(const std::string &str, long long &val)
{

    return getLongLongBase(str, val, 10);
}

bool StrUtils::getFloat(const std::string &str, float  &val)
{
    char *endPtr;

    float v;

    errno = 0;
    v = strtof(str.c_str(), &endPtr);

    if ( 0 != errno )
    {
        if (ERANGE == errno)
        {
            fprintf(stderr, "out of long range\n");
        }
        else
        {
            perror("strtof:");
        }
        return false;
    }
    if (endPtr == str)
    {
        fprintf(stderr, "no digit found\n");
        return false;
    }

    val = v;
    return true;
}

bool StrUtils::getDouble(const std::string &str, double  &val)
{
    char *endPtr;
    double v;

    errno = 0;
    v = strtod(str.c_str(), &endPtr);

    if ( 0 != errno )
    {
        if (ERANGE == errno)
        {
            fprintf(stderr, "out of long range\n");
        }
        else
        {
            perror("strtod:");
        }
        return false;
    }
    if (endPtr == str)
    {
        fprintf(stderr, "no digit found\n");
        return false;
    }
    if (*endPtr != '\0')
    {
        fprintf(stderr, "append additional string %s", endPtr);
        return false;
    }

    val = v;
    return true;
}

void StrUtils::ltrim(std::string &str)
{
    str.erase(str.begin(), std::find_if(str.begin(), str.end(),[](char c)
    { return !std::isspace(c);}) );
}

void StrUtils::rtrim(std::string &str)
{
    str.erase(std::find_if(str.rbegin(), str.rend(), [](char c)
    {
        return !std::isspace(c);
    }).base(),
              str.end()
    );
}

void StrUtils::trim(std::string &str)
{
    StrUtils::ltrim(str);
    StrUtils::rtrim(str);
}

bool StrUtils::getLongBase(const std::string &str, long &val, int base)
{
    if (base < 0 || 1 == base || base > 32) {
        fprintf(stderr, "base error\n");
        return false;
    }

    char *endPtr;
    long v;

    errno = 0;
    v = strtol(str.c_str(), &endPtr, base);

    if ( 0 != errno ) {
        if (ERANGE == errno) {
            fprintf(stderr, "out of long range\n");
        }
        else {
            perror("strtol:");
        }
        return false;
    }
    if (endPtr == str) {
        fprintf(stderr, "no digit found\n");
        return false;
    }

    if (*endPtr != '\0') {
        fprintf(stderr, "append additional string %s", endPtr);
        return false;
    }


    val = v;
    return true;
}

bool StrUtils::getLongLongBase(const std::string &str, long long int &val, int base)
{
    char *endPtr;
    long long v;

    errno = 0;
    v = strtoll(str.c_str(), &endPtr, 10);

    if ( 0 != errno )
    {
        if (ERANGE == errno)
        {
            fprintf(stderr, "out of long range\n");
        }
        else
        {
            perror("strtol:");
        }
        return false;
    }
    if (endPtr == str)
    {
        fprintf(stderr, "no digit found\n");
        return false;
    }

    if (*endPtr != '\0')
    {
        fprintf(stderr, "append additional string %s", endPtr);
        return false;
    }


    val = v;

    return true;
}

bool StrUtils::getInt(const std::string &str, int &val)
{
    long lval = 0;
    if ( !getLongBase(str, lval, 10) )
        return false;

    if (lval > INT_MAX || lval < INT_MIN)
        return false;

    val = static_cast<int>(lval);
    return true;
}

bool StrUtils::isHexStr(const std::string &str)
{
    std::size_t length = str.size();
    if (!length)
        return false;

    std::string aStr = str;
    toUpper(aStr);

    // 可以0x开头
    std::size_t offSet = 0;
    if (length > 2 && aStr[0] == '0' && aStr[1] == 'X')
        offSet = 2;


    return std::find_if_not(aStr.begin() + offSet, aStr.end(),
                        [](char c)->bool
                        {
                            if ( c >= 'A' && c <= 'F')
                                return true;
                            if ( c >= '0' && c <= '9')
                                return true;
                            return false;
                        }
    ) == aStr.end();

}

void  StrUtils::toUpper(std::string &str)
{
    std::transform(str.begin(), str.end(), str.begin(),
                   [](char c) {
                       return static_cast<char>(::toupper(c));
                   });
}

char StrUtils::toBitVal(char c) {

    char tc = static_cast<char> (toupper(c));

    if (tc >= 'A')
        tc = tc - 'A' + 10;
    else
        tc = tc - '0';

    return tc;
}


