#pragma once
#include <string_view>
#include "OscillatorBank.h"
#include "Audiofile.h"
#include "standard_tuning_frequencies.h"
using namespace std;

void generateFiles(OscillatorBank* oscBank, string cwd, string fileName, float duration, char scale, char mode) {
    auto maxAmplitude = pow(2, bitDepth - 1) - 1;

    if (mode == 'u') {
        Audiofile audiofile(fileName, cwd);

        ofstream freqFile;
        freqFile.open(cwd + "/out/" + fileName + ".txt");
        for (int i = 0; i < sampleRate * duration; i++) {
            double sample = oscBank->process();
            int intSample = static_cast<int> (sample * maxAmplitude);
            audiofile.writeSample(intSample);
        }

        for (int i = 0; i < oscBank->oscillators.size(); i++) {
            freqFile << oscBank->oscillators[i]->getFrequency() << "\n";
        }
        return;
    }

    int midiNumber = 0;
    for (double freq : Tunings::A440) {
        Audiofile audiofile(fileName + " " + to_string(midiNumber), cwd);
        ofstream freqFile;
        freqFile.open(cwd + "/out/" + fileName + to_string(midiNumber) + ".txt");
        cout << "setting frequencies to " << freq << endl;
        oscBank->update_frequencies(freq);
        freqFile << oscBank->get_details();
        for (int i = 0; i < sampleRate * duration; i++) {
            double sample = oscBank->process();
            int intSample = static_cast<int> (sample * maxAmplitude);
            audiofile.writeSample(intSample);
        }
        midiNumber++;
    }
}

void generateFiles(OscillatorBank* oscBank, string cwd, string fileName, char scale) {
    auto maxAmplitude = pow(2, bitDepth - 1) - 1;

    int midiNumber = 0;
    for (double freq : Tunings::A440) {
        Audiofile audiofile(fileName + " " + to_string(midiNumber), cwd);
        ofstream freqFile;
        freqFile.open(cwd + "/out/" + fileName + to_string(midiNumber) + ".txt");
        cout << "setting frequencies to " << freq << endl;
        oscBank->update_frequencies(freq);
        freqFile << oscBank->get_details();
        double prevSample = 0;
        int zero_crossings = 0;
        while (zero_crossings < 24){
            double sample = oscBank->process();
            int intSample = static_cast<int> (sample * maxAmplitude);
            audiofile.writeSample(intSample);
            if ( (prevSample < 0 && sample > 0) || (prevSample > 0 && sample < 0) || sample == 0) {
                zero_crossings++;
            }
        }
        audiofile.writeSample(static_cast<int>(0));

      /*  for (int i = 0; i < sampleRate * duration; i++) {
            double sample = oscBank->process();
            int intSample = static_cast<int> (sample * maxAmplitude);
            audiofile.writeSample(intSample);
        }*/
        midiNumber++;
    }
}

void generateFiles(OscillatorBank* oscBank, string cwd) {

    char mode = requestUserInput<char>("Enter mode ([s]cale or [u]nique)", 's');

    auto maxAmplitude = pow(2, bitDepth - 1) - 1;
    float duration = requestUserInput<float>("Enter duration (in seconds)", (float)4);
    string fileName = requestUserInput<string>("Enter file name ",__DATE__);


    if (mode == 'u') {
        Audiofile audiofile(fileName, cwd);

        ofstream freqFile;
        freqFile.open(cwd + "/out/" + fileName + ".txt");
        for (int i = 0; i < sampleRate * duration; i++) {
            double sample = oscBank->process();
            int intSample = static_cast<int> (sample * maxAmplitude);
            audiofile.writeSample(intSample);
        }

        for (int i = 0; i < oscBank->oscillators.size(); i++) {
            freqFile << oscBank->oscillators[i]->getFrequency() << "\n";
        }
        return;
    }

    int midiNumber = 0;
    for (double freq : Tunings::A440) {
        Audiofile audiofile(fileName + " " + to_string(midiNumber), cwd);
        ofstream freqFile;
        freqFile.open(cwd + "/out/" + fileName + to_string(midiNumber) + ".txt");
        cout << "setting frequencies to " << freq << endl;
        oscBank->update_frequencies(freq);
        freqFile << oscBank->get_details();
        for (int i = 0; i < sampleRate * duration; i++) {
            double sample = oscBank->process();
            int intSample = static_cast<int> (sample * maxAmplitude);
            audiofile.writeSample(intSample);
        }
        midiNumber++;
    }
}
