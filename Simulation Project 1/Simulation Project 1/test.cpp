#pragma once
#include <iostream>
#include <string>
#include "GameTimer.h"
#include "SimulationWorld.h"
using namespace std;

LARGE_INTEGER start;
LARGE_INTEGER frequency;
int main()
	{
		int i;
		bool quit = false;
		SimulationWorld w = SimulationWorld();
		QueryPerformanceFrequency(&frequency);
		QueryPerformanceCounter(&start);

		w.Init();

		GameTimer timer(start,frequency);

		float t  = 0.0f;;
		float dt = 1/60.0f;

		float currentTime = timer.GetTime(start,frequency);

		while(!quit)
			{
				float newTime = timer.GetTime(start,frequency);	
				float frameTime = newTime - currentTime;
				currentTime = newTime;

				while(frameTime > 0.0f)
					{
						const float deltaTime = min(frameTime,dt);
						w.Update(deltaTime);
						frameTime -= deltaTime;
						t += deltaTime;
					}
			}
			
		cout << "\ntype something to exit: ";
		cin >> i;
		w.Destroy();
		return 0;
	}