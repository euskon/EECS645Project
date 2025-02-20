#ifndef TRACE_PARSE_H
#define TRACE_PARSE_H
#include <string>
#include <iostream>
#include <fstream>//used for reading from file
#include <algorithm>//sort
#include <vector>
#include <tuple>
using namespace std;
class traceParse
{
private:
    /*vector containg tuples with traces to be executed
    **tuple type: (int, int, bool, string)
    **tuple desc: (proc, cyc, r/w, hex)
    */
    vector<tuple<int,int,bool,string>> traces;
    
public:
    /*constructor parses the 4 given trace files 
    **populates vector of tuples, then sorts the
    **tuples based on proc, then by cyc.
    */
    traceParse();
    /*
    **nothing for now
    */
    ~traceParse();

    /*prints our all tuples in vector
    **loop is bounded by vect.size()
    */
    void printTraces(); 
    tuple<int,int,bool,string> getTraceAt(int index);
    int getTraceVectorSize();
};
//helper func: sorting using tuples as params use w/ sort()
bool sortByCycles(const tuple<int,int,bool,string>& next,
                  const tuple<int,int,bool,string>& curr);
#endif