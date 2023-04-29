#ifndef PROFILER_HPP
#define PROFILER_HPP

#include <chrono>
#include <ctime>
#include <iostream>
#include <mutex>
#include <string>
#include <sys/time.h>
#include <vector>
struct Sample {
    long nsTime;
    std::string name;
    Sample() { }
    Sample(std::string name) { this->name = name; }
    Sample(std::string name, long nsTime)
    {
        this->name = name;
        this->nsTime = nsTime;
    }
};

class Profiler
{
private:
    std::mutex mxSamples;
    std::vector<Sample> samples;
    static Profiler* profiler;

protected:
    Profiler();
    ~Profiler();

public:
    Profiler(Profiler& other) = delete;
    void operator=(const Profiler&) = delete;

    static Profiler* getInstance();
    void AddSample(Sample sample);
    std::string getTimingsAsString(bool doClearSamples = true);

    std::vector<Sample> getTimings(bool doClearSamples = true);

    void clearSamples();
    void printProfilerData(bool doClearSamples = true);
};

#define TOKENPASTE(x, y) x##y
#define TOKENPASTE2(x, y) TOKENPASTE(x, y)
// use for acurate creation to block end timing
#define newTimer(name) PTimer TOKENPASTE2(Timer_, __LINE__) = PTimer(name)
// use by throwing newTimer({string name}) into code block that has to be measured
class PTimer
{
private:
    Sample sample;
    std::chrono::_V2::system_clock::time_point startTime;

public:
    PTimer(std::string name);
    ~PTimer();
};

#endif // PROFILER_HPP
