/*连续离散混合仿真2*/
#include <iostream>
#include "simucpp.hpp"
using namespace simucpp;
using namespace std;
int main()
{
    Simulator sim1;
    auto* utfGs = new TransferFcn(&sim1, vector<double>{1.2}, vector<double>{1, 1, 0});
    FUInput(uin1, &sim1);
    FUZOH(uzoh1, &sim1);
    FUSum(usum1, &sim1);
    FUOutput(uoutu, &sim1);
    FUOutput(uouty, &sim1);

    uin1->Set_Function([](double t) { return cos(t); });
    sim1.Set_SimStep(1/double(1<<10));
    sim1.Set_PrintPrecision(16);

    sim1.connectU(uin1, usum1);
    sim1.connectU(usum1, uzoh1);
    sim1.connectU(uzoh1, utfGs);
    sim1.connectU(utfGs, usum1);
    usum1->Set_InputGain(-1);
    sim1.connectU(uzoh1, uoutu);
    sim1.connectU(utfGs, uouty);
    sim1.Set_EnablePrint(true);

    sim1.Initialize();
    sim1.Simulate();
    cout.precision(16);
    cout << uoutu->Get_OutValue() << endl;
    cout << uouty->Get_OutValue() << endl;
    return 0;
}
