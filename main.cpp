
#include <sndfile.hh>
#include <iostream>
#include <fstream>
#include <cmath>
#include <vector>
using namespace std;

#include "Particle.h"
#include "SoundModel.h"
#include "SoundSpectra.h"


// Sound model for muons
float pitchMuon = 400;
SoundSpectra spectraMuon({1,   2,   3,   4,    5   },
                         {1.0, 0.2, 0.1, 0.05, 0.01} );
float enveloppeMuon(float t) { return enveloppeADSR(0.03,0.09,0.15,0.18,t); }

// Sound model for electrons
float pitchElectron = 330;
SoundSpectra spectraElectron({1,   2,   3,   4,   5   } ,
                             {1.0, 0.5, 0.3, 0.1, 0.05} );
float enveloppeElectron(float t) { return enveloppeADSR(0.03,0.09,0.15,0.18,t); }

// Sound model for jets
float pitchJet = 170;
SoundSpectra spectraJet({1,   2,   3,   4,    5   } ,
                        {1.0, 0.2, 0.1, 0.05, 0.01} );
float enveloppeJet(float t) { return enveloppeADSR(0.10,0.3,0.23,0.35,t); }

// Sound model for invisible energy
float pitchInvisible = 100;
SoundSpectra spectraInvisible({1,   1.5,   2,   2.5,    3   } ,
                              {1.0, 0.2, 0.1, 0.05, 0.01} );
float enveloppeInvisible(float t) { return enveloppeADSR(0.3,0.5,0.5,0.7,t); }
    



int main()
{

    // 
    // Read input file (list of events)
    //
    
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
    // Now writing sound while associating particle from each event to sounds
    //

    int eventDuration = 5; // in second
    //int numberOfEvents = events.size();
    int numberOfEvents = 30;
    const int size = sampleRate * eventDuration * numberOfEvents;
    
    float sample[size];
    for (int e = 0 ; e < numberOfEvents ; e++) 
    {
         // Getting current event
         vector<Particle> currentEvent = events[e];
         
         // Initializing collection of sounds
         vector<SoundModel> soundsFromParticles;

         // Reading particle in current event and associating a sound for each of them
         for (unsigned int p = 0 ; p < currentEvent.size() ; p++)
         {
                  if (currentEvent[p].getId() == 13)
                 soundsFromParticles.push_back(SoundModel(spectraMuon,     enveloppeMuon,      eventDuration, currentEvent[p].getE()/400,  pitchMuon * (5 - currentEvent[p].getEta())/5 )); 
             else if (currentEvent[p].getId() == 11)
                 soundsFromParticles.push_back(SoundModel(spectraElectron, enveloppeElectron,  eventDuration, currentEvent[p].getE()/400,  pitchElectron * (5 - currentEvent[p].getEta())/5 )); 
             else if (currentEvent[p].getId() == 21)
                 soundsFromParticles.push_back(SoundModel(spectraJet,      enveloppeJet,       eventDuration, currentEvent[p].getE()/700,  pitchJet * (5 - currentEvent[p].getEta())/5 )); 
             else if (currentEvent[p].getId() == 12)
                 soundsFromParticles.push_back(SoundModel(spectraInvisible,enveloppeInvisible, eventDuration, currentEvent[p].getPt()/300, pitchInvisible )); 
             }
         
         // "Playing" the sound we got from particle, into the output
         for (int t = 0 ; t < sampleRate * eventDuration ; t++)
         {
             sample[t + sampleRate * eventDuration * e ] = 0;
             for (unsigned int s = 0 ; s < soundsFromParticles.size() ; s++)
             {
                 sample[t + sampleRate * eventDuration * e ] += soundsFromParticles[s].play(float(t) / sampleRate);
             }
         }
    }
    outfile.write(&sample[0], size);

    return 0;
}

