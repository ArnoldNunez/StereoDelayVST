/**
 * \file StereoDelayCtr.cpp
 *
 * \author Arnold N
 */


#include "StereoDelayCtrl.h"



CStereoDelayCtrl::CStereoDelayCtrl()
{
	mQueSize = 0;
	mDelayTime = 0;
	mWriteLoc = 0;
	mReadLoc = 0;
}


CStereoDelayCtrl::~CStereoDelayCtrl()
{
}

void CStereoDelayCtrl::Process(float * leftSamples, float * rightSamples, int numSamples)
{
}

void CStereoDelayCtrl::ClockProcess(float * leftSample, float * rightSample)
{
	// Calculate delay in samples
	int numDelaySamples = int((mDelayTime * mSampleRate + 0.5)) * 2;

	// Make sure audio taps don't go out of bounds
	mWriteLoc = (mWriteLoc + 2) % mQueSize;
	mReadLoc = (mWriteLoc + mQueSize - numDelaySamples) % mQueSize;

	// Store this sample in our que
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
	mQueSize = time * sampleRate;
	mQue.resize(mQueSize);
}