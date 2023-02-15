#include <fstream>
#include <stdlib.h>
#include <string>
using namespace std;

void writeToFile(ofstream& file, int value, int size) {
    file.write(reinterpret_cast<const char*> (&value), size);
};


class Audiofile{
	ofstream file, preAudioPosition;
    void prepareHeaders() {//header chunk
        file << "RIFF" << "----" << "WAVE";

        //format chunk
        file << "fmt ";
        writeToFile(file, 16, 4); //size
        writeToFile(file, 1, 2); //compression code
        writeToFile(file, 1, 2); //number of channels
        writeToFile(file, sampleRate, 4); //sample rate
        writeToFile(file, sampleRate * bitDepth / 8, 4); //byte rate ( sampleRate * bit depth * number of channels / 8
        writeToFile(file, 2, 2); //block align
        writeToFile(file, bitDepth, 2); // bit depth

        //Data chunk
        file << "data" << "----";
        preAudioPosition = file.tellp();
    }

    void finalizeHeaders() {
        int postAudioPosition = file.tellp();

        file.seekp(preAudioPosition - 4);
        writeToFile(file, postAudioPosition - preAudioPosition, 4);

        file.seekp(4, ios::beg);
        writeToFile(file, postAudioPosition - 8, 4);
        file.close();
    }
public:
	Audiofile(std::string fileName, cwd ) {
		file.open(cwd + "/out/" + fileName + ".wav", ios::binary);
        prepareHeaders();
	}
    ~Audiofile() {
        finalizeHeaders();
    }
    void writeSample(int sample) {
        writeToFile(file, sample, 2);
    }
};