/*线性微分方程组*/
#include <iostream>
#include "simucpp.hpp"
using namespace std;
using namespace zhnmat;
using namespace simucpp;

int main()
{
    Simulator sim1(1);
    Mat A(3, 3, vecdble{-1, 1, 0, -4, 3, 0, 1, 0, 2});
    Mat initvalue(3, 1, 1);
    auto mY = new MStateSpace(&sim1, BusSize(3, 1), true, "mY");
    auto mA = new MGain(&sim1, A, true, "mA");
    auto dmx = new DeMux(&sim1, BusSize(3, 1));
    FUOutput(uout1, &sim1);
    FUOutput(uout2, &sim1);
    FUOutput(uout3, &sim1);

    sim1.connectM(mY, mA);
    sim1.connectM(mA, mY);
    sim1.connectM(mY, dmx);
    sim1.connectU(dmx, BusSize(0, 0), uout1);
    sim1.connectU(dmx, BusSize(1, 0), uout2);
    sim1.connectU(dmx, BusSize(2, 0), uout3);
    sim1.Set_SimStep(1/double(1<<10));
    mY->Set_InitialValue(initvalue);

    sim1.Initialize();
    sim1.Simulate();
    cout.precision(12);
    cout << uout1->Get_OutValue() << endl;
    sim1.Plot();
    return 0;
}
