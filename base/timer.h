#pragma once

#include <chrono>

class Timer
{
private:
    using TimeType = std::chrono::time_point<std::chrono::high_resolution_clock>;


    static TimeType startTime;
    static TimeType stopTime;

public:
    Timer(/* args */) = default;
    ~Timer() = default;

    static void Start()
    {
        startTime = std::chrono::high_resolution_clock::now();
    }

    static void End()
    {
        stopTime = std::chrono::high_resolution_clock::now();
    }

    static float Duration()
    {
        return std::chrono::duration<float, std::chrono::seconds::period>(stopTime - startTime).count();
    }
};
