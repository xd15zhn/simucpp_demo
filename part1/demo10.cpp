/*零极点对消*/
#include <iostream>
#include "simucpp.hpp"
using namespace simucpp;
using namespace std;
int main()
{
    Simulator sim1(20);
    TransferFcn *tf1 = new TransferFcn(&sim1, vector<double>{1, -3}, vector<double>{1, 2, 0});
    TransferFcn *tf2 = new TransferFcn(&sim1, vector<double>{1}, vector<double>{1, -3});
    FUInput(uin1, &sim1);
    FUSum(usum1, &sim1);
    FUGain(uK, &sim1);
    FUOutput(uout1, &sim1);
    FUOutput(uout2, &sim1);

    uK->Set_Gain(3);
    uout1->Set_EnableStore(false);
    // uout2->Set_EnableStore(false);

    sim1.connectU(uin1, usum1);
    sim1.connectU(usum1, uK);
    sim1.connectU(uK, tf1);
    sim1.connectU(tf1, tf2);
    sim1.connectU(tf2, usum1);
    usum1->Set_InputGain(-1);
    sim1.connectU(tf1, uout1);
    sim1.connectU(tf2, uout2);

    sim1.Initialize();
    sim1.Simulate();
    cout.precision(12);
    cout << uout1->Get_OutValue() << endl;
    cout << uout2->Get_OutValue() << endl;
    sim1.Plot();
    return 0;
}
