#ifndef PROFILER_HPP
#define PROFILER_HPP

#include <chrono>
#include <ctime>
#include <fcntl.h>
#include <iostream>
#include <mutex>
#include <string>
#include <sys/mman.h>
#include <sys/time.h>
#include <unistd.h>
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
protected:
    std::mutex mxSamples;
    std::vector<Sample> samples;
    static Profiler* instance_;
    ~Profiler();
    Profiler();

protected:
public:
    static Profiler* getInstance();
    Profiler(Profiler& other) = delete;
    void operator=(const Profiler&) = delete;

    // static Profiler* getInstance();
    void AddSample(Sample sample);

    std::string getTimingsAsString(bool doClearSamples = true);
    std::vector<Sample> getTimings(bool doClearSamples = true);

    void clearSamples();
    void printProfilerData(bool doClearSamples = true);
};
// extern Profiler profiler;

#define TOKENPASTE(x, y) x##y
#define TOKENPASTE2(x, y) TOKENPASTE(x, y)
// use for acurate creation to block end timing cant be used in return scope //TODO deal with that problem
#define newTimer(name) PTimer TOKENPASTE2(Timer_, __LINE__) = PTimer(name)
// use by throwing newTimer({string name}) into code block, it will measure to the end of a block
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
