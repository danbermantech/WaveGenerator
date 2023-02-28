#pragma once
#define _USE_MATH_DEFINES
#include "Oscillator.h"
#include "definitions.h"
using namespace std;

class CotanOscillator : public Oscillator {
    double frequency, amplitude, angle = 0.0f, offset = 0.0;
public:
    CotanOscillator(double freq, double amp) : frequency(freq), amplitude(amp) {
        Oscillator();
        offset = 2 * M_PI * frequency / sampleRate;
        cout << "created tan oscillator at " << frequency << "hz" << endl;
    }
    virtual double process() {
        angle += offset;
        auto sample = amplitude * (tan(angle));
        return sample;
    }
};