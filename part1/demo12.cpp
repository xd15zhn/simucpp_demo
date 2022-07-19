/*定积分*/
#include <iostream>
#include "simucpp.hpp"
using namespace simucpp;
using namespace std;

int main()
{
    Simulator sim1(2);
    FMInput(min1, &sim1);
    FMIntegrator(mint1, &sim1);
    sim1.connect(min1, mint1);
    min1->Set_Function([](double t){return (t+1.0)*(t+1.0);});
    sim1.Set_t(1);
    sim1.Initialize();
    sim1.Simulate();
    cout.precision(12);
    cout << mint1->Get_OutValue() << endl;
    return 0;
}
