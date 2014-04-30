#ifndef PARTICLE_H
#define PARTICLE_H

#include <iostream>
using namespace std;

class Particle
{
    public:
        
        Particle(ifstream* inputFile)
        {
            (*inputFile) >> id;
            (*inputFile) >> pt;
            (*inputFile) >> eta;
            (*inputFile) >> phi;
            (*inputFile) >> E;
        }
    
        Particle(int id_, float pt_, float eta_, float phi_, float E_)
        {
            id  = id_;
            pt  = pt_;
            eta = eta_;
            phi = phi_;
            E   = E_;
        }

        ~Particle() { };

        int   getId()  { return id;  }
        float getPt()  { return pt;  }
        float getEta() { return eta; }
        float getPhi() { return phi; }
        float getE()   { return E;   }

    private:

        int   id;
        float pt;
        float eta;
        float phi;
        float E;
};

#endif
