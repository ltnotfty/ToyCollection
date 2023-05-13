//
// Created by xOx on 2023/4/18.
//

#ifndef TESTME_CONFIG_H
#define TESTME_CONFIG_H

#include <string>
#include "OSUtils.h"
#include <iostream>

class iConfig
{
public:

    enum ConfType {INI_CONF,YAML_CONF};
    explicit iConfig(const char *fileName, bool searchFile);
    virtual ~iConfig();

    virtual bool getConfig();

    virtual int optInt(const std::string &key, int dft) = 0;
    virtual long optLong(const std::string& key, long dft) = 0;
    virtual bool optBool(const std::string& key, bool dft) = 0;
    virtual float optFloat(const std::string& key, float dft) = 0;
    virtual double optDouble(const std::string &key, double dft) = 0;
    virtual bool has(const std::string &key) = 0;
    virtual  enum ConfType getConfFileType() = 0;
    virtual bool readConfFile(const char *fileName);


    static  const std::string searchConfFile(const char *filename);

protected:
    std::string m_file;
    bool m_searchFor;
};


#endif //TESTME_CONFIG_H
