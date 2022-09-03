/*直流电机(无封装)*/
#include <iostream>
#include "simucpp.hpp"

int main()
{
    using namespace simucpp;
    using namespace std;
    Simulator sim1(2);
    double L = 0.0189;
    double R = 1.309;
    double J = 0.32;
    double D = 0;
    double Cm = 2.589;
    FUInput(Voltage, &sim1);
    FUInput(Loadtorque, &sim1);
    FUOutput(Current, &sim1);
    FUOutput(omega, &sim1);
    FUSum(sum1, &sim1);
    FUSum(sum2, &sim1);
    auto *tr1 = new TransferFcn(&sim1, vector<double>{1}, vector<double>{L, R});
    auto *tr2 = new TransferFcn(&sim1, vector<double>{1}, vector<double>{J, D});

    sim1.connectU(Voltage, sum1);
    sim1.connectU(sum1, tr1);
    sim1.connectU(tr1, sum2);
    sum2->Set_InputGain(Cm);
    sim1.connectU(sum2, tr2);
    sim1.connectU(tr2, omega);
    sim1.connectU(tr2, sum1);
    sum1->Set_InputGain(-Cm);
    sim1.connectU(Loadtorque, sum2);
    sum2->Set_InputGain(-1);
    sim1.connectU(tr1, Current);
    Voltage->Set_Function([](double t){return 400.0;});
    Loadtorque->Set_Function([](double t){return t<1?0:100.0;});

    sim1.Initialize();
    sim1.Simulate();
    cout.precision(12);
    cout << omega->Get_OutValue() << endl;
    cout << Current->Get_OutValue() << endl;
    sim1.Plot();
    return 0;
}
