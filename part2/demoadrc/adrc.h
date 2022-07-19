#ifndef __ADRC_H
#define __ADRC_H

#include "td.h"

class ADRC: public PackModule
{
public:
    ADRC(Simulator *sim);
private:
    virtual PUnitModule Get_InputPort(int n=0);
    virtual PUnitModule Get_OutputPort(int n=0);
};

#endif
