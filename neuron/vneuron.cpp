#include "vneuron.h"

VNeuron::VNeuron()
    :spike(0), id(NID)
{
}

VNeuron::VNeuron(int nid)
    :spike(0), id(nid)
{
}

VNeuron::VNeuron(double istat)
    :spike(istat), id(NID)
{
}

VNeuron::VNeuron(double istat, int nid)
    :spike(istat), id(nid)
{
}

VNeuron::VNeuron(const VNeuron & n)
    :spike(n.spike), id(n.id)
{
}

VNeuron& VNeuron::operator=(const VNeuron& n)
{
    this->spike = n.spike;
    this->id = n.id;
    return *this;
}
//----------------------------------------


int VNeuron::Mark() const
{
    return id;
}

int VNeuron::Mark(int nid)
{
    id = nid;
    return id;
}

double VNeuron::Measure() const
{
    return spike;
}

VNeuron& VNeuron::Refresh(){
    spike = Sgn(spike);
    return *this;
}

VNeuron& VNeuron::Refresh(double other){
    spike = Sgn(spike + other);
    return *this;
}

VNeuron& VNeuron::Refresh(double other, double stim){
    spike = Sgn(spike + other + stim);
    return *this;
}
