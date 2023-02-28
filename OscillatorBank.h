#pragma once
#include "TanOscillator.h"
#include "CotanOscillator.h"
#include "SawOscillator.h"
#include "SineOscillator.h"
#include "HarmonicOscillator.h"
#include "definitions.h"
#include "requestUserInput.h"
#include <vector>
using namespace std;
class OscillatorBank {
    Oscillator* createOscillator(double freq) {
        Oscillator* osc = new SineOscillator(freq, 0.1);
        oscillators.push_back(osc);
        return osc;
    }
    Oscillator* createOscillator(double freq, double amp, double modifier) {
        Oscillator* osc = new HarmonicOscillator(freq, amp, modifier);
        oscillators.push_back(osc);
        return osc;
    }
    Oscillator* createOscillator(double freq, double amp, char type) {
        Oscillator* osc;
        switch (type) {
        case('s'):
            osc = new SineOscillator(freq, amp);
            break;
        case('t'):
            osc = new TanOscillator(freq, amp);
            break;
        case('c'):
            osc = new CotanOscillator(freq, amp);
            break;
        case('w'):
            osc = new SawOscillator(freq, amp);
            break;
        case('h'):
        default:
            osc = new HarmonicOscillator(freq, amp);
        }
        oscillators.push_back(osc);
        return osc;
    }
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

    OscillatorBank* addOscillator(double freq) {
        createOscillator(freq);
        return this;
    }

    OscillatorBank* addOscillator(double freq, double amp, char type) {
        createOscillator(freq, amp, type);
        return this;
    }

    //alternate form to set harmonic with modifier
    OscillatorBank* addOscillator(double freq, double amp, double modifier) {
        createOscillator(freq, amp, modifier);
        return this;
    }

    OscillatorBank* addOscillatorInteractive() {
        char type = requestUserInput<char>("Enter oscillator type ([t]an, [c]otan, [s]in, sa[w], [h]armonic) [default 'harmonic']", 'h');
        double freq = requestUserInput<double>(type == 'h' ? "Enter harmonic" : "Enter frequency", (double)1);
        double amp = requestUserInput<double>("Enter amplitude", (double)0.5);
        createOscillator(freq, amp, type);

        cout << endl;

        char addAnother = requestUserInput<char>("Add another ? [Y / n]", 'y');

        if (addAnother == 'y' || addAnother == 'Y') {
            addOscillatorInteractive();
        };
        return this;
    }

    OscillatorBank* update_frequencies(double frequency) {
        for (unsigned int i = 0; i < oscillators.size(); i++) {
            oscillators[i]->setFrequency(frequency);
        }
        return this;
    }

    string get_details() {
        string data = "Frequency, Harmonic, Amplitude\n";
        for (unsigned int i = 0; i < oscillators.size(); i++) {
            data +=  to_string(oscillators[i]->getFrequency()) + ", ";
            data += to_string(oscillators[i]->getHarmonic()) + ", ";
            data += to_string(oscillators[i]->getAmplitude()) + "\n";
        }
        return data;
    }

    virtual double process() {

        double sample = 0.0;
        for (unsigned int i = 0; i < oscillators.size(); i++) {
            sample = sample + (oscillators[i]->process() / oscillators.size());
        }
        return sample;
    }
};