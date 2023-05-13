//
// Created by xOx on 2023/4/18.
//

#include "YamlConfig.h"


bool YamlConfig::has(const std::string &key)
{
    return node[key].IsDefined();
}


bool YamlConfig::readConfFile(const char *file)
{
    if(nullptr == file || file[0] == 0){
        std::cout << "empty file read" << std::endl;
        return false;
    }


    node = YAML::LoadFile(file);
    return true;
}


bool YamlConfig::getConfig()
{
    bool ret;
    if (m_searchFor)
    {
        std::string str = iConfig::searchConfFile(m_file.c_str());
        std::cout << str << std::endl;
        ret = readConfFile(str.c_str());
    }
    else
    {
        ret = readConfFile(m_file.c_str());
    }
    if (!ret)
    {
        std::cerr << "文件打开或读取失败: " << m_file << std::endl;
    }
    return ret;
}


int YamlConfig::optInt(const std::string &key, int dft)
{
    if (has(key) && node[key].IsScalar())
        return node[key].as<int>();

    return dft;
}

long YamlConfig::optLong(const std::string& key, long dft)
{
    if (!YamlConfig::has(key))
        return dft;
    return node[key].as<long>();
}

bool YamlConfig::optBool(const std::string& key, bool dft)
{
    if (!YamlConfig::has(key))
        return dft;
    return node[key].as<bool>();
}

float YamlConfig::optFloat(const std::string& key, float dft)
{
    if (!YamlConfig::has(key))
        return dft;
    return node[key].as<float>();
}

double YamlConfig::optDouble(const std::string &key, double dft)
{
    if (!YamlConfig::has(key))
        return dft;
    return node[key].as<double >();
}

YamlConfig::YamlConfig(const char *fileName, bool searchFile) : iConfig(fileName, searchFile)
{

}

YamlConfig::~YamlConfig()
{

}

iConfig::ConfType YamlConfig::getConfFileType() {
    return iConfig::YAML_CONF;
}


