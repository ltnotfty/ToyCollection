//
// Created by xOx on 2023/4/4.
//

#ifndef TESTME_STRUTILS_H
#define TESTME_STRUTILS_H

#include <unistd.h>
#include <cstdio>
#include <cerrno>
#include <cstdlib>
#include <string>
#include <climits>

#include <algorithm>

class StrUtils
{
public:

    static bool getInt(const std::string &str, int &val);
    static bool getLong(const std::string &str, long int &val);
    static bool getLongLong(const std::string &str, long long &val);
    static bool getFloat(const std::string &str, float  &val);
    static bool getDouble(const std::string &str, double  &val);

    static bool getLongBase(const std::string &str, long int &val, int base);
    static bool getLongLongBase(const std::string &str, long  long &va, int base);


    static void toUpper(std::string& str);


    /// \brief transfer ascii val to original val
    /// \example 'e' => 14, 'a' => 10
    static char toBitVal(char c);

    /// \brief judge it is a legal hex string
    /// \example
    ///  0x1aef => true
    /// 1w212. => false
   static bool isHexStr(const std::string &str);



    static void ltrim(std::string &str);
    static void rtrim(std::string &str);
    static void trim(std::string &str);



};


#endif //TESTME_STRUTILS_H
