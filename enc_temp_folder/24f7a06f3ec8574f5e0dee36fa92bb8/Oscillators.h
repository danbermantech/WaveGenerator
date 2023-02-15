#pragma once
#define _USE_MATH_DEFINES
#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <math.h>
#include <vector>
#include <string>
using namespace std;

const int sampleRate = 44100;
const int bitDepth = 16;
const int number_of_frequencies = 64;

class Oscillator {
    double frequency = 0, amplitude = 0, angle = 0.0f, offset = 0.0;
public:
    Oscillator() {};
    Oscillator(double freq, double amp) : frequency(freq), amplitude(amp) {
        angle = 0.0f;
        offset = 0.0;
    };
    virtual double process() { return 0; };
    void setFrequency(double freq) {
        frequency = freq;
    };
    void setAmplitude(double amp) {
        amplitude = amp;
    };
    double getFrequency() { return frequency; };
    double getAmplitude() { return amplitude; };
};

class TanOscillator : public Oscillator {
    double frequency, amplitude, angle = 0.0f, offset = 0.0;
public:
    TanOscillator(double freq, double amp) : frequency(freq), amplitude(amp) {
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

        //offset += frequency / amplitude;
        //if (offset >= 1) {
        //    offset -= 2;
        //}
        //return (offset * amplitude) - 1;
    }
};

class SineOscillator : public Oscillator {
    double frequency, amplitude, angle = 0.0f, offset = 0.0;
public:
    SineOscillator(double freq, double amp) : frequency(freq), amplitude(amp) {
        Oscillator();
        offset = 2 * M_PI * frequency / sampleRate;
        cout << "created oscillator at " << frequency << "hz" << endl;
    }
    virtual double process() {
        auto sample = amplitude * (sin(angle));
        angle += offset;
        return sample;
    };
};

class OscillatorBank {
public:
    vector<Oscillator*> oscillators;
    OscillatorBank() {};
    OscillatorBank(vector<float> freqs) {
        float amp = 0.5;
        for (unsigned int i = 0; i < freqs.size(); i++) {
            cout << freqs[i] << endl;
            Oscillator* osc = new SineOscillator(freqs[i], amp);
            amp *= 0.5;
            oscillators.push_back(osc);
        }
    }
    void addOscillator(double freq) {
        Oscillator* osc = new SineOscillator(freq, 0.1);
        oscillators.push_back(osc);
    }
    void addOscillator(double freq, double amp, std::string type) {
        if (type == "sin") {
            Oscillator* osc = new SineOscillator(freq, amp);
            oscillators.push_back(osc);
            return;
        }
        if (type == "tan") {
            Oscillator* osc = new TanOscillator(freq, amp);
            oscillators.push_back(osc);
            return;
        }
        if (type == "saw") {
            Oscillator* osc = new SawOscillator(freq, amp);
            oscillators.push_back(osc);
            return;
        }
        cout << "uhhh something went wrong" << endl;
        return;
    }

    virtual double process() {

        double sample = 0.0;
        for (unsigned int i = 0; i < oscillators.size(); i++) {
            sample = sample + (oscillators[i]->process() / oscillators.size());
        }
        return sample;
    }
};

class FMBank : public OscillatorBank {
public:
    FMBank() {};
    virtual double process() {
        double sample = 1.0;
        for (unsigned int i = 0; i < oscillators.size(); i++) {
            sample = sample * (oscillators[i]->process());
        }
        //cout << oscillators.size() << " " << sample << endl;
        return sample * (double)oscillators.size();
    }
};

class AdditiveBank : public OscillatorBank {
public:
    AdditiveBank() {};

    virtual double process() {

        double sample = 0.0;
        for (unsigned int i = 0; i < oscillators.size(); i++) {
            sample = sample + (oscillators[i]->process() / oscillators.size());
        }
        return sample;
    }
};