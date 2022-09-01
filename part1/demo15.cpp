/*代数环*/
#include "simucpp.hpp"
using namespace simucpp;
using namespace std;

int main()
{
    Simulator sim1, sim2;
    FUInput(in1, &sim1);
    FUOutput(out1, &sim1);
    FUGain(gain1, &sim1);
    FUGain(gain2, &sim1);
    FUGain(gain3, &sim1);
    FUGain(gain4, &sim1);
    FUSum(sum1, &sim1);
    FUSum(sum2, &sim1);
    FUSum(sum3, &sim1);
    in1->Set_Function([](double t){return 1.0;});
    sim1.connectU(in1, gain1);  // 将该语句改为 sim1.connectU(sum1, gain1); 则引发代数环
    sim1.connectU(in1, gain2);
    sim1.connectU(gain1, gain3);
    sim1.connectU(gain2, gain4);
    sim1.connectU(gain1, sum2);
    sim1.connectU(gain2, sum1);
    sim1.connectU(gain3, sum1);
    sim1.connectU(gain4, sum2);
    sim1.connectU(sum1, sum3);
    sim1.connectU(sum2, sum3);
    sim1.connectU(sum3, out1);
    sim1.Initialize();

    FUInput(s2in1, &sim2);
    FUSum(s2sum1, &sim2);
    FUZOH(s2zoh1, &sim2);
    FUSum(s2sum2, &sim2);
    FUOutput(s2out1, &sim2);
    s2in1->Set_Function([](double t){return t;});
    sim2.connectU(s2in1, s2sum1);
    sim2.connectU(s2sum1, s2zoh1);
    sim2.connectU(s2zoh1, s2sum2);
    sim2.connectU(s2in1, s2sum1);  // 将该语句改为 sim2.connectU(s2sum2, s2sum1); 则引发代数环
    sim2.connectU(s2sum2, s2out1);
    sim2.Initialize();
    return 0;
}
