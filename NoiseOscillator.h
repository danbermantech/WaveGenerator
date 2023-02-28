#pragma once
#include <random>
#include "Oscillator.h"
using namespace std;

double randomValue(double min, double max) {
    //cout << RAND_MAX < endl;
    return ((rand() / RAND_MAX) * (max - min) + min);

}

//(X - A) / (B - A) * (D - C) + C

class NoiseOscillator :
    public Oscillator
{
    double amplitude;
public:
    NoiseOscillator(double freq, double amp): amplitude(amp) {
    }
    virtual double process() {
        return randomValue(-1, 1);
    }
};

