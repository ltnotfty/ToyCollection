//
// Created by xOx on 2023/3/2.
//

#include "MyTimeRecorder.h"


MyTimeRecorder::MyTimeRecorder()
{
#if __cplusplus  >= 201103L
    this->beginTimePoint = std::chrono::high_resolution_clock::now();
#else
    if ( -1 == clock_gettime(CLOCK_MONOTONIC, &beginTimePoint) )
        {
            perror("clock_gettime: ");
            exit(EXIT_FAILURE);
        }
#endif
}
MyTimeRecorder::~MyTimeRecorder()
{
#if __cplusplus  >= 201103L
    this->endTimePoint = std::chrono::high_resolution_clock::now();
#else
    if ( -1 == clock_gettime(CLOCK_MONOTONIC,  &endTimePoint) )
        {
            fprintf(stderr, "clock_gettime error\n");
            exit(EXIT_FAILURE);
        }
#endif
    lastTime();
}

void MyTimeRecorder::lastTime()
{
#if __cplusplus >= 201103L
    C11_lastTime(this->beginTimePoint, this->endTimePoint);
#else
    C98_lastTime(this->beginTimePoint, this->endTimePoint);
#endif
}

#if __cplusplus < 201103L
void MyTimeRecorder::C98_lastTime(const timespec & beginTime, const timespec & endTime)
{
    if (beginTime.tv_sec > endTime.tv_sec ||
        (beginTime.tv_sec == endTime.tv_sec && beginTime.tv_nsec > endTime.tv_nsec) )
    {
        printf("warning: beginTime > endTime\n");
        return C98_lastTime(endTime, beginTime);
    }

    double totalSec = (endTime.tv_sec - beginTime.tv_sec);
    long long lastNsec = endTime.tv_nsec - beginTime.tv_nsec;
    if (lastNsec < 0)
    {
        lastNsec += 1000000000;
        --totalSec;
    }

    while (lastNsec >= 1000000000)
    {
        ++totalSec;
        lastNsec -= 1000000000;
    }
    totalSec += ((double) lastNsec)/1000000000;

    printf("last Time: %.9lf\n", totalSec);
}

#else
void MyTimeRecorder::C11_lastTime(const std::chrono::time_point<std::chrono::high_resolution_clock> &beginTime,
                                  const std::chrono::time_point<std::chrono::high_resolution_clock> &endTime)
{
    using namespace std::chrono;
    duration<double> lastSec = duration_cast<duration<double>>(endTime - beginTime);

    printf("last Time: %.9lf\n", lastSec.count());
}

#endif