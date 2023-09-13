#pragma once

#include <chrono>

class Timer
{
private:

    using Type = std::chrono::time_point<std::chrono::high_resolution_clock>;

    Type  startTime;
    Type  stopTime;

public:
    Timer(/* args */) = default;
    ~Timer() = default;

    Type Start()
    {
        startTime = std::chrono::high_resolution_clock::now();

        return startTime;
    }

    Type End()
    {
        stopTime = std::chrono::high_resolution_clock::now();

        return stopTime;
    }

    float Duration()
    {
        return std::chrono::duration<float, std::chrono::seconds::period>(stopTime - startTime).count();
    }
};
