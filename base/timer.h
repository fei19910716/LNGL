#pragma once

#include <chrono>

class Timer
{
private:

     std::chrono::time_point<std::chrono::high_resolution_clock> startTime;
     std::chrono::time_point<std::chrono::high_resolution_clock> stopTime;

public:
    Timer(/* args */) = default;
    ~Timer() = default;

     void Start()
    {
        startTime = std::chrono::high_resolution_clock::now();
    }

     void End()
    {
        stopTime = std::chrono::high_resolution_clock::now();
    }

     float Duration()
    {
        return std::chrono::duration<float, std::chrono::seconds::period>(stopTime - startTime).count();
    }
};
