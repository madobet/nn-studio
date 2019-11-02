#ifndef VBRAINNET_H
#define VBRAINNET_H
#include "vgraph.h"

class VBrainNet : public VGraph
{
public:
    VBrainNet();
    VBrainNet(int size, double** mat);
};

#endif // VBRAINNET_H
