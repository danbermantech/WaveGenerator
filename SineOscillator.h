#pragma once
#define _USE_MATH_DEFINES
#include "Oscillator.h"
#include "definitions.h"
using namespace std;

class SineOscillator : public Oscillator {
    double frequency, amplitude, angle = 0.0f, offset = 0.0;
public:
    SineOscillator(double freq, double amp) : frequency(freq), amplitude(amp) {
        Oscillator();
        offset = 2 * M_PI * frequency / sampleRate;
        cout << "created oscillator at " << frequency << "hz" << endl;
    }
    virtual void setFrequency(double freq) {
        cout << "frequency set to " << freq << endl;
        frequency = freq;
    };
    virtual double process() {
        auto sample = amplitude * (sin(angle));
        angle += offset;
        return sample;
    };
};