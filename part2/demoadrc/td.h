#ifndef __TD_H
#define __TD_H

#include <cmath>
#include "simucpp.hpp"
using namespace simucpp;
using namespace std;

#define ABS(x)                   ((x)>=0?(x):-(x))
#define SIGN(x)                  ((x)>=0?1:-1)
#define LIMIT(x,min,max)         (((x)<=(min) ? (min) : ((x)>=(max) ? (max) : (x))))

class TD: public PackModule
{
public:
    TD(Simulator *sim);
    void Set_SampleTime(double T);
    void Set_R(double R);
    MConnector *in1, *outx1, *outx2;
    DiscreteIntegrator *delayx1, *delayx2;
    MSum *sum1;
    MFcnMISO *fhan;
    MInput *constant;
    MGain *gainR, *gainH;
private:
    virtual PUnitModule Get_InputPort(int n=0) const;
    virtual PUnitModule Get_OutputPort(int n=0) const;
};

#endif
