/*时滞系统*/
#include <iostream>
#include "simucpp.hpp"
int main()
{
    using namespace simucpp;
    using namespace std;
    // double tau = 2*M_PI/3/sqrt(3);
    double tau = 15;
    Simulator sim1(100);
    TransferFcn *tf1 = new TransferFcn(&sim1, vector<double>{2}, vector<double>{1, 1}, "tf1");
    TransferFcn *tf2 = new TransferFcn(&sim1, vector<double>{2}, vector<double>{1, 1}, "tf2");
    FUConstant(in1, &sim1);
    FUTransportDelay(trd1, &sim1);
    FUTransportDelay(trd2, &sim1);
    FUSum(sum1, &sim1);
    FUSum(sum2, &sim1);
    FUOutput(out1, &sim1);
    FUOutput(out2, &sim1);

    sim1.connectU(in1, sum1);
    sim1.connectU(sum1, trd1);
    sim1.connectU(trd1, tf1);
    sim1.connectU(tf1, out1);
    sim1.connectU(tf1, sum1);
    sum1->Set_InputGain(-1);
    sim1.connectU(in1, sum2);
    sim1.connectU(sum2, tf2);
    sim1.connectU(tf2, trd2);
    sim1.connectU(trd2, out2);
    sim1.connectU(trd2, sum2);
    sum2->Set_InputGain(-1);

    trd1->Set_DelayTime(tau);
    trd2->Set_DelayTime(tau);
    sim1.Set_SampleTime(0.1);

    sim1.Initialize();
    sim1.Simulate();
    cout.precision(12);
    cout << out1->Get_OutValue() << endl;
    cout << out2->Get_OutValue() << endl;
    sim1.Plot();
    return 0;
}
