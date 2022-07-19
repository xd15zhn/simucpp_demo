/*连续离散混合仿真*/
#include "simucpp.hpp"
using namespace simucpp;
using namespace std;
// # define DURATION_T1
int main()
{
    Simulator sim1;
    auto* mdGs = new TransferFcn(&sim1, vector<double>{1}, vector<double>{10, 1, 0});
    //auto *mdDs = new TransferFcn(&sim1, vector<double>{10, 1}, vector<double>{1, 1});  // 连续控制器
#ifdef DURATION_T1
    auto* mdDz = new DiscreteTransferFcn(&sim1, vector<double>{6.64, -6.008}, vector<double>{0.3679});  // T=1时的离散控制器
#else
    auto* mdDz = new DiscreteTransferFcn(&sim1, vector<double>{9.1565, -8.9752}, vector<double>{0.8187});  // T=0.2时的离散控制器
#endif
    FMInput(mdin1, &sim1);
    FMZOH(mdzoh1, &sim1);
    FMSum(mdsum1, &sim1);
    FMOutput(mdu, &sim1);
    FMOutput(mdy, &sim1);

    mdin1->Set_Function([](double t) { return 1.0; });
    // mdy->Set_InputGain(10);
#ifdef DURATION_T1
    sim1.Set_Duration(20);
    sim1.Set_SimStep(1/double(1<<10));
#else
    sim1.Set_Duration(5);
    mdzoh1->Set_SampleTime(0.2);
    mdDz->Set_SampleTime(0.2);
#endif
    sim1.Set_PrintPrecision(16);

    sim1.connect(mdin1, mdsum1);
    sim1.connect(mdsum1, mdzoh1);
    sim1.connect(mdzoh1, mdDz);
    sim1.connect(mdDz, mdGs);
    sim1.connect(mdGs, mdsum1);
    mdsum1->Set_InputGain(-1);
    sim1.connect(mdDz, mdu);
    sim1.connect(mdGs, mdy);

    sim1.Initialize();
    sim1.Simulate();
    cout.precision(16);
    cout << mdu->Get_OutValue() << endl;
    cout << mdy->Get_OutValue() << endl;
    sim1.Plot();
    return 0;
}
