
#include <sndfile.hh>
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
using namespace std;

#include "Particle.h"
#include "SoundModel.h"

int main()
{
    ifstream eventFile("example.dat");
    vector<vector<Particle> > events;


    while (!(eventFile.eof()))
    {
        vector<Particle> particles;
        int eventNumber;
        int nParticles;
        eventFile >> eventNumber >> nParticles;
        for (int i = 0 ; i < nParticles ; i++)
        {
            particles.push_back(Particle(&eventFile));
        }
        events.push_back(particles);
    }

    const int format=SF_FORMAT_WAV | SF_FORMAT_PCM_16;
    //const int format=SF_FORMAT_WAV | SF_FORMAT_FLOAT;
    const int channels=1;
    const int sampleRate=48000;
    const char* outfilename="foo.wav";

    SndfileHandle outfile(outfilename, SFM_WRITE, format, channels, sampleRate);
    if (not outfile) return -1;

    float eventPerSeconds = 0.333;
    const int size = sampleRate * events.size() / eventPerSeconds;
    float sample[size];
    for (int i=0; i<size; i++) 
    {
        //int currentEvent = i / sampleRate;
        sample[i]= 0;

        // Current plan is to have :
        // E   : amplitude
        // Eta : pitch
        // Id  : harmonics + enveloppe + basis freq

        /*
        for (unsigned int j = 0 ; j < harmonics.size() ; j++)
        {
            float amplitude = harmonics[j].first;
            float frequence = harmonics[j].second;
            sample[i] += amplitude * sin(float(i)/sampleRate*(2*M_PI) * frequence);
        }
        */
    }
    outfile.write(&sample[0], size);
    return 0;
}

