/*一阶非齐次线性微分方程*/
#include <iostream>
#include "simucpp.hpp"
using namespace simucpp;
using namespace std;

int main()
{
    Simulator sim1(15);
    FMIntegrator(y1, &sim1);
    FMSum(sum1, &sim1);
    FMProduct(prod1, &sim1);
    FMInput(input1, &sim1);
    FMInput(input2, &sim1);
    FMOutput(output1, &sim1);

    sim1.connect(input1, sum1);
    sim1.connect(sum1, y1);
    sim1.connect(y1, output1);
    sim1.connect(y1, prod1);
    sim1.connect(input2, prod1);
    sim1.connect(prod1, sum1);

    y1->Set_InitialValue(1);
    input1->Set_Function([](double t){return sin(t);});
    input2->Set_Function([](double t){return -2/(t+1);});

    sim1.Initialize();
    sim1.Simulate();
    cout.precision(12);
    cout << output1->Get_OutValue() << endl;
    sim1.Plot();
    return 0;
}
