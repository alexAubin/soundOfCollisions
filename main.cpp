
#include <sndfile.hh>
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
using namespace std;

#include "Particle.h"
#include "SoundModel.h"
#include "SoundSpectra.h"

float enveloppeTest(float t)
{
    return enveloppeADSR(0.04,0.12,0.3,0.18,t);
}

int main()
{

    // 
    // Read input file (list of events)
    //
    
    /*
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
    */

    //
    // Settings for WAV output
    //

    
    const int format=SF_FORMAT_WAV | SF_FORMAT_PCM_16;
    //const int format=SF_FORMAT_WAV | SF_FORMAT_FLOAT;
    const int channels=1;
    const int sampleRate=48000;
    const char* outfilename="foo.wav";

    SndfileHandle outfile(outfilename, SFM_WRITE, format, channels, sampleRate);
    if (not outfile) return -1;
    


    //
    // Some draft to write the WAV
    //

    /*
    float eventPerSeconds = 0.333;
    const int size = sampleRate * events.size() / eventPerSeconds;
    float sample[size];
    for (int i=0; i<size; i++) 
    {
        //int currentEvent = i / sampleRate;
        sample[i] = 0;

        // Current plan is to have :
        // E   : amplitude
        // Eta : pitch
        // Id  : harmonics + enveloppe + basis freq

        
        //for (unsigned int j = 0 ; j < harmonics.size() ; j++)
        //{
        //    float amplitude = harmonics[j].first;
        //    float frequence = harmonics[j].second;
        //    sample[i] += amplitude * sin(float(i)/sampleRate*(2*M_PI) * frequence);
        //}
        
    }
    outfile.write(&sample[0], size);
    */

    SoundSpectra testSpectra({1,   2,   3,   4,    5   } ,
                             {1.0, 0.2, 0.1, 0.05, 0.01} );

    float totalTime = 1;
    SoundModel testModel (testSpectra, enveloppeTest, totalTime, 0.55, 100);
    SoundModel testModel2(testSpectra, enveloppeTest, totalTime, 0.35, 80);
    
    const int size = sampleRate * totalTime;
    float sample[size];
    for (int t=0 ; t < size ; t++) 
    {
         sample[t] = testModel. play(float(t) / sampleRate)
                   + testModel2.play(float(t) / sampleRate);
    }
    outfile.write(&sample[0], size);

    return 0;
}

