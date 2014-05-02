#ifndef SOUNDSPECTRA_H
#define SOUNDSPECTRA_H

class SoundSpectra
{
    public:
        
        SoundSpectra(   vector<float> harmonics_,
                        vector<float> amplitudes_)
        {
            harmonics     = harmonics_;
            amplitudes    = amplitudes_;
        }
    
        ~SoundSpectra() { };

        int getNComponents() { return harmonics.size(); }
        float getHarmonics(int i) { return harmonics[i]; }
        float getAmplitude(int i) { return amplitudes[i]; }

    private:

        vector<float> harmonics;
        vector<float> amplitudes;
};


#endif
