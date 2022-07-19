#include "simucpp.hpp"
#include "controller.hpp"
using namespace simucpp;
using namespace std;

int main()
{
    Simulator sim1;
    FMGain(mg1, &sim1);
    FMFcn(mfcn1, &sim1);
    FMOutput(mout1, &sim1);
    sim1.connect(mg1, mfcn1);
    sim1.connect(mfcn1, mg1);
    sim1.connect(mfcn1, mout1);
    mg1->Set_Gain(2);
    sim1.Initialize();
    sim1.Simulate();
    cout.precision(16);
    PRINT_VALUE(mout1->Get_OutValue());
    sim1.Plot();
    return 0;
}
