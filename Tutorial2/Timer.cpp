#include "Timer.h"

Timer::Timer()
{
	last = std::chrono::steady_clock::now();
}

float Timer::DeltaTime()
{
	const auto old = last;
	last = std::chrono::steady_clock::now();

	const std::chrono::duration<float> frameTime = last - old;

	return frameTime.count();
}

float Timer::PeekDelta() const
{
	return std::chrono::duration<float>(std::chrono::steady_clock::now() - last).count();
}