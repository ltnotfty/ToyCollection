//
// Created by xOx on 2023/3/15.
//

#ifndef TESTME_OSUTILS_H
#define TESTME_OSUTILS_H

#include <unistd.h>
#include <cstdio>
#include <string>
#include <sys/stat.h>



class OSUtils
{
public:
    static void printPwd();

    static bool isFileExist(const char *path_to_file);
    static std::string getPwd();

};


#endif //TESTME_OSUTILS_H
