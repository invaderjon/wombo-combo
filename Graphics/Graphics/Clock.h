#pragma once

#include "Primitives.h"

namespace graphics
{
	class Clock
	{
		GEuint mTimeCycles;
		GEfloat mTimeScale;
		GEboolean mIsPaused;

		static GEfloat sCyclesPerSecond;

		static inline GEulong secondsToCycles(GEfloat seconds)
		{
			return (GEuint)(seconds * sCyclesPerSecond);
		}

		// WARNING: Dangerous -- only use to convert small
		// durations into seconds
		static inline GEfloat cyclesToSeconds(GEulong cycles)
		{
			return (GEfloat)cycles / sCyclesPerSecond;
		}

	public:
		// call this when engine first starts up
		static void init()
		{
			//sCyclesPerSecond = (GEfloat)readHiResTimerFrequency();
		}
		
		explicit Clock(GEfloat startTimeSeconds = 0.0f) :
			mTimeCycles(secondsToCycles(startTimeSeconds)),
			mTimeScale(1.0f),
			mIsPaused(false) 
		{
		}

		// Return the current time in cycles. NOTE that we do 
		// not return absolute time measurements in floating 
		// point seconds, because a 32-bit float doesnÅft have 
		// enough precision. See calcDeltaSeconds().
		GEulong getTimeCycles() const
		{
			return mTimeCycles;
		}

		// Determine the difference between this clockÅfs
		// absolute time and that of another clock, in 
		// seconds. We only return time deltasas floating  
		// point seconds, due to the precision limitations of 
		// a 32-bit float.
		GEfloat calcDeltaSeconds(const Clock& other)
		{
			GEulong dt = mTimeCycles - other.mTimeCycles;
			return cyclesToSeconds(dt);
		}

		// This function should be called once per frame,  
		// with the real measured frame time delta in seconds.
		void update(GEfloat dtRealSeconds)
		{
			if (!mIsPaused)
			{
				GEulong dtScaledCycles = secondsToCycles(dtRealSeconds * mTimeScale);
				mTimeCycles += dtScaledCycles;
			}
		}

		void setPaused(GEboolean isPaused)
		{
			mIsPaused = isPaused;
		}

		GEboolean isPaused() const
		{
			return mIsPaused;
		}

		void setTimeScale(GEfloat scale)
		{
			mTimeScale = scale;
		}

		GEfloat getTimeScale() const
		{
			return mTimeScale;
		}

		void singleStep()
		{
			if (mIsPaused)
			{
				// Add one ideal frame interval; donÅft forget 
				// to scale it by our current time scale!
				GEulong  dtScaledCycles = secondsToCycles(
					(1.0f / 30.0f) * mTimeScale);

				mTimeScale += dtScaledCycles;
			}
		}
	};
}

