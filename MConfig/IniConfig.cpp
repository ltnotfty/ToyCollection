//
// Created by xOx on 2023/4/18.
//

#include "IniConfig.h"

using namespace std;

bool IniConfig::readConfFile(const char *file)
{
    if(nullptr == file || file[0] == 0){
        std::cout << "empty file read" << std::endl;
        return false;
    }

    UnorderedMap<std::string, string> refMap;
    bool ret = parseIniFile(file, refMap);
    if(ret)
    {
        for (auto iter = refMap.getMap()->begin();iter != refMap.getMap()->end(); ++iter)
        {
            std::string & refKey = iter->second;
            if (has(refKey)) {
                mConfigMap.setItem(iter->first, mConfigMap.getOrNew(refKey));
            }else {
                throw runtime_error("no ref value, ref key is " + refKey);
            }
        }
    }
    return ret;
}




IniConfig::IniConfig(const char* file, bool searchFor): iConfig(file, searchFor)
{
}

IniConfig::~IniConfig()
{
    mConfigMap.clear();
}


bool IniConfig::parseIniFile(const std::string & file, UnorderedMap<string, string> & refMap)
{
    if(file.length() == 0){
        return false;
    }
    ifstream fis(file, std::ios::in);
    if(!fis){
        cerr << "文件打开失败: " << file << endl;
        return false;
    }


    char buf[500];
    int line_n = 0;
    string node_name;
    string key;
    string value;

    try {
        while( fis.getline(buf, sizeof(buf)) ){
            line_n++;

            string line = buf;
            trim(line);

            if (line.length() == 0 ) {
                continue;
            }

            switch (line[0]) {
                case '#': continue;

                case '[':
                    if(']' == line.back()){
                        line.erase(0, 1);
                        line.pop_back();
                        trim(line);
                        if (line.length() == 0) {
                            throw runtime_error("domain name is empty.");
                        }else {
                            node_name = line + ".";
                        }
                    }else {
                        throw runtime_error("domain format error");
                    }
                    break;

                case '.':
                    line = line.substr(1);
                    trim(line);
                    if (line.length() == 0) {
                        throw runtime_error("import file error, no file");
                    }
                    if (!parseIniFile(line, refMap)) {
                        throw runtime_error("import file error, ref cfg file not exists");
                    }
                    break;

                default:
                    int n = line.find('=') ;
                    if ( n > 0 ) {
                        int m ;
                        bool isRef = false;
                        if (line[n - 1] == '<') {	//  a <= b  , 引用其他key的value
                            isRef = true;
                            m = n - 1;
                        }else {
                            m = n;
                        }
                        key = line.substr(0, m);
                        trim(key);
                        if(key.length() == 0) {
                            throw runtime_error("no key string");
                        }
                        if(node_name.length() > 0){
                            key = node_name + key;
                        }
                        value = line.substr(n + 1);
                        trim(value);
                        if(isRef) {
                            if (value.length() == 0) {
                                throw runtime_error("no ref key");
                            }
                            refMap.setItem(key, value);
                        }
                        else
                        {
                            mConfigMap.setItem(key, value);
                        }
                    }else {
                        throw runtime_error("cannot parse config file");
                    }
                    break;
            }
        }
    }
    catch (exception& e) {
        throw runtime_error(string(e.what()) + "   at line " + to_string(line_n));
    }

    return true;
}


string & IniConfig::optString(const string & key, string & def)
{
    return mConfigMap.getItemDefault(key, def);
}


long IniConfig::optLong(const string & key, long def)
{
    string v;
    if(mConfigMap.getItem(key, &v)){
        return parseLong(v);
    }else{
        return def;
    }
}

bool IniConfig::has(const string & key)
{
    return mConfigMap.hasItem(key);
}

string& IniConfig::trim(string& s)
{
    if (s.empty()){
        return s;
    }
    const char* blanks = " \t\r\n";

    s.erase(s.find_last_not_of(blanks) + 1);
    s.erase(0, s.find_first_not_of(blanks));
    return s;
}


bool IniConfig::optBool(const string & key, bool def)
{
    if(mConfigMap.hasItem(key)){
        return getBool(key);
    }else{
        return def;
    }
}

bool IniConfig::getBool(const string & key)
{
    string & s = mConfigMap.getItemDefault(key, "");

    if(s == "true"){
        return true;
    }else if(s == "false"){
        return false;
    }else{
        return stoi(s, nullptr, 0) != 0;
    }
}


long IniConfig::parseLong(string& s)
{
    if(s.find_first_of("_*") == string::npos){
        return stol(s, nullptr, 0);
    }

    long value = 1;
    string tmp;
    tmp.reserve(20);

    for (char & c : s){
        if(c == '_' || c == ' '){
            continue;
        }else if(c == '*'){
            if(tmp.length() > 0){
                value *= stol(tmp, nullptr, 0);
                tmp.clear();
            }else{
                throw runtime_error("numeric format error");
            }
        }else{
            tmp.push_back(c);
        }
    }

    if(tmp.length() > 0){
        return value * stol(tmp, nullptr, 0);
    }else{
        throw runtime_error("numeric format error");
    }
}

string IniConfig::searchConfigFile(const string &filename)
{
    const char * searchDirs[] = {"", "./conf/", "../conf/", "/home/workspace/conf/"};

    for (const auto &dir : searchDirs) {

        auto file = dir + filename ;
        if (access( file.c_str(), R_OK ) == 0) {

            return file;
        }
    }
//    return filename;
    return "";
}

string IniConfig::domainKey(const string &domain, const string &key)
{
    return domain + "." + key;
}

float IniConfig::optFloat(const std::string &key, float dft)
{
    if (!has(key))
        return dft;
    float ret;
    if (!StrUtils::getFloat(key, ret))
        return dft;
    return ret;
}

double IniConfig::optDouble(const std::string &key, double dft)
{
    if (!has(key))
        return dft;
    double ret;
    if (!StrUtils::getDouble(key, ret))
        return dft;
    return ret;
}

bool IniConfig::getConfig()
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

int IniConfig::optInt(const std::string &key, int dft)
{
    int ret = 0;
    if (!has(key) || !StrUtils::getInt(key, ret))
        return dft;

    return ret;
}


