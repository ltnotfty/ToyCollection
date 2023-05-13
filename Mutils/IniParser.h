//
// Created by xOx on 2023/4/3.
//

#ifndef TESTME_INIPARSER_H
#define TESTME_INIPARSER_H

#include <unordered_map>
#include <string>
#include <fstream>
#include <algorithm>

#include "StrUtils.h"

class IniParser
{
public:
    explicit IniParser(const char * fileName = "");

    bool parse(const char *filename);


    static constexpr bool isCommentChar(char c)
    { return c == '#' || c == ';'; }

    bool getString(const std::string &key, std::string &str) const;
    bool getLong(const std::string &key, long &val) const;
    bool getFloat(const std::string &key, float &val) const;

    bool isLegalVal(const std::string &str) const;
    bool isLegalKey(const std::string &str) const;

    std::string getCurFile() const
    { return m_File;}
private:

    bool haveKey(const std::string &k) const;

    bool open(const char *filename);


    bool parseLine(std::string &str);

    bool parseCommentLine(const std::string  &str);
    bool parsePairLine(const std::string &str);
    bool parseSecLine(const std::string &str);


    std::string m_secStr;
    std::ifstream m_ifStream;
    std::string m_File;
    std::unordered_map<std::string, std::string> m_KVPair;
};


#endif //TESTME_INIPARSER_H
