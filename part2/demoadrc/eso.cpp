#include "eso.h"

ESO::ESO(Simulator *sim, string name)
{
    inu = new MConnector(sim, name+"_inu");
    iny = new MConnector(sim, name+"_iny");
    outz1 = new MConnector(sim, name+"_outz1");
    outz2 = new MConnector(sim, name+"_outz2");
    outw = new MConnector(sim, name+"_outw");
    disintz1 = new DiscreteIntegrator(sim, name+"_disintz1");
    disintz2 = new DiscreteIntegrator(sim, name+"_disintz2");
    disintw = new DiscreteIntegrator(sim, name+"_disintw");
    gainL1 = new MGain(sim, name+"_gainL1");
    gainL2 = new MGain(sim, name+"_gainL2");
    gainL3 = new MGain(sim, name+"_gainL3");
    gainb = new MGain(sim, name+"_gainb");
    sumz1 = new MSum(sim, name+"_sumz1");
    sumz2 = new MSum(sim, name+"_sumz2");
    sumdw = new MSum(sim, name+"_sumdw");
    Set_BandWidth();
    sim->connect(inu, gainb);
    sim->connect(iny, sumdw);
    sim->connect(gainb, sumz2);
    sim->connect(sumdw, gainL1);
    sim->connect(sumdw, gainL2);
    sim->connect(sumdw, gainL3);
    sim->connect(gainL3, disintw);
    sim->connect(disintw, sumz2);
    sim->connect(gainL2, sumz2);
    sim->connect(sumz2, disintz2);
    sim->connect(disintz2, sumz1);
    sim->connect(gainL1, sumz1);
    sim->connect(sumz1, disintz1);
    sim->connect(disintz1, sumdw);
    sumdw->Set_InputGain(-1);
    sim->connect(disintw, outw);
    sim->connect(disintz1, outz1);
    sim->connect(disintz2, outz2);
}
void ESO::Set_SampleTime(double T)
{
    disintz1->Set_SampleTime(T);
    disintz2->Set_SampleTime(T);
    disintw->Set_SampleTime(T);
}
void ESO::Set_BandWidth(double w)
{
    gainL1->Set_Gain(3*w);
    gainL2->Set_Gain(3*w*w);
    gainL3->Set_Gain(w*w*w);
}
PUnitModule ESO::Get_InputPort(int n) const
{
    if (n==0) return inu;
    if (n==1) return iny;
    return nullptr;
}
PUnitModule ESO::Get_OutputPort(int n) const
{
    if (n==0) return outz1;
    if (n==1) return outz2;
    if (n==2) return outw;
    return nullptr;
}
