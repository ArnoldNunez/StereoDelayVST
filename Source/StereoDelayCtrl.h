/**
 * \file StereoDelayCtrl.h
 *
 * \author Arnold N
 *
 * \brief Class for implementing stereo delay audio processing
 */

#pragma once

#include <vector>

class CStereoDelayCtrl
{
public:
	/** Default constructor */
	CStereoDelayCtrl();
	/** Default destructor */
	~CStereoDelayCtrl();
	/** Default copy constructor (disabled) */
	CStereoDelayCtrl(const CStereoDelayCtrl&) = delete;

	/** Setter for the length of the delay
	 * \param time The length of the delay (ms)
	 * \param sampleRate The sampele rate of the audio */
	void SetDelayTime(double time, const int sampleReate);

	/** Stere Delay control.
	 * The audio delay is created using a que with read and write
	 * locations to keep track of the current sample we are on and
	 * the delayed sample. This processes multiple frames.
	 *
	 * \param leftSamples Ptr to left channel audio buffer
	 * \param rightSamples Ptr to right channel audio buffer
	 * \param numSamples the number of samples in the buffer
	 */
	void Process(float* leftSamples, float* rightSamples, int numSamples);

	/** Stere Delay control for one sample
	 * The audio delay is created using a que with read and write
	 * locations to keep track of the current sample we are on and the
	 * delayed sample. This processes only 1 frame.
	 *
	 * \param leftSamples Ptr to left channel audio buffer
	 * \param rightSamples Ptr to right channel audio buffer
	 */
	void ClockProcess(float* leftSample, float* rightSample);

private:

	double mDelayTime;		///< The length of the delay (sec)
	const int mQueSize;		///< Max possible delay * 2 (Samples)
	int mWriteLoc;			///< Buffer write location
	int mReadLoc;			///< Buffer read location
	std::vector<float> mQue;///< The buffer of audio samples
	int mSampleRate;		///< The sampling rate of the audio input (Hz)
};

