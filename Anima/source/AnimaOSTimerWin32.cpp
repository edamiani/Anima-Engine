#include "../../include/Timer.h"

namespace TR
{
	//-------------------------------------------------------------------------
	Timer::Timer()
	{
		reset();
	}

	//-------------------------------------------------------------------------
	Timer::~Timer()
	{
	}

	//-------------------------------------------------------------------------
	void Timer::reset()
	{
		zeroClock = clock();

		mCurrentMark = 0;
		mLastMark = 0;

		QueryPerformanceFrequency(&mFrequency);
		QueryPerformanceCounter(&mStartTime);
		mStartTick = GetTickCount();
		mLastTime = 0;
		mQueryCount = 0;

		// Save the current process
		HANDLE mProc = GetCurrentProcess();

		// Get the current Affinity
	#if _MSC_VER >= 1400 && defined (_M_X64)
		GetProcessAffinityMask(mProc, (PDWORD_PTR)&mProcMask, (PDWORD_PTR)&mSysMask);
	#else
		GetProcessAffinityMask(mProc, &mProcMask, &mSysMask);
	#endif

		mThread = GetCurrentThread();
	}

	//-------------------------------------------------------------------------
	unsigned long Timer::getMilliseconds()
	{
		 LARGE_INTEGER curTime;

		 // Set affinity to the first core
		 SetThreadAffinityMask(mThread, 1);

		 // Query the timer
		 QueryPerformanceCounter(&curTime);

		 // Reset affinity
		 SetThreadAffinityMask(mThread, mProcMask);

		// Resample the frequency
		 mQueryCount++;
		 if(mQueryCount == FREQUENCY_RESAMPLE_RATE)
		 {
			  mQueryCount = 0;
			  QueryPerformanceFrequency(&mFrequency);
		 }

		 LONGLONG newTime = curTime.QuadPart - mStartTime.QuadPart;
	    
		 // scale by 1000 for milliseconds
		 unsigned long newTicks = (unsigned long) (1000 * newTime / mFrequency.QuadPart);

		 // detect and compensate for performance counter leaps
		 // (surprisingly common, see Microsoft KB: Q274323)
		 unsigned long check = GetTickCount() - mStartTick;
		 signed long msecOff = (signed long)(newTicks - check);
		 if (msecOff < -100 || msecOff > 100)
		 {
			  // We must keep the timer running forward :)
			  LONGLONG adjust = (std::min)(msecOff * mFrequency.QuadPart / 1000, newTime - mLastTime);
			  mStartTime.QuadPart += adjust;
			  newTime -= adjust;

			  // Re-calculate milliseconds
			  newTicks = (unsigned long) (1000 * newTime / mFrequency.QuadPart);
		 }

		 // Record last time for adjust
		 mLastTime = newTime;

		 return newTicks;
	}

	//-------------------------------------------------------------------------
	unsigned long Timer::getMicroseconds()
	{
		 LARGE_INTEGER curTime;
		 QueryPerformanceCounter(&curTime);
		 LONGLONG newTime = curTime.QuadPart - mStartTime.QuadPart;
	    
		 // get milliseconds to check against GetTickCount
		 unsigned long newTicks = (unsigned long) (1000 * newTime / mFrequency.QuadPart);
	    
		 // detect and compensate for performance counter leaps
		 // (surprisingly common, see Microsoft KB: Q274323)
		 unsigned long check = GetTickCount() - mStartTick;
		 signed long msecOff = (signed long)(newTicks - check);
		 if (msecOff < -100 || msecOff > 100)
		 {
			  // We must keep the timer running forward :)
			  LONGLONG adjust = (std::min)(msecOff * mFrequency.QuadPart / 1000, newTime - mLastTime);
			  mStartTime.QuadPart += adjust;
			  newTime -= adjust;
		 }

		 // Record last time for adjust
		 mLastTime = newTime;

		 // scale by 1000000 for microseconds
		 unsigned long newMicro = (unsigned long) (1000000 * newTime / mFrequency.QuadPart);

		 return newMicro;
	}

	//-------------------------------------------------------------------------
	unsigned long Timer::getMillisecondsCPU()
	{
		clock_t newClock = clock();
		return (unsigned long)((float)(newClock-zeroClock) / ((float)CLOCKS_PER_SEC/1000.0)) ;
	}

	//-------------------------------------------------------------------------
	unsigned long Timer::getMicrosecondsCPU()
	{
		clock_t newClock = clock();
		return (unsigned long)((float)(newClock-zeroClock) / ((float)CLOCKS_PER_SEC/1000000.0)) ;
	}
}
