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
#include "oscillators.h"
#include "AudioFile.h"
using namespace std;

//const int sampleRate = 44100;
//const int bitDepth = 16;
//const int number_of_frequencies = 64;



//void writeToFile(ofstream& file, int value, int size) {
//    file.write(reinterpret_cast<const char*> (&value), size);
//};

//float filter(float sample) {
//    return sample * sin(sample);
//}

int makeAWave(vector<float> freqs, std::string cwd) {
    vector<float> frequencyList = freqs;
    OscillatorBank * oscBank = new AdditiveBank({});
    if (frequencyList.size() < 1) {

    char addAnother;
    float input;
    do {
        cout << frequencyList.size()+1 << " : " << endl;

        std::string type;
        cout << "Enter oscillator type ([tan],[sin],[saw]) : ";
        cin >> type;

        double freq;
        cout << "Enter frequency : ";
        cin >> freq;

        double amp;
        cout << "Enter amplitude : ";
        cin >> amp;

        cout << endl;
        oscBank->addOscillator(freq, amp, type);
        cout << "Add another ? [Y/n]";
        cin >> addAnother;
        cout << endl;
        if(addAnother != 'n'){}
    } while (addAnother != 'n');
    }
    else {
        for (int i = 0; i < frequencyList.size(); i++) {
            oscBank->addOscillator(frequencyList[i]);
        }
    }

    auto maxAmplitutde = pow(2, bitDepth - 1) - 1;
    int duration;
    string fileName;
    cout  << "Enter duration (in seconds): ";
    cin >> duration;
    cout << "Enter file name: ";
    cin >> fileName;
    Audiofile audiofile(fileName, cwd);

    ofstream freqFile;
    freqFile.open(cwd + "/out/" + fileName + ".txt");
    for (int i = 0; i < sampleRate * duration; i++) {
        float sample = oscBank->process();
        int intSample = static_cast<int> (sample * maxAmplitutde);
        audiofile.writeSample(intSample);
    }
    
    for (int i = 0; i < oscBank->oscillators.size(); i++) {
        freqFile << oscBank->oscillators[i]->getFrequency() << "\n";
    }

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
