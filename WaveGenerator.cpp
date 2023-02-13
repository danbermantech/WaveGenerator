// SineWaveGenerator.cpp : This file contains the 'main' function. Program execution begins and ends there.
//
#define _USE_MATH_DEFINES
#include <iostream>
#include <stdlib.h>
#include <cmath>
#include <math.h>
#include <fstream>
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
    Oscillator(double freq, double amp): frequency(freq), amplitude(amp) {
        angle = 0.0f;
        offset = 0.0;
    };
    virtual double process() { return 0; };
    virtual void setFrequency() {};
    virtual void setAmplitude() {};
    virtual double getFrequency() { return frequency; };
    virtual double getAmplitude() { return amplitude; };
};

class SineOscillator: public Oscillator{
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

    virtual void setFrequency(double freq) {
        frequency = freq;
    };

    virtual void setAmplitude(double amp) {
        amplitude = amp;
    };

    double getFrequency() {
        return frequency;
    };
    
    double getAmplitude() {
        return amplitude;
    }

};

 class OscillatorBank {
     public:
     vector<Oscillator *> oscillators;
     /*OscillatorBank() {
     };*/
     OscillatorBank(vector<float> freqs){
         float amp = 0.5;
         for (int i = 0; i < freqs.size(); i++){
             cout << freqs[i] << endl;
             Oscillator * osc = new SineOscillator(freqs[i], amp);
             amp *= 0.5;
             oscillators.push_back( osc);
         }
     }
     void addOscillator(float freq) {
         Oscillator * osc = new SineOscillator(freq, 0.1);
         oscillators.push_back(osc);
     }
 };

void writeToFile(ofstream& file, int value, int size) {
    file.write(reinterpret_cast<const char*> (&value), size);
};

int makeAWave(vector<float> freqs, std::string cwd) {
    vector<float> frequencyList = freqs;
    OscillatorBank * oscBank = new OscillatorBank({});
    if (frequencyList.size() < 1) {

    cout << "enter frequencies:" << endl;
    float input;
    do {
        cout << frequencyList.size()+1 << " : ";
        cin >> input;
        if (input > 0) {
            frequencyList.push_back(input);
        }
        else {
            cout << endl;
        }
    } while (input != 0);
    }
    for (int i = 0; i < frequencyList.size(); i++) {
        oscBank->addOscillator(frequencyList[i]);
    }

    ofstream audioFile;
    auto maxAmplitutde = pow(2, bitDepth - 1) - 1;
    int duration;
    string fileName;
    cout  << "Enter duration (in seconds): ";
    cin >> duration;
    cout << "Enter file name: ";
    cin >> fileName;
    audioFile.open(cwd + "/out/" + fileName + ".wav", ios::binary);

    //header chunk
    audioFile << "RIFF" << "----" << "WAVE";

    //format chunk
    audioFile << "fmt ";
    writeToFile(audioFile, 16, 4); //size
    writeToFile(audioFile, 1, 2); //compression code
    writeToFile(audioFile, 1, 2); //number of channels
    writeToFile(audioFile, sampleRate, 4); //sample rate
    writeToFile(audioFile, sampleRate * bitDepth / 8, 4); //byte rate ( sampleRate * bit depth * number of channels / 8
    writeToFile(audioFile, 2, 2); //block align
    writeToFile(audioFile, bitDepth, 2); // bit depth

    //Data chunk
    audioFile << "data" << "----";

    int preAudioPosition = audioFile.tellp();

    ofstream freqFile;
    freqFile.open(cwd + "/out/" + fileName + ".txt");
    for (int i = 0; i < sampleRate * duration; i++) {
         float sample = 0.0;
         for (int i = 0; i < oscBank->oscillators.size(); i++){
            Oscillator *osc = oscBank-> oscillators[i];
            sample = sample + osc->process();
         }
        int intSample = static_cast<int> (sample * maxAmplitutde);
        writeToFile(audioFile, intSample, 2);

    }
    
    for (int i = 0; i < oscBank->oscillators.size(); i++) {
        freqFile << oscBank->oscillators[i]->getFrequency() << "\n";
    }

    int postAudioPosition = audioFile.tellp();

    audioFile.seekp(preAudioPosition-4);
    writeToFile(audioFile, postAudioPosition - preAudioPosition, 4);

    audioFile.seekp(4, ios::beg);
    writeToFile(audioFile, postAudioPosition - 8, 4);
    audioFile.close();
    freqFile.close();


    cout << "Try another? [y/n]: ";
    char tryAgain = 'n';
    cin >> tryAgain;
    if (tryAgain == 'n' || tryAgain == 'N') {
        cout << "Goodbye!";
        return 0;
    }
    makeAWave({}, cwd);
    return 0;
}

int main(int argc, char* argv[])
{
    std::string filePath = argv[0];
    std::string cwd = filePath.substr(0, filePath.find_last_of("/\\"));
    cout << cwd << endl;
    vector<float> argValues;
    if (argc > 1) {

    for (int i = 1; i < argc; i++) {
        cout << argv[i] << endl;
        argValues.push_back(std::strtof(argv[i], NULL));
    }
    }
    return makeAWave(argValues, cwd);

}

// Run program: Ctrl + F5 or Debug > Start Without Debugging menu
// Debug program: F5 or Debug > Start Debugging menu

// Tips for Getting Started: 
//   1. Use the Solution Explorer window to add/manage files
//   2. Use the Team Explorer window to connect to source control
//   3. Use the Output window to see build output and other messages
//   4. Use the Error List window to view errors
//   5. Go to Project > Add New Item to create new code files, or Project > Add Existing Item to add existing code files to the project
//   6. In the future, to open this project again, go to File > Open > Project and select the .sln file
