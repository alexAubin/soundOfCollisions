#ifndef SOUNDMODEL_H
#define SOUNDMODEL_H

class SoundModel
{
    public:
        
        SoundModel(vector<pair<float,float> > harmonics_,
        float (*enveloppe_)(float),
        float length_,
        float amplitude_,
        float pitchModifier_)
        {
            harmonics     = harmonics_;
            enveloppe     = enveloppe_;
            length        = length_;
            amplitude     = amplitude_;
            pitchModifier = pitchModifier_;
        }
    
        ~SoundModel() { };

        float play(float t)  
        { 
            float value = 0;
            for (unsigned int i = 0 ; i < harmonics.size() ; i++)
            {
                float h_frequency = harmonics[i].first;
                float h_amplitude = harmonics[i].second;
                value += h_amplitude * sin(t*(2*M_PI) * h_frequency * pitchModifier);
            }
            value *= amplitude * enveloppe(t/length);
            return value;
        }

    private:

        vector<pair<float,float> > harmonics;
        float (*enveloppe)(float);
        float length;
        float amplitude;
        float pitchModifier;
};


float enveloppeADSR(float t_A, float t_D, float l_s, float t_R, float t)
{
    if ((t < 0) || (t > 1)) 
        return 0;

    if (t <= t_A) 
        return t / t_A;
    
    if ((t > t_A) && (t < t_D))
        return (t * (l_s - 1) + t_D - l_s * t_A) / (t_D - t_A);

    if ((t >= t_D) && (t <= t_R))
        return l_s;

    if (t > t_R)
        return l_s * (t - 1) / (t_R - 1);

    return 0;
}


#endif
