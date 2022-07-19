/*零极点对消*/
#include "simucpp.hpp"
using namespace simucpp;
using namespace std;
int main()
{
    Simulator sim1(20);
    TransferFcn *tf1 = new TransferFcn(&sim1, vector<double>{1, -3}, vector<double>{1, 2, 0});
    TransferFcn *tf2 = new TransferFcn(&sim1, vector<double>{1}, vector<double>{1, -3});
    FMInput(in1, &sim1);
    FMSum(sum1, &sim1);
    FMGain(K, &sim1);
    FMOutput(out1, &sim1);
    FMOutput(u, &sim1);

    K->Set_Gain(3);

    sim1.connect(in1, sum1);
    sim1.connect(sum1, K);
    sim1.connect(K, tf1);
    sim1.connect(tf1, tf2);
    sim1.connect(tf2, sum1);
    sum1->Set_InputGain(-1);
    sim1.connect(tf2, out1);
    sim1.connect(tf1, u);

    sim1.Initialize();
    sim1.Simulate();
    cout.precision(12);
    cout << out1->Get_OutValue() << endl;
    cout << u->Get_OutValue() << endl;
    return 0;
}
