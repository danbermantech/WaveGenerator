#pragma once
#define _USE_MATH_DEFINES
#include "Oscillator.h"
#include <iostream>
#include "definitions.h"
using namespace std;

class HarmonicOscillator : public Oscillator {
    double frequency = 0, amplitude, angle = 0.0f, offset = 0.0, harmonic = 1, modifier = 0;
public:
    HarmonicOscillator(double freq, double amp) : harmonic(freq), amplitude(amp) {
        Oscillator();
        offset = 2 * M_PI * (frequency * harmonic) / sampleRate;
        cout << "created oscillator at " << frequency << "hz" << endl;
    }

    HarmonicOscillator(double freq, double amp, double mod) : harmonic(freq), amplitude(amp), modifier(mod) {
        Oscillator();
        offset = 2 * M_PI * ((frequency * harmonic)+modifier) / sampleRate;
        cout << "created oscillator at " << frequency << "hz" << endl;
    }



    virtual void setFrequency(double freq) {
        frequency = freq;
    }

    virtual double process() {
        double sample = amplitude * (sin(angle));
        angle += 2 * M_PI * ((frequency * harmonic)+modifier) / sampleRate;
        return sample;
    };

    virtual double getFrequency() { return frequency; };
    virtual double getAmplitude() { return amplitude; };
    virtual double getHarmonic() { return harmonic; };
};