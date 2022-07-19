/*离散传递函数与与单步仿真*/
#include <iostream>
#include "simucpp.hpp"
using namespace simucpp;
using namespace std;

int main()
{
    Simulator sim1;
    auto *mdtf1 = new DiscreteTransferFcn(&sim1, vecdble{1, 2, 1}, vecdble{0.75, -0.125});
    FMInput(mdin1, &sim1);
    FMOutput(mdout1, &sim1);
    sim1.connect(mdin1, mdtf1);
    sim1.connect(mdtf1, mdout1);
    //out1->Set_SampleTime(1);  // 设置OUTPUT模块每1秒保存一个数据

    sim1.Initialize();
    cout.precision(12);
    double lv, outvalue, t=0;  // 上个时刻、当前时刻的输出值，当前仿真时间
    lv = mdout1->Get_OutValue();
    while (t<=10) {
        t = sim1.Get_t();
        sim1.Simulate_OneStep();
        outvalue = mdout1->Get_OutValue();
        if (lv != outvalue) {  // 当前时刻的值与上个时刻不同时输出
            cout << t << ", " << outvalue << endl;
            lv = outvalue;
        }
    }
    return 0;
}
