#ifndef VNEURON_H
#define VNEURON_H
// base class of all neuron model
#include "./math/vmath.h"
#define NID -1

class VNeuron
{
public:
    VNeuron();                          // default initial status = 0
    VNeuron(int nid);
    VNeuron(double istat);
    VNeuron(double istat, int nid);     // specified initial status
    VNeuron(const VNeuron& neuron);
    VNeuron& operator=(const VNeuron&);        // make a copy
    // create a neuron

    int Mark() const;       // what id it is
    int Mark(int nid);      // set a new id and return it;
    double Measure() const; // "measure" and return current neuron spike
    virtual VNeuron& Refresh();   // "refresh" status, return true if successed
    virtual VNeuron& Refresh(double other);    // there sames to be some signal from other neuron..
    virtual VNeuron& Refresh(double other, double stim);    // not only other neurons but also stimulating neuron
    // do something with it!

    virtual ~VNeuron() = default;
    // destory your neuron

protected:
    double spike;   // value of neuron spike

private:
    int id;         // identification
};

#endif // VNEURON_H
