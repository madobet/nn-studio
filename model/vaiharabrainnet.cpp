#include "vaiharabrainnet.h"

VAiharaBrainNet::VAiharaBrainNet()
{
    network = new VBrainNet();
    int node_num = network->VertexNum();
    neuron = new VNeuron*[node_num];
    for(int i = 0; i < node_num; i++)
    {
        neuron[i] = new VAihara();
    }
}

VAiharaBrainNet::VAiharaBrainNet(int nsize, double **mat, double ikf, double ikr, double iai, double ialpha)
{
    network = new VBrainNet(nsize, mat);
    int node_num = network->VertexNum();
    neuron = new VNeuron*[node_num];
    for(int i = 0; i < node_num; i++)
    {
        neuron[i] = new VAihara(ikf, ikr, iai, ialpha, i+1);
    }
}
//VAiharaBrainNet::~VAiharaBrainNet()
//{
//}
