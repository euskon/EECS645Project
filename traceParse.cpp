#include "traceParse.h"
using namespace std;
traceParse::traceParse()
{    
    int cycle;
    bool rw;
    string hex;
    ifstream inFile("p0.tr");
    while(inFile >> cycle >> rw >> hex)
    {
        traces.push_back(make_tuple(0, cycle, rw, hex));
    }
    inFile.close();
    inFile.open("p1.tr");
    while(inFile >> cycle >> rw >> hex)
    {
        traces.push_back(make_tuple(1, cycle, rw, hex));
    }
    inFile.close();
    inFile.open("p2.tr");
    while(inFile >> cycle >> rw >> hex)
    {
        traces.push_back(make_tuple(2, cycle, rw, hex));
    }
    inFile.close();
    inFile.open("p3.tr");
    while(inFile >> cycle >> rw >> hex)
    {
        traces.push_back(make_tuple(3, cycle, rw, hex));
    }
    inFile.close();
    
}
traceParse::~traceParse()
{

}
void traceParse::printTraces()
{
    for(int i = 0; i<traces.size(); i++)
    {
        cout << "v[" << i << "] = " << get<1>(traces[i]) << " " << get<3>(traces[i]) << '\n';
    }
}
// std::string str = "0x195d5910";
// int val = std::stoi (str,nullptr,0);
//   std::bitset<32> hexDig (val);
bool traceParse::sortByCycles(const tuple<int,int,bool,string> a,
                              const tuple<int,int,bool,string> b)
{
    return(get<1>(a), get<1>(b));
}