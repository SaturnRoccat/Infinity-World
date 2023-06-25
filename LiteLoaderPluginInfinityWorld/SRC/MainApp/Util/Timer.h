#ifndef TIMER_H
#define TIMER_H

#include <chrono>

#include <llapi/LoggerAPI.h>

extern Logger logger;
class Timer {
public:
    Timer() : start_time_(std::chrono::high_resolution_clock::now()) {}

    ~Timer() {
        const auto end_time = std::chrono::high_resolution_clock::now();
        const auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time_);
        // logger.error( "Elapsed time:{} milliseconds", duration.count());
    }

    inline long long getTime() 
    {
        const auto end_time = std::chrono::high_resolution_clock::now();
        const auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(end_time - start_time_);

        start_time_ = end_time;
        return duration.count();
    }

private:
    std::chrono::time_point<std::chrono::high_resolution_clock> start_time_;
};

#endif  // TIMER_H
