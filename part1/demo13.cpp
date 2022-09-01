/*离散低通滤波器*/
#include <iostream>
#include "simucpp.hpp"
using namespace simucpp;
using namespace std;

int main()
{
    Simulator sim1;
    auto *dtf1 = new DiscreteTransferFcn(&sim1, vecdble{0.008125, 0.01625, 0.008125}, vecdble{1.7, -0.7325});
    FUInput(min1, &sim1);
    FUNoise(min2, &sim1);
    FUZOH(mzoh1, &sim1);
    FUSum(msum1, &sim1);
    FUOutput(mout1, &sim1);
    FUOutput(mout2, &sim1);

    sim1.connectU(min1, mzoh1);
    sim1.connectU(mzoh1, msum1);
    sim1.connectU(min2, msum1);
    sim1.connectU(msum1, mout1);
    sim1.connectU(msum1, dtf1);
    sim1.connectU(dtf1, mout2);

    min1->Set_Function([](double t){return sin(t);});
    min2->Set_Variance(0.1);
    mzoh1->Set_SampleTime(0.1);
    min2->Set_SampleTime(0.1);
    dtf1->Set_SampleTime(0.1);

    sim1.Initialize();
    sim1.Simulate();
    cout.precision(12);
    PRINT_VALUE(mout2->Get_OutValue());
    sim1.Plot();
    return 0;
}
