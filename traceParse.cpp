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
    sort(traces.begin(), traces.end());
    sort(traces.begin(), traces.end(), sortByCycles);
    
}
traceParse::~traceParse()
{

}
void traceParse::printTraces()
{
    for(unsigned int i = 0; i<traces.size(); i++)
    {
        cout << "v[" << i << "] = " << get<0>(traces[i]) << " " << get<1>(traces[i]) << " " << get<3>(traces[i]) << '\n';
    }
}
tuple<int,int,bool,string> traceParse::getTraceAt(int index)
{
    return (traces[index]);
}
int traceParse::getTraceVectorSize()
{
    return(traces.size());
}
// std::string str = "0x195d5910";
// int val = std::stoi (str,nullptr,0);
// std::bitset<32> hexDig (val);
bool sortByCycles(const tuple<int,int,bool,string>& next,
                  const tuple<int,int,bool,string>& curr)
{
    return(get<1>(next) < get<1>(curr));
}
