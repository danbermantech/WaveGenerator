#pragma once
#include <iostream>
using namespace std;

class Oscillator {
    double frequency = 0, amplitude = 0, angle = 0.0f, offset = 0.0, harmonic = 1;
public:
    Oscillator() {};
    Oscillator(double freq, double amp) : frequency(freq), amplitude(amp) {
        angle = 0.0f;
        offset = 0.0;
    };
    virtual double process() { return 0; };
    void setHarmonic(double harm) {
        harmonic = harm;
    }
    virtual void setFrequency(double freq) {
        cout << "frequency set to " << freq << endl;
        frequency = freq;
    };
    void setAmplitude(double amp) {
        amplitude = amp;
    };
    virtual double getFrequency() { return frequency; };
    virtual double getAmplitude() { return amplitude; };
    virtual double getHarmonic() { return harmonic; };
};