#include <cmath>
#include "eso.h"

int main()
{
    Simulator sim1;
    auto eso = new ESO(&sim1);
    auto tf1 = new TransferFcn(&sim1, vector<double>{1}, vector<double>{1, 2, 1});
    MACRO_MInput(in1, &sim1);
    MACRO_MOutput(outy, &sim1);
    MACRO_MOutput(outz1, &sim1);
    MACRO_MOutput(outz2, &sim1);
    MACRO_MOutput(outw, &sim1);

    in1->Set_Function([](double t){return 1.0;});
    eso->Set_SampleTime(0.1);
    sim1.connect(in1, tf1);
    sim1.connect(in1, eso, 0);
    sim1.connect(tf1, eso, 1);
    sim1.connect(tf1, outy);
    sim1.connect(eso, 0, outz1);
    sim1.connect(eso, 1, outz2);
    sim1.connect(eso, 2, outw);

    sim1.Initialize();
    sim1.Simulate();
    cout.precision(12);
    cout << outy->Get_OutValue() << endl;
    cout << outz1->Get_OutValue() << endl;
    cout << outz2->Get_OutValue() << endl;
    cout << outw->Get_OutValue() << endl;
    sim1.Plot();
    return 0;
}
