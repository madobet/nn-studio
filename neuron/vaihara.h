#ifndef VAIHARA_H
#define VAIHARA_H
#include "vneuron.h"

class VAihara : public VNeuron
{
public:
    VAihara();
    VAihara(double ikf, double ikr, double iai, double ialpha);
    VAihara(double ikf, double ikr, double iai, double ialpha, int nid);
    // create a Aihara neuron
    VAihara(const VAihara& n);
    VAihara(const VAihara& n, double dev);
    VAihara& operator=(const VAihara& n);
    // make a copy

    VAihara& Refresh() override;
    VAihara& Refresh(double other) override;
    VAihara& Refresh(double other, double stim) override;
    // refresh neuron status

    double MeasureIn() const;		// 测量内部状态
    VAihara& operator* (double dev);
    //~VAihara();

private:
    double kf;
    double kr;
    double ai;
    double alpha;
    // model parameter

    double etai;        // feedback from other neurons
    double zetai;       // 不应性

    double instat;      // inner status
};

#endif // VAIHARA_H
