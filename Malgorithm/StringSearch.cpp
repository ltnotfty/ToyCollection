//
// Created by xOx on 2023/3/3.
//

#include "StringSearch.h"

/*
 * 关键点
 * 1) 奇偶对称中心
 * 2) 当前点的对称性
 *
 * 如果按照原始串来处理的话，要涉及到奇偶性的判断，所以我们可以添加字符使得原字符串长度为奇数。
 * 根据对称性质来进行优化的
 * 即如果一个点在最大对称中心覆盖的位置则，与它对称的点的对称长度有可能成为它的最大对称长度。
 * 为什么是有可能，因为
 * (1) 可以扩展
 * (2) 右边是有边界的
 */
std::string Manacher(const std::string &str)
{

    std::vector<int> pLenRec(str.size() + str.size() + 3, 1);
    std::string conStr(pLenRec.size(),0);

    /*构造伪字符串*/

    /*首尾特殊处理*/

    conStr[0] = '$';
    conStr[pLenRec.size() - 1] = '#';

    pLenRec[0] = pLenRec[pLenRec.size() - 1] = 1;


    for (int i = 1;i < pLenRec.size() - 1; ++i)
    {
        if (i % 2)
        {
            conStr[i] = '.';
        }
        else
        {
            conStr[i] = str[i / 2 - 1];
        }
        pLenRec[i] = 1;
    }

    int maxPos = 0;
    int maxExtLen = 1;

    int mostPos = 0;
    int mostExtLen = 1;

    for (int i = 1;i < pLenRec.size();++i)
    {
        int curExtLen = pLenRec[i];
        if (maxPos + maxExtLen > i)
        {
            curExtLen = std::min(mostPos + mostExtLen - i, pLenRec[maxPos + maxPos - i]);
        }

        while (i - curExtLen > -1 && i + curExtLen < pLenRec.size() &&
        conStr[i - curExtLen] == conStr[i + curExtLen])
            ++curExtLen;
        pLenRec[i] = curExtLen;

        if (i + curExtLen >= mostPos + mostExtLen)
        {
            mostPos = i;
            mostExtLen = curExtLen;
        }

        if (maxExtLen < curExtLen)
        {
            maxPos = i;
            maxExtLen = curExtLen;
        }
    }

    std::string ret;
    for (int i = maxPos - maxExtLen + 1; i < maxPos + maxExtLen;++i)
        if (conStr[i] != '.')
            ret.push_back(conStr[i]);

    return ret;
}

/*
 * 根据模式串本身的性质来进行移动的。
 * 主要的思想还是求当前字符位置之前字符串的最长公共前后缀长度。
 * 优化的思想主要是递归，即当适配时，若pat[i] == pat[next[i]]
 * 说明了会继续失配，直到不相等为止，则 next[j] = next[i]
 * 然后-1的引入优化了程序的结构，注意next数组的长度应该为patStr.size() + 1.
 */
void
KMP_getNext(const std::string &patString, std::vector<int> &next)
{
    next[0] = -1;
    next[1] =  0;
    int i = 0, j = 1;

    while (j < patString.size())
    {
        if (-1 == i || patString[i] == patString[j])
        {
            next[++j] = ++i;

            /*
             * 如果纯粹求最长公共前缀后缀，则应该放弃该优化。
             * 如果是为了单纯的匹配的话，则应该使用该优化。
             */
            if (patString[i] == patString[j])
                next[j] = next[i];
        }
        else
        {
            i = next[i];
        }
    }

}

std::list<int>
KMP(const std::string &txtString, const std::string &patString)
{

    std::vector<int> next(patString.size() + 1);
    KMP_getNext(patString, next);
    std::list<int> res;


    int i = 0;
    int j = 0;

    while (i < txtString.size())
    {
        if (-1 == j || txtString[i] == patString[j])
        {
            ++i, ++j;
        }
        else
        {
            j = next[j];
        }

        if (j == patString.size())
        {
            res.push_back(i - j);
            j = next[j];
        }
    }

    return res;
}






int  BM_suffixIndex(const std::string &patStr, int misPos)
{
    int pLen = (int) patStr.size();
    int i = misPos;
    int j = pLen - 1;

    for ( ; ~i; --i)
    {
        if (patStr[i] == patStr[j])
            --j;
        else
            j = pLen - 1;

        if (j == misPos)
            break;
    }

    return i;
}



bool BM_isPrefix(const std::string &patStr, int pos)
{
    int suffixLen = (int) patStr.size() - pos;

    return !strncmp(patStr.c_str(), patStr.c_str() + pos, suffixLen);
}
int BM_makeDelta1(std::vector<int> &deltaArr1, const std::string &patStr)
{

    int pLen = static_cast<int>(patStr.size());

    for (auto &v : deltaArr1)
        v =  -1;

    for (int i = 0;i < pLen; ++i)
        deltaArr1[patStr[i]] = pLen - 1 - i;

    return 0;
}



int BM_makeDelta2(std::vector<int> &deltaArr2, const std::string &patStr)
{
    /*第一种情况是已经匹配的最长后缀串未能匹配失配字符之前的部分模式串, 所以看模式串中的前缀能否与部分后缀匹配*/

    int pLen = patStr.size();
    for (int p = pLen - 1; ~p; --p)
    {
        if (BM_isPrefix(patStr,p + 1))
        {
            deltaArr2[p] = p + 1;
        }
    }

    /*第二种情况是，匹配了的后缀再次出现在之前的字符串中*/
    for (int i = pLen - 1; ~i; --i)
    {
        int rightMostPos = BM_suffixIndex(patStr, i);

        if (~rightMostPos)
        {
            deltaArr2[i] = i + 1 - rightMostPos;
        }
    }
    return 0;
}
int
BM(const std::string  &txtStr, const std::string &patStr)
{

    std::vector<int> Delta1Arr(256, 0);
    std::vector<int> Delta2Arr(patStr.size(), 0);


    BM_makeDelta1(Delta1Arr, patStr);
    BM_makeDelta2(Delta2Arr, patStr);

    int pLen = (int) patStr.size();
    int tLen = (int) txtStr.size();

    int bpos = 0;
    int mPos = pLen - 1;


    while (bpos + pLen < tLen + 1)
    {
        /*如果相等则继续匹配，直到整个串都匹配*/
        if (patStr[mPos] == txtStr[bpos + mPos])
        {
            --mPos;
        }
        else
        {
        /*如果不匹配，则需要调整文本串的位置。
         * 1) 若失配字符没有在模式串中出现，则移动文本串的开头位置应该越过该字符。
         * 2) 若失配字符在模式串中出现，还需要考虑是否已经匹配过。
         *      * 若已经匹配过，则只能将文本串向右移动一位
         *      * 若未匹配，则将文本串移动相应的位置(最右边出现的位置减去当前的位置)
         */
            if (mPos > Delta1Arr[txtStr[bpos + mPos]])
            {
                bpos += mPos - Delta1Arr[txtStr[bpos + mPos]];
            }
            else
            {
                ++bpos;
            }
            /*已经失配了，从头开始比较*/







            mPos = pLen - 1;
        }



    }





    return -1;
}


