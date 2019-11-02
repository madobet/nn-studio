#include "vneuronnet.h"

VNeuronNet::VNeuronNet()
    :network(nullptr), neuron(nullptr)
{

}

VNeuronNet::~VNeuronNet()
{
    int num = network->VertexNum();
    delete network;
    network = nullptr;
    for(int i = 0; i < num; i++)
    {
        delete neuron[i];
    }
    delete[] neuron;
    neuron = nullptr;
}

VNeuronNet& VNeuronNet::Refresh()
{
    if(network == nullptr || neuron == nullptr)
        return *this;
    int node_num = network->VertexNum();
    double* other_neuron = new double[node_num];
    for(int i = 0;i < node_num;i++)
    {
        other_neuron[i] = 0;
        for(int j = 0; j < node_num; j++)
            other_neuron[i] += network->Weight(i,j)*neuron[j]->Measure();
    } // should sum other neurons' spkie-weight before refresh each neuron
    for(int i = 0;i < node_num;i++)
    {
        neuron[i]->Refresh(other_neuron[i]);
    }
    delete[] other_neuron;
    return *this;
}

VNeuronNet& VNeuronNet::Refresh(const double *stim)
{
    if(network == nullptr || neuron == nullptr)
        return *this;
    int node_num = network->VertexNum();
    double* other_neuron = new double[node_num];
    for(int i = 0;i < node_num;i++)
    {
        other_neuron[i] = 0;
        for(int j = 0; j < node_num; j++)
            other_neuron[i] += network->Weight(i,j)*neuron[j]->Measure();
    } // should sum other neurons' spkie-weight before refresh each neuron
    for(int i = 0;i < node_num;i++)
    {
        neuron[i]->Refresh(other_neuron[i],stim[i]);
    }
    delete[] other_neuron;
    return *this;
}
