/**
 * \file StereoDelayCtr.cpp
 *
 * \author Arnold N
 */


#include "StereoDelayCtrl.h"



CStereoDelayCtrl::CStereoDelayCtrl()
{
	mQue = nullptr;
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
}
