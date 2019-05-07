#ifndef TRACE_PARSE_H
#define TRACE_PARSE_H
#include <string>
#include <iostream>
#include <bitset>//used for int -> binary
#include <fstream>//used for reading from file
#include <algorithm>//sort
#include <vector>
#include <tuple>
using namespace std;
class traceParse
{
private:
    vector<tuple<int,int,bool,string>> traces;
    
public:
    traceParse();
    ~traceParse(); 
    void printTraces();
    bool sortByCycles(const tuple<int,int,bool,string> a,
                                  const tuple<int,int,bool,string> b);
    
};
#endif