#include "uTimer.h"

uTimer::uTimer()
: dbl_SecondsPerCount(0.0), dbl_DeltaTime(-1.0), ll_Base(0), 
  ll_Paused(0), ll_Prev(0), ll_Current(0), b_Stopped(false)
{
	__int64 countsPerSec;
	QueryPerformanceFrequency((LARGE_INTEGER*)&countsPerSec);
	dbl_SecondsPerCount = 1.0 / (double)countsPerSec;
}

float uTimer::TotalTime()const {
	if( b_Stopped ) { return (float)(((ll_Stop - ll_Paused)-ll_Base)*dbl_SecondsPerCount); }
	else {	return (float)(((ll_Current-ll_Paused)-ll_Base)*dlb_SecondsPerCount); }
}

float uTimer::DeltaTime()const {
	return (float)dbl_DeltaTime;
}

void uTimer::Reset() {
	__int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

	ll_Prev = ll_Base = currTime;
	ll_Stop = 0;
	b_Stopped  = false;
}

void uTimer::Start() {
	__int64 startTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&startTime); 

	if( b_Stopped ) {
		ll_Paused += (startTime - ll_Stop);	

		ll_Prev = startTime;
		ll_Stop = 0;
		b_Stopped  = false;
	}
}

void uTimer::Stop() {
	if( !b_Stopped ) {
		__int64 currTime;
		QueryPerformanceCounter((LARGE_INTEGER*)&currTime);

		ll_Stop = currTime;
		b_Stopped  = true;
	}
}

void uTimer::Tick() {
	if( b_Stopped ) {
		mDeltaTime = 0.0;
		return;
	}

	__int64 currTime;
	QueryPerformanceCounter((LARGE_INTEGER*)&currTime);
	ll_Current = currTime;

	ll_Delta = (ll_Current - ll_Prev)*dbl_SecondsPerCount;

	ll_Prev = ll_Current;

	if(ll_Delta < 0.0) {
		ll_Delta = 0.0;
	}
}
