# WaveGenerator

A CLI tool for generating waveforms

Run without any arguments and it will begin an interactive dialog for generating a waveform

Run with a csv file as an argument to generate waveforms based ont the contents of the file. 
CSV should be formatted as:
{harmonic},{amplitude},{modifier}

harmonic will be multiplied by the frequency of the midi pitch.
amplitude should usually be between 0.0 and 1.0. Can be any number, but will distort.
modifier is added to the calculated frequency of the oscillator

The program will walk you for the finishing details.
