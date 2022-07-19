/*单摆*/
#include <cmath>
#include "simucpp.hpp"

int main()
{
    using namespace simucpp;
    Simulator sim1;
    MIntegrator *integrator1 = new MIntegrator(&sim1);
    MIntegrator *integrator2 = new MIntegrator(&sim1);
    MSum *sum1 = new MSum(&sim1);
    MFcn *fcn1 = new MFcn(&sim1);
    MOutput *output1 = new MOutput(&sim1);

    constexpr double k=1,m=1,l=1,g=9.8;
    integrator1->Set_InitialValue(1);
    fcn1->Set_Function([](double u){return -g/l*sin(u);});

    sim1.connect(integrator1, integrator2);
    sim1.connect(integrator2, output1);
    sim1.connect(integrator2, fcn1);
    sim1.connect(fcn1, sum1);
    sim1.connect(integrator1, sum1);
    sum1->Set_InputGain(-k/m);
    sim1.connect(sum1, integrator1);

    sim1.Initialize();
    sim1.Simulate();
    sim1.Plot();
    return 0;
}
