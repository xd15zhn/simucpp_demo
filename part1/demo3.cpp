/*Mathieu方程*/
#include <iostream>
#include <cmath>
#include "simucpp.hpp"

constexpr double pax = 0.236;
constexpr double pqx = 0.706;

double Input_Function(double t)
{
    return (pqx + pqx) * cos(t + t) - pax;
}

int main()
{
    using namespace simucpp;
    using namespace std;
    Simulator sim1(15);
    MIntegrator *integrator1 = new MIntegrator(&sim1);
    MIntegrator *integrator2 = new MIntegrator(&sim1);
    MProduct *product1 = new MProduct(&sim1);
    MInput *input1 = new MInput(&sim1);
    MOutput *output1 = new MOutput(&sim1);

    integrator2->Set_InitialValue(1);
    input1->Set_Function(Input_Function);

    sim1.connect(input1, product1);
    sim1.connect(product1, integrator1);
    sim1.connect(integrator1, integrator2);
    sim1.connect(integrator2, output1);
    sim1.connect(integrator2, product1);

    sim1.Initialize();
    sim1.Simulate();
    cout.precision(12);
    cout << output1->Get_OutValue() << endl;
    sim1.Plot();
    return 0;
}
