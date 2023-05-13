//
// Created by xOx on 2023/4/18.
//

#include "iConfig.h"


iConfig::iConfig(const char *file, bool searchFor):m_file(file),m_searchFor(searchFor)
{

}


iConfig::~iConfig()
{

}



const std::string iConfig::searchConfFile(const char *filename)
{
    const char * searchDirs[] = {"", "./conf/", "../conf/", "/home/workspace/conf/"};


    std::cout << "!" <<std::string(filename) << "!" << std::endl;
    for (const auto &dir : searchDirs) {

        auto file = std::string(dir) + filename ;
        if (OSUtils::isFileExist(file.c_str())) {
            return file;
        }
    }

    return "";
}

bool iConfig::readConfFile(const char *fileName)
{
    perror( "using default readConfFile\n");
    return false;
}

bool iConfig::getConfig()
{
    return false;
}

