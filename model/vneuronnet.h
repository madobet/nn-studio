#ifndef VNEURONNET_H
#define VNEURONNET_H
#include "./network/vgraph.h"
#include "./neuron/vneuron.h"

class VNeuronNet
{
public:
    VNeuronNet();
    virtual ~VNeuronNet();

    virtual VNeuronNet& Refresh();
    virtual VNeuronNet& Refresh(const double* stim);
    // refresh topology or status

protected:
    VGraph* network;
    VNeuron** neuron;
    // you can even use different neuron model in the network
};

#endif // VNEURONNET_H

// 能否把模型生成做成模板？
