//
// Created by xOx on 2023/3/15.
//

#include "OSUtils.h"
#define MAX_PATH_LENTH 256

void OSUtils::printPwd()
{
    char PathBuf[MAX_PATH_LENTH];
    if ( !getcwd(PathBuf, MAX_PATH_LENTH))
    {
        printf ("can not determine path\n");
    }
    else
    {
        printf ("current work dir is: %s\n", PathBuf);
    }
}

std::string OSUtils::getPwd()
{
    char PathBuf[256];

    std::string pathStr;

    if ( getcwd(PathBuf, MAX_PATH_LENTH))
    {
        pathStr.push_back('"');
        pathStr.append(PathBuf);
        pathStr.push_back('"');
    }
    return pathStr;
}

bool OSUtils::isFileExist(const char *path_to_file)
{
    return access( path_to_file, R_OK ) == 0;
}
