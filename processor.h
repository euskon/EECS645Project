#ifndef PROCESSOR_H
#define PROCESSOR_H
#include <string>
#include <bitset>//used for int -> binary
using namespace std;
class Processor
{
private:
    //16KB, 32-byte cache line, 16KB/32-byte per cache line = 500 cache lines,
    //2^9 == 512
    string m_tagArr[512];
    char m_stateArr[512];
public:
    Processor();
    ~Processor();
    //gets the vector from traceParse and 'executes' each trace
    void run();

    //Helper functions to extract substring from binary
    string parseIndex(string strHex);
    string parseTag(string strHex);
    
    //Get
    string getTagAt(string index);
    char getStateAt(string index);

    //Set
    void setStateAt(string index, char newState);
    void setTagAt(string index, string newTag);

    //StateSpecific Functions for Transition and side-effects
    void invalid(char state, bool rw, string Tag);
    

};
#endif