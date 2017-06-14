/*
  ==============================================================================

    This file was auto-generated!

    It contains the basic framework code for a JUCE plugin processor.

  ==============================================================================
*/

#include "PluginProcessor.h"
#include "PluginEditor.h"

static String GetStrValue(float v) { return String(v); }
static String GetBypassStr(float v) { return (v != 0.0f) ? "Bypassed" : "Enabled"; }


//==============================================================================
StereoDelayAudioProcessor::StereoDelayAudioProcessor()
#ifndef JucePlugin_PreferredChannelConfigurations
     : AudioProcessor (BusesProperties()
                     #if ! JucePlugin_IsMidiEffect
                      #if ! JucePlugin_IsSynth
                       .withInput  ("Input",  AudioChannelSet::stereo(), true)
                      #endif
                       .withOutput ("Output", AudioChannelSet::stereo(), true)
                     #endif
                       )
#endif
{
	mUndoManager = new UndoManager();
	mState = new AudioProcessorValueTreeState(*this, mUndoManager);

	// Add each of our parameters
	mState->createAndAddParameter(PARAM_MASTERBYPASS, "Bypass", "", NormalisableRange<float>(0, 1, 1), 0,
		GetBypassStr, nullptr);

	mState->createAndAddParameter(PARAM_DELAY_TIME, "DelayTime", "", NormalisableRange<float>(0.01f, 1, 0.01f),
		0, nullptr, nullptr);

	// Now create the actual ValueTree
	mState->state = ValueTree(PARAM_SETNAME);

	// Add any controls you want to trigger a deeper update
	// timed with the call to process
	mState->addParameterListener(PARAM_DELAY_TIME, this);

	// Start with a deeper update
	mMajorParamChange = true;	
}

StereoDelayAudioProcessor::~StereoDelayAudioProcessor()
{
	// Clean up our ValueTreeState and undo manager
	mState = nullptr;
	mUndoManager = nullptr;
}

//==============================================================================
const String StereoDelayAudioProcessor::getName() const
{
    return JucePlugin_Name;
}

bool StereoDelayAudioProcessor::acceptsMidi() const
{
   #if JucePlugin_WantsMidiInput
    return true;
   #else
    return false;
   #endif
}

bool StereoDelayAudioProcessor::producesMidi() const
{
   #if JucePlugin_ProducesMidiOutput
    return true;
   #else
    return false;
   #endif
}

double StereoDelayAudioProcessor::getTailLengthSeconds() const
{
    return 0.0;
}

int StereoDelayAudioProcessor::getNumPrograms()
{
    return 1;   // NB: some hosts don't cope very well if you tell them there are 0 programs,
                // so this should be at least 1, even if you're not really implementing programs.
}

int StereoDelayAudioProcessor::getCurrentProgram()
{
    return 0;
}

void StereoDelayAudioProcessor::setCurrentProgram (int index)
{
}

const String StereoDelayAudioProcessor::getProgramName (int index)
{
    return {};
}

void StereoDelayAudioProcessor::changeProgramName (int index, const String& newName)
{
}

//==============================================================================
void StereoDelayAudioProcessor::prepareToPlay (double sampleRate, int samplesPerBlock)
{
    // Use this method as the place to do any pre-playback
    // initialisation that you need..
}

void StereoDelayAudioProcessor::releaseResources()
{
    // When playback stops, you can use this as an opportunity to free up any
    // spare memory, etc.
}

#ifndef JucePlugin_PreferredChannelConfigurations
bool StereoDelayAudioProcessor::isBusesLayoutSupported (const BusesLayout& layouts) const
{
  #if JucePlugin_IsMidiEffect
    ignoreUnused (layouts);
    return true;
  #else
    // This is the place where you check if the layout is supported.
    // In this template code we only support mono or stereo.
    if (layouts.getMainOutputChannelSet() != AudioChannelSet::mono()
     && layouts.getMainOutputChannelSet() != AudioChannelSet::stereo())
        return false;

    // This checks if the input layout matches the output layout
   #if ! JucePlugin_IsSynth
    if (layouts.getMainOutputChannelSet() != layouts.getMainInputChannelSet())
        return false;
   #endif

    return true;
  #endif
}
#endif

void StereoDelayAudioProcessor::processBlock (AudioSampleBuffer& buffer, MidiBuffer& midiMessages)
{
	if (mMajorParamChange)
	{
		/** 
		 * This is where you would put code to reconfigure buffers
		 * or other major changes 
		 */
		mStereoDelayCtrl.SetDelayTime( (*mState->getRawParameterValue(PARAM_DELAY_TIME)), getSampleRate() );
		mMajorParamChange = false;
	}

    const int totalNumInputChannels  = getTotalNumInputChannels();
    const int totalNumOutputChannels = getTotalNumOutputChannels();

	if (totalNumInputChannels != 2 || totalNumOutputChannels != 2
		|| (*mState->getRawParameterValue(PARAM_MASTERBYPASS)) != 0.0f)
	{
		/** Do Nothing - Since pass through is on we do nothing to the signal */
	}
	else
	{
		// Not bypassed - do processing!
		float** pChannelData = buffer.getArrayOfWritePointers();
		mStereoDelayCtrl.Process(pChannelData[0], pChannelData[1], buffer.getNumSamples());
	}
}

//==============================================================================
bool StereoDelayAudioProcessor::hasEditor() const
{
    return true; // (change this to false if you choose to not supply an editor)
}
  
AudioProcessorEditor* StereoDelayAudioProcessor::createEditor()
{
    return new StereoDelayAudioProcessorEditor (*this);
}

//==============================================================================
void StereoDelayAudioProcessor::getStateInformation (MemoryBlock& destData)
{
    // You should use this method to store your parameters in the memory block.
    // You could do that either as raw data, or use the XML or ValueTree classes
    // as intermediaries to make it easy to save and load complex data.

	// Save UserParams/Data to memory
	MemoryOutputStream stream(destData, false);
	mState->state.writeToStream(stream);
}

void StereoDelayAudioProcessor::setStateInformation (const void* data, int sizeInBytes)
{
    // You should use this method to restore your parameters from this memory block,
    // whose contents will have been created by the getStateInformation() call.

	// Load UserParams/Data from memory
	ValueTree tree = ValueTree::readFromData(data, sizeInBytes);

	if (tree.isValid())
	{
		if (tree.hasType(PARAM_SETNAME))
		{
			mState->state = tree;
		}
	}
}

//==============================================================================
// This creates new instances of the plugin..
AudioProcessor* JUCE_CALLTYPE createPluginFilter()
{
    return new StereoDelayAudioProcessor();
}


void StereoDelayAudioProcessor::parameterChanged(const String& parameterID, float newValue)
{
	mMajorParamChange = true;
}