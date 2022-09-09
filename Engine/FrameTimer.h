#pragma once
#include <chrono>

class FrameTimer
{
public:
	FrameTimer();
	float getDeltaSeconds();
private:
	std::chrono::steady_clock::time_point last;
};