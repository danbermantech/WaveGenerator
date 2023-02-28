#pragma once

class FMBank : public OscillatorBank {
public:
    FMBank() {};
    virtual double process() {
        double sample = 1.0;
        for (unsigned int i = 0; i < oscillators.size(); i++) {
            sample = sample * (oscillators[i]->process());
        }
        return sample * (double)oscillators.size();
    }
};