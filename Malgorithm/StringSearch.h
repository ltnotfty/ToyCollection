//
// Created by xOx on 2023/3/3.
//

#ifndef TESTME_STRINGSEARCH_H
#define TESTME_STRINGSEARCH_H


#include <vector>
#include <string>
#include <list>
#include <iostream>
#include <array>

#include <cstring>

constexpr static uint8_t ALPHABET_LEN = 255;

std::string
Manacher(const std::string &str);

std::list<int>
KMP(const std::string &txtString, const std::string &patString);

void
KMP_getNext(const std::string &patString, std::vector<int> &next);




bool BM_isPrefix(const std::string &patStr, int pos);

int  BM_suffixIndex(const std::string &patStr, int misPos);


int BM_makeDelta1(std::vector<int> &deltaArr1, const std::string &patStr);


int BM_makeDelta2(std::vector<int> &deltaArr2, const std::string &patStr);


int BM(const std::string  &txtStr, const std::string &patStr);

#endif //TESTME_STRINGSEARCH_H
