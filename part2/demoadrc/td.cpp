#include "td.h"

/**********************
离散系统最速控制综合函数
*@x1:二阶串联积分器的输出
*@x2:二阶串联积分器输出的微分
*@return:控制量输出
**********************/
inline double ADRC_fhan(double* param)
{
    double x1 = param[0];
    double x2 = param[1];
    double r  = param[2];
    double h  = param[3];
    double u;
    double y = x1 + h*x2;
    double absy = ABS(y);
    double d1 = 1/(h*h*r);
    double k = 0.5*(1+sqrt(1+8*d1*absy));
    k = SIGN(k-(int)k)+(int)k;
    if(absy*d1 <= 1)
        u = -(y + h*x2)*d1;
    else
        u = SIGN(y)*(1-0.5*k)-(x1+k*h*x2)/(k-1)*d1;
    u = r*LIMIT(u, -1, 1);
    return u;
}

TD::TD(Simulator *sim)
{
    in1 = new MConnector(sim);
    outx1 = new MConnector(sim);
    outx2 = new MConnector(sim);
    delayx1 = new DiscreteIntegrator(sim);
    delayx2 = new DiscreteIntegrator(sim);
    sum1 = new MSum(sim);
    fhan = new MFcnMISO(sim);
    constant = new MInput(sim);
    gainR = new MGain(sim);
    gainH = new MGain(sim);
    constant->Set_Function([](double t){return 1.0;});
    fhan->Set_Function(ADRC_fhan);
    gainR->Set_Gain(1);
    gainH->Set_Gain(1);
    sim->connect(in1, sum1);
    sum1->Set_InputGain(-1);
    sim->connect(sum1, fhan);
    sim->connect(fhan, delayx2);
    sim->connect(delayx2, delayx1);
    sim->connect(delayx1, sum1);
    sim->connect(delayx2, fhan);
    sim->connect(constant, gainR);
    sim->connect(constant, gainH);
    sim->connect(gainR, fhan);
    sim->connect(gainH, fhan);
    sim->connect(delayx1, outx1);
    sim->connect(delayx2, outx2);
}
void TD::Set_SampleTime(double T)
{
    delayx1->Set_SampleTime(T);
    delayx2->Set_SampleTime(T);
    gainH->Set_Gain(T);
}
void TD::Set_R(double R)
{
    gainR->Set_Gain(R);
}
PUnitModule TD::Get_InputPort(int n) const
{
    return n==0 ? in1 : nullptr;
}
PUnitModule TD::Get_OutputPort(int n) const
{
    if (n==0) return outx1;
    if (n==1) return outx2;
    return nullptr;
}
