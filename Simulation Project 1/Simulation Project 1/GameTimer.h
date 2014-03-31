#pragma once

#include "Windows.h"
class GameTimer
{
public:
	GameTimer(LARGE_INTEGER start,LARGE_INTEGER frequency);
	GameTimer(){};
	~GameTimer(void);

	
	void setLatestFrame(float t){latestFrame = t;}
	float getLatestFrame(){return latestFrame;}

	float getDeltaT();


	float GetTime(LARGE_INTEGER start,LARGE_INTEGER frequency)
	{
		LARGE_INTEGER t;
		QueryPerformanceCounter(&t);
		return (float)((t.QuadPart - start.QuadPart) * 1000.0f / frequency.QuadPart);
	}

protected:
	

	float startTime;
	float latestFrame;
	LARGE_INTEGER freq;
	LARGE_INTEGER start;


};

