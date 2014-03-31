#include "GameTimer.h"


GameTimer::GameTimer(LARGE_INTEGER start, LARGE_INTEGER frequency)
{
	startTime = GetTime(start,frequency);
	latestFrame = startTime;
	this->start = start;
	freq = frequency;
}


GameTimer::~GameTimer(void)
{
}

float GameTimer::getDeltaT()
	{
		float t1 = GetTime(start,freq);
		float answer = t1-latestFrame;
		latestFrame = t1;
		return answer;
	}