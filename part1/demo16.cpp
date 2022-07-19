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
    auto mtf2 = new StateSpace(&sim1, A, B, C, D, SIMUCPP_CONTINUOUS, "tf2");
    FMConstant(mu1, &sim1);
    FMOutput(mout1, &sim1);
    FMOutput(mout2, &sim1);
    sim1.connect(mu1, mtf1);
    sim1.connect(mu1, mtf2);
    sim1.connect(mtf1, mout1);
    sim1.connect(mtf2, mout2);
    sim1.Initialize();
    sim1.Simulate();
    sim1.Plot();
    return 0;
}
