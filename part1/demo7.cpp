/*传递函数*/
#include <iostream>
#include <cmath>
#include "simucpp.hpp"

int main()
{
    using namespace simucpp;
    using namespace std;
    Simulator sim1(10);
    auto *in1 = new UInput(&sim1);
    auto *tf1 = new TransferFcn(&sim1, vector<double>{1, 2}, vector<double>{1, 2, 3});
    auto *out1 = new UOutput(&sim1);

    in1->Set_Function([](double t){return 1.0;});

    sim1.connectU(in1, tf1);
    sim1.connectU(tf1, out1);

    sim1.Initialize();
    sim1.Simulate();
    cout.precision(12);
    cout << out1->Get_OutValue() << endl;
    sim1.Plot();
    return 0;
}
