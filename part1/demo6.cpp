/*简谐振动与共振*/
#include <iostream>
#include "simucpp.hpp"
using namespace simucpp;
using namespace std;

int main()
{
    Simulator sim1(150);
    FUIntegrator(uint1, &sim1);
    FUIntegrator(uint2, &sim1);
    FUSum(usum1, &sim1);
    FUInput(uin1, &sim1);
    FUOutput(uout1, &sim1);

    constexpr double c=1;  // 弹簧劲度系数
    constexpr double mu=0;  // 动摩擦因数
    constexpr double m=0.2;  // 质量
    constexpr double H=0.1;  // 干扰力振幅
    constexpr double p=2.2;  // 干扰力频率

    sim1.connectU(uin1, usum1);
    sim1.connectU(usum1, uint1);
    sim1.connectU(uint1, uint2);
    sim1.connectU(uint2, uout1);
    sim1.connectU(uint2, usum1);
    usum1->Set_InputGain(-c/m);
    sim1.connectU(uint1, usum1);
    usum1->Set_InputGain(-mu/m);

    uint1->Set_InitialValue(1);
    uin1->Set_Function([](double u){ return H/m*sin(p*u); });
    sim1.Set_SampleTime(0.1);

    sim1.Initialize();
    sim1.Simulate();
    cout.precision(12);
    cout << uout1->Get_OutValue() << endl;
    sim1.Plot();
    return 0;
}
