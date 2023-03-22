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
#include "Audiofile.h"
#include "AdditiveBank.h"
#include "FMBank.h"
#include "standard_tuning_frequencies.h"
#include "requestUserInput.h"
#include "generateFiles.h"
#include "csv_parser.h"
using namespace std;

static string cwd;

int makeAWave(){
    OscillatorBank* oscBank;
    char genMode = requestUserInput<char>("Enter generator mode ([A]dditive or [F]requency Modulation)", 'a');
    if (genMode == 'A' || genMode == 'a') {
        oscBank = new AdditiveBank();
    }
    else {
        oscBank = new FMBank({});
    }
        oscBank->addOscillatorInteractive();

    generateFiles(oscBank, cwd);

    delete oscBank;

    char tryAgain = requestUserInput<char>("Try another? [y/n]", 'y');

    if (tryAgain == 'n' || tryAgain == 'N') {
        std::cout << "Goodbye!";
        return 0;
    }
    return makeAWave();
}

int makeAWave(string srcUrl) {
    cout << "srcUrl route" << endl;
    OscillatorBank* oscBank;
    std::ifstream       file(srcUrl);
    char genMode = requestUserInput<char>("Enter generator mode ([A]dditive or [F]requency Modulation)", 'a');
    if (genMode == 'A' || genMode == 'a') {
        oscBank = new AdditiveBank();
    }
    else {
        oscBank = new FMBank({});
    }

    for (auto& row : CSVRange(file))
    {
        cout << "doing a row" << endl;
        string args = row[0].data();
        double freq = atof(args.substr(0, args.find(',')).c_str());
        cout << "freq : " << freq << endl;
        double amp = atof(args.substr(args.find(',')+1, args.rfind(',')).c_str());
        cout << "amp : " << amp << endl;
        double modifier = atof(args.substr(args.rfind(',') + 1, args.size()-1).c_str());
        cout << "modifier : " << modifier << endl;
        oscBank->addOscillator(freq, amp, modifier);
    }
    generateFiles(oscBank, cwd);
    cout << "success";
    delete oscBank;
    return 0;
}

int makeAWave(string srcUrl, string outName, float duration, char scale, char mode) {
    cout << "full definition route" << endl;
    OscillatorBank* oscBank;
    std::ifstream       file(srcUrl);

    char genMode = scale ? 'a' : 'f';
    if (genMode == 'A' || genMode == 'a') {
        oscBank = new AdditiveBank();
    }
    else {
        oscBank = new FMBank({});
    }

    for (auto& row : CSVRange(file))
    {
        cout << "doing a row" << endl;
        string args = row[0].data();
        double freq = atof(args.substr(0, args.find(',')).c_str());
        cout << "freq : " << freq << endl;
        double amp = atof(args.substr(args.find(',') + 1, args.rfind(',')).c_str());
        cout << "amp : " << amp << endl;
        double modifier = atof(args.substr(args.rfind(',') + 1, args.size() - 1).c_str());
        cout << "modifier : " << modifier << endl;
        oscBank->addOscillator(freq, amp, modifier);
    }
    generateFiles(oscBank, cwd, outName, duration, scale, mode);
    cout << "success";
    delete oscBank;
    return 0;
}

int makeAWave(vector<float> freqs) {
    vector<float> frequencyList = freqs;
    OscillatorBank* oscBank;
    char genMode = requestUserInput<char>("Enter generator mode ([A]dditive or [F]requency Modulation)", 'a');
    if (genMode == 'A' || genMode == 'a') { 
        oscBank = new AdditiveBank(); 
    } else {
        oscBank = new FMBank({});
    }

    if (frequencyList.size() < 1) {
        oscBank->addOscillatorInteractive();
    } else {
        for (int i = 0; i < frequencyList.size(); i++) {
            oscBank->addOscillator(frequencyList[i]);
        }
    }

    generateFiles(oscBank, cwd);

    delete oscBank;

    char tryAgain = requestUserInput<char>("Try another? [y/n]", 'y');

    if (tryAgain == 'n' || tryAgain == 'N') {
        std::cout << "Goodbye!";
        return 0;
    }
    return makeAWave();
}


int parseArgs(int argCount, char* args[]) {
    //vector<string> argValues;
    string inputFile = "";
    string outName = "";
    float duration = 8;
    char scale = 's';
    char mode = 'a';

    for (int i = 1; i < argCount; i++) {
        char* a = args[i];
        
        //std::cout << args[i] << endl;
        if (a[0] == '-') {

            switch (a[1]) {
            case('i'):
                inputFile = args[++i];
                break;
            case('o'):
                outName = args[++i];
                break;
            case('d'):
                duration = stof(args[++i]);
                break;
            case('s'):
                scale = 's';
                break;
            case('u'):
                scale = 'u';
                break;
            case('a'):
                mode = 'a';
                break;
            case('m'):
                mode = 'm';
                break;
            default:
                break;
            }
        }
    }
    cout << inputFile << endl;
    cout << duration << endl;
    cout << outName << endl;
    cout << scale << endl;

    return makeAWave(inputFile, outName, duration, scale, mode);
}

int main(int argc, char* argv[])
{
    string filePath = argv[0];
    cwd = filePath.substr(0, filePath.find_last_of("/\\"));
    std::cout << cwd << endl;
    vector<float> argValues;
    cout << argc << "args" << endl;
    parseArgs(argc, argv);
    return 0;
    switch(argc){
    case(1):
        return makeAWave();
    case(2):
        cout << argv[1] << endl;
        return makeAWave(argv[1]);
    default:
        for (int i = 1; i < argc; i++) {
            std::cout << argv[i] << endl;
            argValues.push_back(strtof(argv[i], NULL));
        }
    }
    return makeAWave(argValues);
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