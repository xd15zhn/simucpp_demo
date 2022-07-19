/*传递函数*/
#include <iostream>
#include <cmath>
#include "simucpp.hpp"

int main()
{
    using namespace simucpp;
    using namespace std;
    Simulator sim1(100);
    MInput *in1 = new MInput(&sim1);
    TransferFcn *tf1 = new TransferFcn(&sim1, vector<double>{1, 2}, vector<double>{1, 2, 3});
    MOutput *out1 = new MOutput(&sim1);

    in1->Set_Function([](double t){return 1.0;});

    sim1.connect(in1, tf1);
    sim1.connect(tf1, out1);

    sim1.Initialize();
    sim1.Set_ShowWave(false);
    sim1.Simulate();
    cout.precision(12);
    cout << out1->Get_OutValue() << endl;
    sim1.Plot();
    return 0;
}
