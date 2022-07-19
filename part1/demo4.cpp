/*将文件中的数据加载到输入端口并直连到输出端口显示*/
#include <fstream>
#include <string>
#include <sstream>
#include "simucpp.hpp"
using namespace simucpp;
using namespace std;

vector<double> Read_data(const string filename)
{
    ifstream fp(filename);
    vector<double> data;
    string line;
    while(getline(fp, line))
        data.push_back(stod(line));
    return data;
}

int main()
{
    vector<double> data = Read_data("sinewave");
    Simulator sim1(20);
    MInput *input1 = new MInput(&sim1);
    MOutput *output1 = new MOutput(&sim1);

    input1->Set_Continuous(false);
    input1->Set_SampleTime(0.2);
    input1->Set_InputData(data);

    sim1.connect(input1, output1);

    sim1.Initialize();
    sim1.Simulate();
    sim1.Plot();
    return 0;
}
