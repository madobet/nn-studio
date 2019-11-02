#ifndef VAIHARABRAINNET_H
#define VAIHARABRAINNET_H
#include "vneuronnet.h"
#include "./network/vbrainnet.h"
#include "./neuron/vaihara.h"

class VAiharaBrainNet : private VNeuronNet
{
public:
    VAiharaBrainNet();
    VAiharaBrainNet(int nsize, double** mat, double ikf, double ikr, double iai, double ialpha);
};

#endif // VAIHARABRAINNET_H
