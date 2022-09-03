/*多次重复仿真验证连续离散混合仿真结果*/
#include <iostream>
#include <cmath>
#include "simucpp.hpp"
using namespace simucpp;
using namespace std;
// #define DURATION_T1
int main()
{
#ifdef DURATION_T1
    Simulator sim1(1);
    sim1.Set_SimStep(1/double(1<<10));
#else
    Simulator sim1(0.2);
#endif
    TransferFcn* mdGs = new TransferFcn(&sim1, vector<double>{1}, vector<double>{10, 1, 0});
    FUInput(mdin1, &sim1);
    FUGain(mdgain1, &sim1);
    FUOutput(mdu, &sim1);
    FUOutput(mdy, &sim1);

    double e=0, e1=0, u=0, y=0;
    sim1.Set_PrintPrecision(16);

    sim1.connectU(mdin1, mdgain1);
    sim1.connectU(mdgain1, mdGs);
    sim1.connectU(mdgain1, mdu);
    sim1.connectU(mdGs, mdy);

    sim1.Initialize();
    cout.precision(16);
#ifdef DURATION_T1
    for (int i=0;i<20;i++){
        e1 = e;
        e = 1.0 - y;
        u = 0.3679*u + 6.64*e - 6.008*e1;
        mdgain1->Set_Gain(u);
        sim1.Set_t(0);
        sim1.Simulate();
        y = mdy->Get_OutValue();
        cout << u << ", " << y << endl;
    }
#else
    for (int i=0;i<25;i++){
        e1 = e;
        e = 1.0 - y;
        u = 0.8187*u + 9.1565*e - 8.9752*e1;
        mdgain1->Set_Gain(u);
        sim1.Set_t(0);
        sim1.Simulate();
        y = mdy->Get_OutValue();
        cout << u << ", " << y << endl;
    }
#endif
    return 0;
}
