#pragma once
#define _USE_MATH_DEFINES
#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <math.h>
#include <vector>
#include <string>
#include "OscillatorBank.h"
#include "definitions.h"
using namespace std;

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