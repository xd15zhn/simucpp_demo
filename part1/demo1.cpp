/*一阶系统阶跃响应*/
#include <iostream>
#include "simucpp.hpp"
using namespace simucpp;
using namespace std;

double Input_Function(double t)
{
    return 1;
}

int main()
{
    // 初始化仿真器
    Simulator sim1(10);

    // 初始化模块
    UIntegrator *integrator1 = new UIntegrator(&sim1);
    USum *sum1 = new USum(&sim1);
    UInput *input1 = new UInput(&sim1);
    UOutput *output1 = new UOutput(&sim1);

    // 模块之间的连接
    sim1.connectU(input1, sum1);
    sum1->Set_InputGain(1);
    sim1.connectU(sum1, integrator1);
    sim1.connectU(integrator1, sum1);
    sum1->Set_InputGain(-0.5);
    sim1.connectU(integrator1, output1);

    // 参数设置
    integrator1->Set_InitialValue(0);
    input1->Set_Function(Input_Function);

    // 运行仿真
    sim1.Initialize();
    sim1.Simulate();
    cout.precision(12);
    cout << output1->Get_OutValue() << endl;
    sim1.Plot();
    return 0;
}