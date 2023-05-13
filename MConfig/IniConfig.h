//
// Created by xOx on 2023/4/18.
//

#ifndef TESTME_INICONFIG_H
#define TESTME_INICONFIG_H

#include "../MDataStruct/UnorderedMap.h"
#include "iConfig.h"
#include <fstream>

#include "StrUtils.h"

#define GEN_DOMAIN_FUN(RET, NAME) \
    RET NAME(const string & key); \
    RET NAME(const string & domain, const string & key) {return NAME(domainKey(domain, key));}

#define GEN_DOMAIN_FUN_OPT(RET, NAME, DEF) \
    RET NAME(const string & key, RET def=DEF); \
    RET NAME(const string & domain, const string & key, RET def=DEF) \
    {return NAME(domainKey(domain, key), DEF);}

class IniConfig:public iConfig
{
    public:
        explicit IniConfig(const char* file = nullptr, bool searchFor = false);
        ~IniConfig() ;

        virtual bool getConfig();

        int optInt(const std::string &key, int dft) final;
        long optLong(const std::string& key, long dft) final;
        bool optBool(const std::string& key, bool dft) final;
        float optFloat(const std::string& key, float dft) final;
        double optDouble(const std::string &key, double dft) final;
        bool has(const std::string &key) final;
        enum ConfType getConfFileType() final
        { return INI_CONF; }
        bool readConfFile(const char *fileName) final;




         bool getBool(const string & key);

        std::string & optString(const std::string & key, std::string & def);
        std::string & optString(const std::string & domain, const std::string & key, std::string & def)
        {
            return optString(domainKey(domain, key), def);
        }

        static string domainKey(const string & domain, const string & key);
        static string searchConfigFile(const string & filename);
        static string& trim(string &s);
    private:

        UnorderedMap<string, string> mConfigMap;
        bool parseIniFile(const string & file, UnorderedMap<string, string> & refMap);
        static long parseLong(string& s);

};


#endif //TESTME_INICONFIG_H
