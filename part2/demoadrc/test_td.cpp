#include <cmath>
#include "td.h"
using namespace simucpp;
using namespace std;

int main()
{
    Simulator sim1;
    TD *td = new TD(&sim1);
    MInput *in1 = new MInput(&sim1);
    MOutput *out1 = new MOutput(&sim1);
    MOutput *out2 = new MOutput(&sim1);

    in1->Set_Function([](double t){return 1.0;});
    td->Set_SampleTime(0.5);
    td->Set_R(0.1);
   sim1.connect(in1, td);
    sim1.connect(td, 0, out1);
    sim1.connect(td, 1, out2);
    sim1.Initialize();
    sim1.Simulate();
    sim1.Plot();
    cout << out1->Get_OutValue() << endl;
    cout << out2->Get_OutValue() << endl;
    return 0;
}
