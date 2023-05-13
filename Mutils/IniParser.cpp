//
// Created by xOx on 2023/4/3.
//

#include "IniParser.h"



IniParser::IniParser(const char * fileName):m_File(std::move(std::string(fileName)))
{

}
bool IniParser::open(const char *filename)
{

    if (m_ifStream.is_open())
    {
        m_File.clear();
        m_ifStream.close();
    }

    m_ifStream.open(filename, std::ios::in);
    if (!m_ifStream.good())
    {
        return false;
    }

    m_File = std::move(std::string(filename));
    return true;
}
bool IniParser::parse(const char  *filename)
{
    if (!open(filename))
    {
        fprintf(stderr, "file open error\n");
        return false;
    }

    std::string lineStr;
    while (getline(m_ifStream, lineStr).good())
    {
        if (!parseLine(lineStr))
        {
            fprintf(stderr, "parse failed\n");
            return false;
        }
    }

    return true;
}

bool IniParser::parseLine(std::string &str)
{

    StrUtils::trim(str);

    if ( str.empty())
    {
        fprintf(stdout, "space line\n");
        return true;
    }
    if (parseCommentLine(str))
    {
        fprintf(stdout, "comment line\n");
        return true;
    }
    if (parsePairLine(str))
    {
        fprintf(stdout, "pair line");
        return true;
    }
    if (parseSecLine(str))
    {
        fprintf(stdout, "sec line");
        return true;
    }

    fprintf(stdout, "syntax error\n");
    return false;
}



bool IniParser::isLegalVal(const std::string &str) const
{
    if (str.empty())
        return false;

    return std::find_if(str.begin(), str.end(), [](char c) {
        if (!std::isalpha(c) &&
            !std::isdigit(c)&&
            c != '.' &&
            c != '+' &&
            c != '-')
            return false;
        return true;
    }) != str.end();

}



bool IniParser::parseCommentLine(const std::string  &str)
{
    return IniParser::isCommentChar(*str.begin());
}



bool IniParser::parsePairLine(const std::string &str)
{
    if (str.empty())
        return false;

    std::size_t ePos = str.find('=');
    if (ePos == std::string::npos)
    {
        fprintf(stdout, "no equal operator\n");
        return false;
    }


    std::string mKey = str.substr(0, ePos);
    StrUtils::rtrim(mKey);
    if (!isLegalKey(mKey))
    {
        fprintf(stdout, "not a legal key\n");
        return false;
    }

    std::string mVal = str.substr(ePos + 1, str.size() - ePos - 1);
    StrUtils::ltrim(mVal);
    if (!isLegalVal(mVal))
    {
        fprintf(stdout, "not a legal value\n");
        return false;
    }


    if (m_KVPair.find(mKey) != m_KVPair.end())
    {
        fprintf(stdout, "a duplicate key\n");
        return false;
    }

    fprintf(stdout, "key: %s, val: %s\n", mKey.c_str(), mVal.c_str());
    m_KVPair.insert({mKey,mVal});

    return true;
}



bool IniParser::parseSecLine(const std::string &str)
{
    if (str.empty())
        return false;

    if (*str.begin() == '[')
    {
        if ( *str.rbegin() == ']')
        {
            std::string tmpStr = str.substr(0, str.size() - 1);

            if (!isLegalVal(tmpStr))
            {
                fprintf(stdout, "have illegal character!");
                return false;
            }

            m_secStr = std::move(tmpStr);

            fprintf(stdout, "secStr: %s\n", m_secStr.c_str());
            return true;
        }
        else
        {
            fprintf(stdout, "[ not compared\n");
            return false;
        }
    }
    else
    {
        fprintf(stdout, "no [ found\n");
        return false;
    }
}


bool IniParser::getString(const std::string &key, std::string &str) const
{
    if (haveKey(key))
    {
        str = m_KVPair.at(key);
        return true;
    }
    else
    {
        fprintf(stdout, "no related key\n");
        return false;
    }
}

bool IniParser::getLong(const std::string &key, long &val) const
{
    if (haveKey(key))
    {
        return StrUtils::getLong(m_KVPair.at(key).c_str(), val);
    }
    else
    {
        fprintf(stdout, "no related key\n");
        return false;
    }
    return true;
}
bool IniParser::getFloat(const std::string &key, float  &val) const
{
    if (haveKey(key))
    {
        std::string tmpStr = m_KVPair.at(key);
        return StrUtils::getFloat(tmpStr.c_str(), val);
    }
    else
    {
        fprintf(stdout, "no related key\n");
        return false;
    }
}
bool IniParser::haveKey(const std::string &k) const
{
    return m_KVPair.find(k) != m_KVPair.end();
}

bool IniParser::isLegalKey(const std::string &str) const
{
    return std::find_if(str.begin(), str.end(), [](char c)
    {
        return !std::isalnum(c);
    }) == str.end();
}




