#include "FrameTimer.h"
using namespace std::chrono;

FrameTimer::FrameTimer()
{
	last = steady_clock::now();
}

float FrameTimer::getDeltaSeconds()
{
	auto temp = last;
	last = steady_clock::now();
	duration<float> frameCount = last - temp;
	return frameCount.count();
}