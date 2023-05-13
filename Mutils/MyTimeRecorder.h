//
// Created by xOx on 2023/3/2.
//

#ifndef TESTME_MYTIMERECORDER_H
#define TESTME_MYTIMERECORDER_H


#include <cstdio>



#if __cplusplus >= 201103L
#include <chrono>
#else
#include <time.h>
#include <cstdlib>
#endif


class MyTimeRecorder
{

public:
    explicit MyTimeRecorder();
    ~MyTimeRecorder();

    void lastTime();

#if __cplusplus >= 201103L
private:
    std::chrono::time_point<std::chrono::high_resolution_clock> beginTimePoint;
    std::chrono::time_point<std::chrono::high_resolution_clock> endTimePoint;
public:
    void C11_lastTime(const std::chrono::time_point<std::chrono::high_resolution_clock> &beginTime,
                      const std::chrono::time_point<std::chrono::high_resolution_clock> &endTime);

#else
    private:
    struct timespec beginTimePoint;
    struct timespec endTimePoint;
public:
void C98_lastTime(const timespec & beginTime, const timespec & endTime);
#endif

};
#endif //TESTME_MYTIMERECORDER_H
