/*离散传递函数与与单步仿真*/
#include <iostream>
#include "simucpp.hpp"
using namespace simucpp;
using namespace std;

int main()
{
    Simulator sim1;
    auto *utf1 = new DiscreteTransferFcn(&sim1, vecdble{1, 2, 1}, vecdble{0.75, -0.125});
    FUInput(uin1, &sim1);
    FUOutput(uout1, &sim1);
    sim1.connectU(uin1, utf1);
    sim1.connectU(utf1, uout1);
    //out1->Set_SampleTime(1);  // 设置OUTPUT模块每1秒保存一个数据

    sim1.Initialize();
    cout.precision(12);
    double lv, outvalue, t=0;  // 上个时刻、当前时刻的输出值，当前仿真时间
    int cnt=0;  // 采样点个数
    lv = uout1->Get_OutValue();
    while (t<=10) {
        t = sim1.Get_t();
        cnt++;
        sim1.Simulate_OneStep();
        outvalue = uout1->Get_OutValue();
        if (lv != outvalue) {  // 当前时刻的值与上个时刻不同时输出
            cout << t << ", " << cnt << ", " << outvalue << endl;
            lv = outvalue;
        }
    }
    return 0;
}
