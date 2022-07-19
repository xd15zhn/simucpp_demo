#ifndef __ESO_H
#define __ESO_H

#include <cmath>
#include "simucpp.hpp"
using namespace simucpp;
using namespace std;

#define ABS(x)                   ((x)>=0?(x):-(x))
#define SIGN(x)                  ((x)>=0?1:-1)
#define LIMIT(x,min,max)         (((x)<=(min) ? (min) : ((x)>=(max) ? (max) : (x))))

class ESO: public PackModule
{
public:
    ESO(Simulator *sim, string name="eso");
    void Set_SampleTime(double T);
    void Set_BandWidth(double w=10);
    MConnector *inu = nullptr;
    MConnector *iny = nullptr;
    MConnector *outz1 = nullptr;
    MConnector *outz2 = nullptr;
    MConnector *outw = nullptr;
    DiscreteIntegrator *disintz1 = nullptr;
    DiscreteIntegrator *disintz2 = nullptr;
    DiscreteIntegrator *disintw = nullptr;
    MSum *sumz1 = nullptr;
    MSum *sumz2 = nullptr;
    MSum *sumdw = nullptr;
    MGain *gainL1 = nullptr;
    MGain *gainL2 = nullptr;
    MGain *gainL3 = nullptr;
    MGain *gainb = nullptr;
private:
    virtual PUnitModule Get_InputPort(int n=0) const;
    virtual PUnitModule Get_OutputPort(int n=0) const;
};

#endif
