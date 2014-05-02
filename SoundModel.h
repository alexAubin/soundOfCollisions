#ifndef SOUNDMODEL_H
#define SOUNDMODEL_H

#include "SoundSpectra.h"

class SoundModel
{
    public:
        
        SoundModel(SoundSpectra spectra_,
                   float (*enveloppe_)(float),
                   float length_,
                   float amplitude_,
                   float pitchModifier_) :
        spectra(spectra_)
        {
            enveloppe     = enveloppe_;
            length        = length_;
            amplitude     = amplitude_;
            pitchModifier = pitchModifier_;
        }
    
        ~SoundModel() { };

        float play(float t)  
        { 
            float value = 0;
            for (int i = 0 ; i < spectra.getNComponents() ; i++)
            {
                float h_frequency = spectra.getHarmonics(i);
                float h_amplitude = spectra.getAmplitude(i);
                value += h_amplitude * sin(t * (2*M_PI) * h_frequency * pitchModifier);
            }
            value *= amplitude * enveloppe(t/length);
            return value;
        }

    private:

        SoundSpectra spectra;
        float (*enveloppe)(float);
        float length;
        float amplitude;
        float pitchModifier;
};


float enveloppeADSR(float t_A, float t_D, float l_S, float t_R, float t)
{
    if ((t < 0) || (t > 1)) 
        return 0;

    if (t <= t_A) 
        return t / t_A;
    
    if ((t > t_A) && (t < t_D))
        return (t * (l_S - 1) + t_D - l_S * t_A) / (t_D - t_A);

    if ((t >= t_D) && (t <= t_R))
        return l_S;

    if (t > t_R)
        return l_S * (t - 1) / (t_R - 1);

    return 0;
}


#endif
