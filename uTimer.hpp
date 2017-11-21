#pragma once
#include <windows.h>

class uTimer {
public:
        uTimer();
  
	void Reset(); // Reset Timer
	void Start(); // Start Timer
	void Stop();  // Stop Timer
	void Tick();  // Call every frame
  
        float TotalTime()const; // in sec
	float DeltaTime()const; // in sec
  
private:
        double dbl_SecondsPerCount;
	double dbl_DeltaTime;

	__int64 ll_Base;    // Base Time
	__int64 ll_Paused;  // Paused Time
	__int64 ll_Stop;    // Stop Time
	__int64 ll_Prev;    // Previous Time
	__int64 ll_Current; // Current Time

	bool b_Stopped;
};
