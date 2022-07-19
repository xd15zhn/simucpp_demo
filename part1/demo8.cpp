/*线性微分方程组*/
#include <iostream>
#include "simucpp.hpp"
using namespace simucpp;
using namespace std;

int main()
{
    Simulator sim1(1);
    FUIntegrator(y1, &sim1);
    FUIntegrator(y2, &sim1);
    FUIntegrator(y3, &sim1);
    FUSum(sum1, &sim1);
    FUSum(sum2, &sim1);
    FUSum(sum3, &sim1);
    FUOutput(output1, &sim1);
    FUOutput(output2, &sim1);
    FUOutput(output3, &sim1);

    sim1.connect(sum1, y1);
    sim1.connect(sum2, y2);
    sim1.connect(sum3, y3);
    sim1.connect(y1, sum1);
    sum1->Set_InputGain(-1);
    sim1.connect(y2, sum1);
    sim1.connect(y1, sum2);
    sum2->Set_InputGain(-4);
    sim1.connect(y2, sum2);
    sum2->Set_InputGain(3);
    sim1.connect(y1, sum3);
    sim1.connect(y3, sum3);
    sum3->Set_InputGain(2);
    sim1.connect(y1, output1);
    sim1.connect(y2, output2);
    sim1.connect(y3, output3);

    y1->Set_InitialValue(1);
    y2->Set_InitialValue(1);
    y3->Set_InitialValue(1);
    sim1.Set_SimStep(1/double(1<<10));

    sim1.Initialize();
    sim1.Simulate();
    cout.precision(12);
    cout << output1->Get_OutValue() << endl;
    sim1.Plot();
    return 0;
}
