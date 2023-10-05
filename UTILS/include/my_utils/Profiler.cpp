#include "Profiler.hpp"
#include <string>

// Profiler profiler;
Profiler::Profiler() { }

Profiler* Profiler::getInstance()
{
    if (instance_ == nullptr) {
        instance_ = new Profiler();
    }
    return instance_;
}

void Profiler::AddSample(Sample sample)
{
    // it will make stuff slower but now there is 0% probability to do a double push_back;
    mxSamples.lock();
    for (size_t i = 0; i < samples.size(); i++) {
        if (sample.name == samples[i].name) {
            samples[i].nsTime += sample.nsTime;
            mxSamples.unlock();
            return;
        }
    }
    samples.push_back(sample);
    mxSamples.unlock();
}

std::string Profiler::getTimingsAsString(bool doClearSamples)
{
    std::string retString = "";
#ifdef DEBUG
    retString = "DEBUG TIMINGS!!!\n ";
#endif

    std::vector<Sample> localSamples = getTimings(doClearSamples);
    long time = 0;
    for (size_t i = 0; i < localSamples.size(); i++) {
        mxSamples.lock();
        retString += localSamples[i].name;
        retString += ": ";
        time = localSamples[i].nsTime;
        mxSamples.unlock();
        retString += std::to_string(time) + "ns.  ";
        time /= 1000000; // change to ms.
        if (time >= 1) {
            retString += std::to_string(time) + "ms.  ";
            time /= 1000; // change to s.
            if (time >= 1) {
                retString += std::to_string(time) + "s.";
            }
        }
        retString += "\n";
    }
    if (localSamples.size()) {
        return retString;
    } else {
        return "no timings";
    }
}

std::vector<Sample> Profiler::getTimings(bool doClearSamples)
{
    std::vector<Sample> retSample;

    mxSamples.lock();
    for (size_t i = 0; i < samples.size(); i++) {
        retSample.push_back(Sample(samples[i].name, samples[i].nsTime));
    }
    mxSamples.unlock();
    if (doClearSamples) {
        clearSamples();
    }

    return retSample;
}

void Profiler::clearSamples()
{
    mxSamples.lock();
    samples.clear();
    mxSamples.unlock();
}

void Profiler::printProfilerData(bool doClearSamples)
{
    for (size_t i = 0; i < samples.size(); i++) {
        std::cout << samples[i].name << ": " << samples[i].nsTime << "ns" << std::endl;
    }
    if (doClearSamples) {
        clearSamples();
    }
}

Profiler::~Profiler()
{
    clearSamples();
    if (instance_) {
        delete instance_;
    }
}

Profiler* Profiler::instance_;

PTimer::PTimer(std::string name)
{
    sample.name = name;
    startTime = std::chrono::system_clock::now();
}

PTimer::~PTimer()
{
    sample.nsTime = std::chrono::duration<long, std::nano>(std::chrono::system_clock::now() - startTime).count();
    Profiler::getInstance()->AddSample(sample);
}
