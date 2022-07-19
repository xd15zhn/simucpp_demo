/*代数环*/
#include "simucpp.hpp"
using namespace simucpp;
using namespace std;

int main()
{
    Simulator sim1, sim2;
    MInput *in1 = new MInput(&sim1);
    MOutput *out1 = new MOutput(&sim1);
    MGain *gain1 = new MGain(&sim1);
    MGain *gain2 = new MGain(&sim1);
    MGain *gain3 = new MGain(&sim1);
    MGain *gain4 = new MGain(&sim1);
    MSum *sum1 = new MSum(&sim1);
    MSum *sum2 = new MSum(&sim1);
    MSum *sum3 = new MSum(&sim1);
    in1->Set_Function([](double t){return 1.0;});
    sim1.connect(in1, gain1);  // 将该语句改为 sim1.connect(sum1, gain1); 则引发代数环
    sim1.connect(in1, gain2);
    sim1.connect(gain1, gain3);
    sim1.connect(gain2, gain4);
    sim1.connect(gain1, sum2);
    sim1.connect(gain2, sum1);
    sim1.connect(gain3, sum1);
    sim1.connect(gain4, sum2);
    sim1.connect(sum1, sum3);
    sim1.connect(sum2, sum3);
    sim1.connect(sum3, out1);
    sim1.Initialize();

    MInput *s2in1 = new MInput(&sim2);
    MSum *s2sum1 = new MSum(&sim2);
    MZOH *s2zoh1 = new MZOH(&sim2);
    MSum *s2sum2 = new MSum(&sim2);
    MOutput *s2out1 = new MOutput(&sim2);
    s2in1->Set_Function([](double t){return t;});
    sim2.connect(s2in1, s2sum1);
    sim2.connect(s2sum1, s2zoh1);
    sim2.connect(s2zoh1, s2sum2);
    sim2.connect(s2in1, s2sum1);  // 将该语句改为 sim1.connect(s2sum2, s2sum1); 则引发代数环
    sim2.connect(s2sum2, s2out1);
    sim2.Initialize();
    return 0;
}
