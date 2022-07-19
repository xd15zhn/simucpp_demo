/*直流电机(无封装)*/
#include <cmath>
#include "simucpp.hpp"

int main()
{
    using namespace simucpp;
    using namespace std;
    Simulator sim1(10);
    double L = 0.0189;
    double R = 1.309;
    double J = 0.32;
    double D = 0;
    double Cm = 2.589;
    MInput *Voltage = new MInput(&sim1);
    MInput *Loadtorque = new MInput(&sim1);
    MOutput *Current = new MOutput(&sim1);
    MOutput *omega = new MOutput(&sim1);
    MSum *sum1 = new MSum(&sim1);
    MSum *sum2 = new MSum(&sim1);
    TransferFcn *tr1 = new TransferFcn(&sim1, vector<double>{1}, vector<double>{L, R});
    TransferFcn *tr2 = new TransferFcn(&sim1, vector<double>{1}, vector<double>{J, D});

    sim1.connect(Voltage, sum1);
    sim1.connect(sum1, tr1);
    sim1.connect(tr1, sum2);
    sum2->Set_InputGain(Cm);
    sim1.connect(sum2, tr2);
    sim1.connect(tr2, omega);
    sim1.connect(tr2, sum1);
    sum1->Set_InputGain(-Cm);
    sim1.connect(Loadtorque, sum2);
    sum2->Set_InputGain(-1);
    sim1.connect(tr1, Current);
    Voltage->Set_Function([](double t){return 400.0;});
    Loadtorque->Set_Function([](double t){return t<5?0:100.0;});

    sim1.Initialize();
    sim1.Simulate();
    cout.precision(12);
    cout << omega->Get_OutValue() << endl;
    cout << Current->Get_OutValue() << endl;
    sim1.Plot();
    return 0;
}
