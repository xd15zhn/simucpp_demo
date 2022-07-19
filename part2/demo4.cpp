/*PID控制器*/
#include "simucpp.hpp"
using namespace simucpp;
using namespace std;

class PID_Controller: public PackModule
{
public:
    PID_Controller() {};
    PID_Controller(Simulator *sim, double Kp=1, double Ki=0, double Kd=0, double N=100)
        :_Kp(Kp), _Ki(Ki), _Kd(Kd), _N(N) {
        Initialize(sim);
    };
    virtual PUnitModule Get_InputPort(int n) const {
        if (n==0) return mdin1;
        return nullptr;
    };
    virtual PUnitModule Get_OutputPort(int n) const {
        if (n==0) return mdout1;
        return nullptr;
    };
    void Initialize(Simulator *sim){
        mdintegral = new MIntegrator(sim, "mdintegral");
        mddifferential = new TransferFcn(sim, vector<double>{1, 0}, vector<double>{1, _N}, "mddifferential");
        mdin1 = new MConnector(sim, "mdin1");
        mdout1 = new MSum(sim, "mdout1");
        sim->connect(mdin1, mdintegral);
        sim->connect(mdin1, mddifferential);
        sim->connect(mdin1, mdout1);
        sim->connect(mdintegral, mdout1);
        sim->connect(mddifferential, mdout1);
        mdout1->Set_InputGain(_Kp, 0);
        mdout1->Set_InputGain(_Ki, 1);
        mdout1->Set_InputGain(_Kd, 2);
    }
    double _Kp=1, _Ki=0, _Kd=0, _N=100;
private:
    MIntegrator *mdintegral;
    TransferFcn *mddifferential;
    MConnector *mdin1;
    MSum *mdout1;
};

int main()
{
    Simulator sim1(10);
    auto *mdclose = new TransferFcn(&sim1, vector<double>{1}, vector<double>{1, 1, 1});  // 闭环传函
    auto *mdpid = new PID_Controller(&sim1, 1, 0, 9, 1);  // PID控制器
    auto* mdGs = new TransferFcn(&sim1, vector<double>{1}, vector<double>{10, 1, 0});  // 被控对象
    FMInput(mdu, &sim1);
    FMSum(mdsum, &sim1);
    FMOutput(mdout1, &sim1);
    FMOutput(mdout2, &sim1);

    sim1.Set_SimStep(1/double(1<<10));
    sim1.connect(mdu, mdclose);
    sim1.connect(mdu, mdsum);
    sim1.connect(mdsum, mdpid);
    sim1.connect(mdpid, mdGs);
    sim1.connect(mdGs, mdsum);
    mdsum->Set_InputGain(-1);
    sim1.connect(mdGs, mdout1);
    sim1.connect(mdclose, mdout2);

    sim1.Initialize();
    sim1.Simulate();
    cout.precision(12);
    cout << mdout1->Get_OutValue() << endl;
    cout << mdout2->Get_OutValue() << endl;
    return 0;
}
