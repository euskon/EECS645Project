#ifndef PROCESSOR_H
#define PROCESSOR_H
#include <string>
#include <iostream>
#include <bitset>//used for int -> binary
using namespace std;
class Processor
{
private:
    //16KB, 32-byte cache line, 16KB/32-byte per cache line = 500 cache lines,
    //2^9 == 512
    string m_tagArr[512];
    char m_stateArr[512];
    Processor* p_A = nullptr;
    Processor* p_B = nullptr;
    Processor* p_C = nullptr;
    int dirtyWriteBack, invalidation, cash2cash, m, o, e, s ,i;
public:
    Processor();
    ~Processor();
    //executes each trace
    void run(int proc, bool rw, string strHex);

    //Helper functions to extract substring from binary
    string parseIndex(string strHex);
    string parseTag(string strHex);
    
    //Get
    string getTagAt(string index);
    char getStateAt(string index);

    //Set
    void setStateAt(string index, char newState);
    void setTagAt(string index, string newTag);
    void setProcessors(Processor& a, Processor& b, Processor& c);

    //StateSpecific Functions for Transition and side-effects
    void invalid(bool rw, string tag, string index);
    void exclusive(bool rw, string tag, string index);
    void modified(bool rw, string tag, string index);
    void shared(bool rw, string tag, string index);
    void owner(bool rw, string tag, string index);
    /*snoop other processors for matching tag 
      at given index. Returns true when another processor
      has the requested data*/
    bool busRead(string tag, string index);
    bool busReadX(string tag, string index);
    bool busUpgrade(string tag, string index);
    
    void printResults();

};
#endif

/*general pseudo
decide read vs write
check <own/other> cache line for data match
activate signal function based on current state and input command





*/