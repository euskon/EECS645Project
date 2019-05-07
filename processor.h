#ifndef PROCESSOR_H
#define PROCESSOR_H
#include <string>
using namespace std;
class Processor
{
private:
    int m_numLines;
    std::string* m_tagArr = nullptr;
    char* m_stateArr = nullptr;
public:
    Processor();
    ~Processor();
    bool changeState(char newState);
    int parseToHex(string input);
    int parseIndex(int input);
    int parseTag(int input);
    int getTagAt(int index);
    

};
#endif