#pragma once

#include <chrono>

//3秒の待機後に経過時間を計測するタイマー
class GameTimer
{
public:
    void Reset();
    void Start(int targetSeconds);
    void Update();
    double Stop();

    bool IsWaiting() const;
    bool IsRunning() const;
    bool IsStopped() const;
    int GetTargetSeconds() const;
    double GetElapsedSeconds() const;

private:
    using Clock = std::chrono::steady_clock;
    static constexpr double WAIT_SECONDS = 3.0;

    Clock::time_point startTime_{};
    double elapsedSeconds_ = 0.0;
    int targetSeconds_ = 0;

    bool waiting_ = false;
    bool running_ = false;
    bool stopped_ = false;
};
