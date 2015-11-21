#ifndef POLYBLEPSTK_H_INCLUDED
#define POLYBLEPSTK_H_INCLUDED


// Derived class to use the PolyBLEP Oscillator as an stk::Generator.

#include "../JuceLibraryCode/JuceHeader.h"
#include "PolyBLEP.h"

class PolyBLEPStk : public stk::Generator, public PolyBLEP {
public:
    PolyBLEPStk(double sampleRate, Waveform waveform = SINE, double initialFrequency = 440.0)
            : PolyBLEP(sampleRate, waveform, initialFrequency) {
        const int numFrames = 1;
        const int numChannels = 1;
        lastFrame_.resize(numFrames, numChannels, 0.0);
    }


    virtual ~PolyBLEPStk() {
    }

    virtual stk::StkFrames &tick(stk::StkFrames &frames, unsigned int channel = 0) override {
        for (size_t frame = 0; frame < frames.size(); ++frame) {
            frames(frame, channel) = getAndInc();
        }
        return frames;
    }

    virtual void sampleRateChanged(stk::StkFloat newRate, stk::StkFloat oldRate) override {
        PolyBLEP::setSampleRate(newRate);
    }

private:
};


#endif
