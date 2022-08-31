/*单摆*/
#include <cmath>
#include "simucpp.hpp"

int main()
{
    using namespace simucpp;
    Simulator sim1;
    FUIntegrator(uint1, &sim1);
    FUIntegrator(uint2, &sim1);
    FUSum(usum1, &sim1);
    FUFcn(ufcn1, &sim1);
    FUOutput(uout1, &sim1);

    constexpr double k=1,m=1,l=1,g=9.8;
    uint1->Set_InitialValue(1);
    ufcn1->Set_Function([](double u){return -g/l*sin(u);});

    sim1.connectU(uint1, uint2);
    sim1.connectU(uint2, uout1);
    sim1.connectU(uint2, ufcn1);
    sim1.connectU(ufcn1, usum1);
    sim1.connectU(uint1, usum1);
    usum1->Set_InputGain(-k/m);
    sim1.connectU(usum1, uint1);

    sim1.Initialize();
    sim1.Simulate();
    sim1.Plot();
    return 0;
}
