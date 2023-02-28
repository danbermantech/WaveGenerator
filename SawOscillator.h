#pragma once
#define _USE_MATH_DEFINES
#include "definitions.h"
#include "Oscillator.h"
using namespace std;

class SawOscillator : public Oscillator {
    double frequency, amplitude, angle = 0.0f, offset = 0.0;
public:
    SawOscillator(double freq, double amp) : frequency(freq), amplitude(amp) {
        Oscillator();
        offset = 2 * M_PI * frequency / sampleRate;
        cout << "created saw oscillator at " << frequency << "hz" << endl;
    }
    virtual double process() {
        angle += offset;
        auto sample = amplitude * (angle);
        return sample;
    }
};