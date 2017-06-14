/**
 * \file StereoDelayCtr.cpp
 *
 * \author Arnold N
 */


#include "StereoDelayCtrl.h"



CStereoDelayCtrl::CStereoDelayCtrl() : mQueSize(200000)
{
	mDelayTime = 0.1;		// Defualt starting delay of 0.1 seconds to avoid / 0
	mWriteLoc = 0;
	mReadLoc = 0;
	mSampleRate = 44100;	// Default sample rate (Hz)
}


CStereoDelayCtrl::~CStereoDelayCtrl()
{
}

void CStereoDelayCtrl::Process(float * leftSamples, float * rightSamples, int numSamples)
{
	// Calculate delay in samples
	int numDelaySamples = int((mDelayTime * mSampleRate + 0.5)) * 2;

	// Using time might be usefull if we want to add more functionality later
	double time = 0;
	for (int i = 0; i < numSamples; ++i, time += 1.0 / mSampleRate)
	{
		// Make sure the taps don't go out of bounds
		mWriteLoc = (mWriteLoc + 2) % mQueSize;
		mReadLoc = (mWriteLoc + mQueSize - numDelaySamples) % mQueSize;

		// Store this frame in our que
		mQue[mWriteLoc] = leftSamples[i];
		mQue[mWriteLoc + 1] = rightSamples[i];

		// Compute the new audio frame
		leftSamples[i] = (leftSamples[i] / 2.0f) + (mQue[mReadLoc++] / 2.0f);
		rightSamples[i] = (rightSamples[i] / 2.0f) + (mQue[mReadLoc] / 2.0f);
	}
}

void CStereoDelayCtrl::ClockProcess(float * leftSample, float * rightSample)
{
	// Calculate delay in samples
	int numDelaySamples = int((mDelayTime * mSampleRate + 0.5)) * 2;

	// Make sure audio taps don't go out of bounds
	mWriteLoc = (mWriteLoc + 2) % mQueSize;
	mReadLoc = (mWriteLoc + mQueSize - numDelaySamples) % mQueSize;

	// Store this frame in our que
	mQue[mWriteLoc] = *leftSample;
	mQue[mWriteLoc + 1] = *rightSample;

	// Compute the new audio samples - we divide by 2 to keep uniform gain
	*leftSample = (*leftSample / 2.0f) + (mQue[mReadLoc++] / 2.0f);
	*rightSample = (*rightSample / 2.0f) + (mQue[mReadLoc] / 2.0f);
}

void CStereoDelayCtrl::SetDelayTime(double time, const int sampleRate)
{
	mDelayTime = time;

	// Adjust other parameters
	mSampleRate = sampleRate;
	mQue.resize(mQueSize);	// Resize fill with zeros for us

	/** TODO: Reset read and write locations? */
	mReadLoc = 0;
	mWriteLoc = 0;
}