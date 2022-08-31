/*多个单元模块*/
#include <iostream>
#include "simucpp.hpp"
using namespace simucpp;
using namespace std;

int main()
{
    Simulator sim1;
    FUInput(uin1, &sim1);
    FUIntegrator(uint1, &sim1);
    FUUnitDelay(delay1, &sim1);
    FUTransportDelay(tdelay1, &sim1);
    FUZOH(zoh1, &sim1);
    FUOutput(out0, &sim1);
    FUOutput(out1, &sim1);
    FUOutput(out2, &sim1);
    FUOutput(out3, &sim1);
    FUOutput(out4, &sim1);

    sim1.connectU(uin1, out0);
    sim1.connectU(uin1, uint1);
    sim1.connectU(uin1, delay1);
    sim1.connectU(uin1, tdelay1);
    sim1.connectU(uin1, zoh1);
    sim1.connectU(uint1, out1);
    sim1.connectU(delay1, out2);
    sim1.connectU(tdelay1, out3);
    sim1.connectU(zoh1, out4);

    uin1->Set_Function([](double t){return sin(t);});
    tdelay1->Set_InitialValue(1);
    tdelay1->Set_DelayTime(1.5);
    // out0->Set_EnableStore(false);
    // out1->Set_EnableStore(false);
    // out2->Set_EnableStore(false);
    // out3->Set_EnableStore(false);
    // out4->Set_EnableStore(false);

    sim1.Initialize();
    sim1.Simulate();
    cout.precision(12);
    cout << out0->Get_OutValue() << endl;
    cout << out1->Get_OutValue() << endl;
    cout << out2->Get_OutValue() << endl;
    cout << out3->Get_OutValue() << endl;
    cout << out4->Get_OutValue() << endl;
    sim1.Plot();
    return 0;
}
