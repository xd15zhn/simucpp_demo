#include "simucpp.hpp"
#include "controller.hpp"
using namespace simucpp;
using namespace std;

int main()
{
    Simulator sim1;
    FMInput(min1, &sim1);
    FMGain(mg0, &sim1);
    FMGain(mg1, &sim1);
    FMGain(mg2, &sim1);
    FMFcn(mf1, &sim1);
    FMFcn(mf2, &sim1);
    FMSum(msum1, &sim1);
    FMOutput(mout1, &sim1);
    sim1.connect(min1, mg0);
    sim1.connect(mg0, mg1);
    sim1.connect(mg1, mf1);
    sim1.connect(mf1, msum1);
    sim1.connect(mg0, mg2);
    sim1.connect(mg2, mf2);
    sim1.connect(mf2, msum1);
    sim1.connect(msum1, mout1);
    min1->Set_Function([](double t){return cos(t);});
    mg1->Set_Gain(2);
    mg2->Set_Gain(3);
    sim1.Initialize();
    sim1.Simulate();
    cout.precision(16);
    PRINT_VALUE(mout1->Get_OutValue());
    sim1.Plot();
    return 0;
}
