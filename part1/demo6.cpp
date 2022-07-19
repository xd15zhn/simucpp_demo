/*简谐振动*/
#include <iostream>
#include "simucpp.hpp"
using namespace simucpp;
using namespace std;

int main()
{
    Simulator sim1(150);
    FMIntegrator(mint1, &sim1);
    FMIntegrator(mint2, &sim1);
    FMSum(msum1, &sim1);
    FMInput(min1, &sim1);
    FMOutput(mout1, &sim1);

    constexpr double c=1;  // 弹簧劲度系数
    constexpr double mu=0;  // 动摩擦因数
    constexpr double m=0.2;  // 质量
    constexpr double H=0.1;  // 干扰力振幅
    constexpr double p=2.2;  // 干扰力频率


    sim1.connect(min1, msum1);
    sim1.connect(msum1, mint1);
    sim1.connect(mint1, mint2);
    sim1.connect(mint2, mout1);
    sim1.connect(mint2, msum1);
    msum1->Set_InputGain(-c/m);
    sim1.connect(mint1, msum1);
    msum1->Set_InputGain(-mu/m);

    mint1->Set_InitialValue(1);
    min1->Set_Function([](double u){ return H/m*sin(p*u); });
    sim1.Set_SampleTime(0.1);

    sim1.Initialize();
    sim1.Simulate();
    cout.precision(12);
    cout << mout1->Get_OutValue() << endl;
    sim1.Plot();
    return 0;
}
