/*多个单元模块*/
#include "simucpp.hpp"
using namespace simucpp;
using namespace std;

int main()
{
    Simulator sim1;
    FMInput(source, &sim1);
    FMIntegrator(integrator1, &sim1);
    FMUnitDelay(delay1, &sim1);
    FMTransportDelay(tdelay1, &sim1);
    FMZOH(zoh1, &sim1);
    FMOutput(out0, &sim1);
    FMOutput(out1, &sim1);
    FMOutput(out2, &sim1);
    FMOutput(out3, &sim1);
    FMOutput(out4, &sim1);

    sim1.connect(source, out0);
    sim1.connect(source, integrator1);
    sim1.connect(source, delay1);
    sim1.connect(source, tdelay1);
    sim1.connect(source, zoh1);
    sim1.connect(integrator1, out1);
    sim1.connect(delay1, out2);
    sim1.connect(tdelay1, out3);
    sim1.connect(zoh1, out4);

    source->Set_Function([](double t){return sin(t);});
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
