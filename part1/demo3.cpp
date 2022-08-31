/*Mathieu方程*/
#include <iostream>
#include <cmath>
#include "simucpp.hpp"

constexpr double pax = 0.236;
constexpr double pqx = 0.706;

double Input_Function(double t)
{
    return (pqx + pqx) * cos(t + t) - pax;
}

int main()
{
    using namespace simucpp;
    using namespace std;
    Simulator sim1(15);
    FUIntegrator(uint1, &sim1);
    FUIntegrator(uint2, &sim1);
    FUProduct(uprod1, &sim1);
    FUInput(uin1, &sim1);
    FUOutput(uout1, &sim1);

    uint2->Set_InitialValue(1);
    uin1->Set_Function(Input_Function);

    sim1.connectU(uin1, uprod1);
    sim1.connectU(uprod1, uint1);
    sim1.connectU(uint1, uint2);
    sim1.connectU(uint2, uout1);
    sim1.connectU(uint2, uprod1);

    sim1.Initialize();
    sim1.Simulate();
    cout.precision(12);
    cout << uout1->Get_OutValue() << endl;
    sim1.Plot();
    return 0;
}
