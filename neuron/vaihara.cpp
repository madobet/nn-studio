#include "./neuron/vaihara.h"
#include "./math/vmath.h"
#include <cstdlib>


VAihara::VAihara()
    : VNeuron(double(std::rand() % 2)), kf(0.15), kr(0.5), ai(2), alpha(10), etai(0), zetai(0), instat(0)
{
}

VAihara::VAihara(double ikf, double ikr, double iai, double ialpha)
    : VNeuron(double(std::rand() % 2)), kf(ikf), kr(ikr), ai(iai), alpha(ialpha), etai(0), zetai(0), instat(0)
{
}

VAihara::VAihara(double ikf, double ikr, double iai, double ialpha, int nid)
    : VNeuron(double(std::rand() % 2), nid), kf(ikf), kr(ikr), ai(iai), alpha(ialpha), etai(0), zetai(0), instat(0)
{
}

VAihara::VAihara(const VAihara & n)
    : VNeuron(n.spike, n.Mark()), kf(n.kf), kr(n.kr), ai(n.ai), alpha(n.alpha), etai(n.etai), zetai(n.zetai), instat(n.instat)
{
}

VAihara::VAihara(const VAihara & n, double dev)
    : VNeuron(n.Mark()), kf(n.kf), kr(n.kr), ai(n.ai), alpha(n.alpha), etai(n.etai*(1 + dev)), zetai(n.zetai*(1 + dev))
{
    instat = etai + zetai;
    spike = Sigmoid(instat);
}

VAihara& VAihara::operator=(const VAihara& n)
{
    this->Mark(n.Mark());    // id在基类是private，是否应该调用基类接口来设置？能否直接赋值？
    this->spike = n.spike;

    this->kf = n.kf;
    this->kr = n.kr;
    this->ai = n.ai;
    this->alpha = n.alpha;

    this->etai = n.etai;
    this->zetai = n.zetai;
    this->instat = n.instat;

    return *this;
}
//-----------------------------------------------------


VAihara& VAihara::Refresh()
{
    etai = kf*etai;
    zetai = kr*zetai - alpha*spike + ai;
    instat = etai + zetai;
    spike = Sigmoid(instat);
    return *this;
}

VAihara& VAihara::Refresh(double other)
{
    etai = kf*etai + other;
    zetai = kr*zetai - alpha*spike + ai;
    instat = etai + zetai;
    spike = Sigmoid(instat);
    return *this;
}

VAihara& VAihara::Refresh(double other, double stim)
{
    etai = kf*etai + other;
    zetai = kr*zetai - alpha*spike + ai;
    instat = etai + zetai;
    spike = Sigmoid(instat);
    return *this;
}
// refresh neuron status

double VAihara::MeasureIn() const
{
    return instat;
}

VAihara& VAihara::operator*(double dev)
{
    etai += etai*dev;
    zetai += zetai*dev;
    instat = etai + zetai;
    spike = Sigmoid(instat);
    return *this;
}
