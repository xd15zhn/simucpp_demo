/*直流电机(封装成用户自定义模块)*/
#include <iostream>
#include "simucpp.hpp"
using namespace simucpp;
using namespace std;

class DCMotor: public PackModule
{
public:
    DCMotor() {};
    DCMotor(Simulator *sim){
        Initialize(sim);
    };
    virtual PUnitModule Get_InputPort(int n) const {
        if (n==0) return in1;
        if (n==1) return in2;
        return nullptr;
    };
    virtual PUnitModule Get_OutputPort(int n) const {
        if (n==0) return tr2->Get_OutputPort();
        if (n==1) return tr1->Get_OutputPort();
        return nullptr;
    };
    void Initialize(Simulator *sim){
        SUSum(sum1, sim);
        SUSum(sum2, sim);
        SUGain(in1, sim);
        SUGain(in2, sim);
        tr1 = new TransferFcn(sim, vector<double>{1}, vector<double>{L, R});
        tr2 = new TransferFcn(sim, vector<double>{1}, vector<double>{J, f});
        sim->connectU(in1, sum1);
        sim->connectU(sum1, tr1);
        sim->connectU(tr1, sum2);
        sum2->Set_InputGain(Cm);
        sim->connectU(sum2, tr2);
        sim->connectU(tr2, sum1);
        sum1->Set_InputGain(-Ce);
        sim->connectU(in2, sum2);
        sum2->Set_InputGain(-1);
    }
    double L=0.0189;  // 线圈电感
    double R=1.309;  // 线圈内阻
    double J=0.32;  // 转子和负载的转动惯量
    double f=0;  // 黏性摩擦系数
    double Cm=2.589;  // 转矩系数
    double Ce=2;  // 反电动势系数
private:
    USum *sum1, *sum2;
    TransferFcn *tr1, *tr2;
    UGain *in1, *in2;
};

int main()
{
    Simulator sim1(2);
    DCMotor *motor1 = new DCMotor(&sim1);
    DCMotor *motor2 = new DCMotor;
    FUInput(Voltage, &sim1);
    FUInput(Loadtorque, &sim1);
    FUOutput(Current1, &sim1);
    FUOutput(omega1, &sim1);
    FUOutput(Current2, &sim1);
    FUOutput(omega2, &sim1);

    Voltage->Set_Function([](double t){return 400.0;});
    Loadtorque->Set_Function([](double t){return t<1?0:100.0;});
    motor2->Ce = 0.1;
    motor2->Initialize(&sim1);

    sim1.connectU(Voltage, motor1, 0);
    sim1.connectU(Loadtorque, motor1, 1);
    sim1.connectU(motor1, 0, omega1);
    sim1.connectU(motor1, 1, Current1);

    sim1.connectU(Voltage, motor2, 0);
    sim1.connectU(Loadtorque, motor2, 1);
    sim1.connectU(motor2, 0, omega2);
    sim1.connectU(motor2, 1, Current2);

    sim1.Initialize();
    sim1.Simulate();
    cout.precision(12);
    // Current1->Set_EnableStore(false);
    // omega1->Set_EnableStore(false);
    Current2->Set_EnableStore(false);
    omega2->Set_EnableStore(false);
    cout << omega1->Get_OutValue() << endl;
    cout << Current1->Get_OutValue() << endl;
    sim1.Plot();
    return 0;
}
