/*状态空间*/
#include "simucpp.hpp"
using namespace simucpp;
using namespace zhnmat;
using namespace std;
int main()
{
    Mat A(2, 2, vecdble{-5, -1, 3, -1});
    Mat B(2, 1, vecdble{2, 5});
    Mat C(1, 2, vecdble{1, 2});
    Mat D(1, 1, vecdble{4});
    Simulator sim1;
    auto mtf1 = new TransferFcn(&sim1, vecdble{4, 36, 91}, vecdble{1, 6, 8}, "tf1");
    auto mtf2 = new StateTransFcn(&sim1, A, B, C, D, SIMUCPP_CONTINUOUS, "tf2");
    auto mx = new Mux(&sim1, BusSize(1, 1));
    auto dmx = new DeMux(&sim1, BusSize(1, 1));
    FUConstant(mu1, &sim1);
    FUOutput(mout1, &sim1);
    FUOutput(mout2, &sim1);
    sim1.connectU(mu1, mtf1);
    sim1.connectU(mtf1, mout1);
    sim1.connectU(mu1, mx);
    sim1.connectM(mx, mtf2);
    sim1.connectM(mtf2, dmx);
    sim1.connectU(dmx, mout2);
    sim1.Initialize();
    sim1.Simulate();
    sim1.Plot();
    return 0;
}
