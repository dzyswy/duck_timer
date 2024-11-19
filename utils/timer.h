#pragma once

#include <string>
#include <iostream>
#include <iomanip> 
#include <mutex>
#include <condition_variable>
#include <thread>
#include <chrono>
#include <functional>
#include <glog/logging.h>

namespace duck {
namespace utils {


class Timer
{
public:
    Timer(long period_ms, int repeat = -1) : period_ms_(period_ms), repeat_(repeat), quit_(true) {}
    ~Timer() {
        stop();
    }
    

    void process() {
        while(true)
        {
            long t0 = now_ms();
            func_();
            long t1 = now_ms();
            long used_ms = (t1 > t0) ? (t1 - t0) : (t0 - t1);
            long diff_ms = period_ms_ - used_ms;
            std::chrono::milliseconds ms(diff_ms);
            std::this_thread::sleep_for(ms);

            if (quit_) {
                break;
            }
        }
    }

    void start() {
        quit_ = false;
        thread_ = std::thread(Timer::thread_handle, this);
    }

    void stop() {
        quit_ = true;
        if (thread_.joinable()) {
            thread_.join();
        }
    }

    template<typename F, typename... Args>
    void submit(F && func, Args&&... args) {
        auto ff = std::bind(std::forward<F>(func), std::forward<Args>(args)...);
        func_ = ff;
    }

    long now_ms() {
        auto now = std::chrono::high_resolution_clock::now();
        auto duration = std::chrono::duration_cast<std::chrono::milliseconds>(now.time_since_epoch());
        long ms = duration.count();
        return ms;
    }

public:
    static void thread_handle(Timer* timer) {
        timer->process();
    }

protected:
    long period_ms_;
    int repeat_;
    bool quit_;
    std::thread thread_;
    std::function<void()> func_;
    
};

}//namespace utils
}//namespace duck












