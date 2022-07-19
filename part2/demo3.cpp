/*连续离散混合仿真2*/
#include "simucpp.hpp"
using namespace simucpp;
using namespace std;
// # define DURATION_T1
int main()
{
    Simulator sim1;
    auto* mdGs = new TransferFcn(&sim1, vector<double>{1.2}, vector<double>{1, 1, 0});
    FMInput(mdin1, &sim1);
    FMZOH(mdzoh1, &sim1);
    FMSum(mdsum1, &sim1);
    FMOutput(mdu, &sim1);
    FMOutput(mdy, &sim1);

    mdin1->Set_Function([](double t) { return cos(t); });
    sim1.Set_SimStep(1/double(1<<10));
#ifndef DURATION_T1
    mdzoh1->Set_SampleTime(0.5);
#endif
    sim1.Set_EnablePrint(false);
    sim1.Set_PrintPrecision(16);

    sim1.connect(mdin1, mdsum1);
    sim1.connect(mdsum1, mdzoh1);
    sim1.connect(mdzoh1, mdGs);
    sim1.connect(mdGs, mdsum1);
    mdsum1->Set_InputGain(-1);
    sim1.connect(mdsum1, mdu);
    sim1.connect(mdGs, mdy);

    sim1.Initialize();
    sim1.Simulate();
    cout.precision(16);
    cout << mdu->Get_OutValue() << endl;
    cout << mdy->Get_OutValue() << endl;
    return 0;
}
