//
// Created by xOx on 2023/4/18.
//

#ifndef TESTME_YAMLCONFIG_H
#define TESTME_YAMLCONFIG_H

#include "iConfig.h"
#include "yaml-cpp/yaml.h"
#include <algorithm>


class YamlConfig:private iConfig
{
public:
    explicit YamlConfig(const char *fileName, bool searchFile = false);
    ~YamlConfig();

    bool getConfig() final;

    int optInt(const std::string &key, int dft);
    long optLong(const std::string& key, long dft);
    bool optBool(const std::string& key, bool dft);
    float optFloat(const std::string& key, float dft);
    double optDouble(const std::string &key, double dft) ;
    bool has(const std::string &key) final;
    enum ConfType getConfFileType() final;
    bool readConfFile(const char *fileName) final;




    template<typename T>
    std::vector<T> getArrOf(const std::string& key) ;


    template<typename T>
    T recurGet(const std::string& hStr, T dft);

private:
    YAML::Node node;
};
template<typename T>
std::vector<T> YamlConfig::getArrOf(const std::string& key)
{
    std::vector<T> ret;
    if ( has(key) && node[key].IsSequence()) {

        T tmp;
        for (auto i = 0;i < node[key].size(); ++i) {
            tmp = node[key][i].as<T>();
            ret.push_back(tmp);
        }
    }


    return ret;
}

template<typename T>
T YamlConfig::recurGet(const std::string& hStr, T dft)
{
    if (!hStr.size())
        return dft;


    std::size_t bPos = 0;
    std::size_t ePos = 0;
    std::size_t sz = hStr.size();

    YAML::Node tmpNode;
    tmpNode.push_back(node);
    std::string tmpStr;

    while (ePos < sz) {

        ePos = hStr.find_first_of('.', bPos);
        ePos = std::min(sz, ePos);

        tmpStr = hStr.substr(bPos, ePos - bPos);

        if (!tmpNode[tmpStr].IsDefined())
            return dft;
        tmpNode = tmpNode[tmpStr];
        bPos = ePos + 1;
    }

    return  tmpNode.as<T>();
}



#endif //TESTME_YAMLCONFIG_H
