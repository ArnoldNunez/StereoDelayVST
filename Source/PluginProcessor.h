/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#pragma once

#include "../JuceLibraryCode/JuceHeader.h"


//==============================================================================
/**
*/
class StereoDelayAudioProcessor  : public AudioProcessor,
	public AudioProcessorValueTreeState::Listener	// Class for monitoring param changes
{
public:
    //==============================================================================
    StereoDelayAudioProcessor();
    ~StereoDelayAudioProcessor();

    //==============================================================================
    void prepareToPlay (double sampleRate, int samplesPerBlock) override;
    void releaseResources() override;

   #ifndef JucePlugin_PreferredChannelConfigurations
    bool isBusesLayoutSupported (const BusesLayout& layouts) const override;
   #endif

    void processBlock (AudioSampleBuffer&, MidiBuffer&) override;

    //==============================================================================
    AudioProcessorEditor* createEditor() override;
    bool hasEditor() const override;

    //==============================================================================
    const String getName() const override;

    bool acceptsMidi() const override;
    bool producesMidi() const override;
    double getTailLengthSeconds() const override;

    //==============================================================================
    int getNumPrograms() override;
    int getCurrentProgram() override;
    void setCurrentProgram (int index) override;
    const String getProgramName (int index) override;
    void changeProgramName (int index, const String& newName) override;

    //==============================================================================
    void getStateInformation (MemoryBlock& destData) override;
    void setStateInformation (const void* data, int sizeInBytes) override;

private:
    //==============================================================================
    JUCE_DECLARE_NON_COPYABLE_WITH_LEAK_DETECTOR (StereoDelayAudioProcessor)

public:

	/** Callback method called when a parameter changes.
	 * This function is overriden from the ...ValueTreeState::Listener
	 * class.
	 * \param parameterID The ID given to the param that changed.
	 * \param newValue The new value of the param that changed.
	 */
	void parameterChanged(const String& parameterID, float newValue) override;


	/// Parameters for user parameter support
	#define PARAM_SETNAME "ParamSetName"
	#define PARAM_MASTERBYPASS "Bypass"
	#define PARAM_DELAY_TIME "DelayTime"

private:
	/// True if we have a major change in our parameters
	bool mMajorParamChange;

	/// Tree used to manage AudioProcessor's entire state
	ScopedPointer<AudioProcessorValueTreeState> mState;

	/// Used to tell listeners when actions are performed or undone.
	ScopedPointer<UndoManager> mUndoManager;

};
