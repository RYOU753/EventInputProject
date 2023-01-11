#include <algorithm>
#include "Timer.h"

Timer::Timer(float limit, float currenttime):limitTime_(limit), currentTime_(currenttime), resetCounter_(0)
{
    currentTime_ = currenttime;
    limitTime_ = limit;
}

Timer::~Timer()
{
}

void Timer::Update(const double& delta)
{
    if (!IsTimeOver())
    {
        currentTime_ += static_cast<float>(delta);
    }
    else
    {
        currentTime_ = limitTime_;
    }
}

bool Timer::IsTimeOver()
{
    return currentTime_ > limitTime_;
}

float Timer::NormalizedTime()
{
    return  std::clamp(currentTime_ / limitTime_,0.0f,1.0f);
}

float Timer::GetDurationTime()
{
    return currentTime_;
}

float Timer::InversNormalizedTime()
{
    return std::max(0.0f,1.0f - NormalizedTime());
}

float Timer::InversTime()
{
    return std::max(0.0f,limitTime_ - currentTime_);
}

void Timer::ResetTime()
{
    currentTime_ = 0.0f;
    resetCounter_++;
}

void Timer::SetTime(float time)
{
    currentTime_ = time;
}

void Timer::SetLimitTime(float limit)
{
    limitTime_ = limit;
}
const float& Timer::GetLimitTime(void)
{
    return limitTime_;
}
const int& Timer::GetResetCount(void)
{
    return resetCounter_;
}
