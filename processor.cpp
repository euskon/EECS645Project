#include "processor.h"
Processor::Processor(){}
Processor::~Processor(){}
string Processor::parseIndex(string strHex)
{
    int val = std::stoi (strHex,nullptr,0);
    std::bitset<32> bNum (val);
    strHex = bNum.to_string();
    return(strHex.substr(5, 9));
}
string Processor::parseTag(string strHex)
{
    int val = std::stoi (strHex,nullptr,0);
    std::bitset<32> bNum (val);
    strHex = bNum.to_string();
    return(strHex.substr(13, 31));
}
string Processor::getTagAt(string index)
{
    return(m_tagArr[stoi(index,nullptr,2)]);
}
char Processor::getStateAt(string index)
{
    return(m_stateArr[stoi(index,nullptr,2)]);
}
void Processor::setStateAt(string index, char newState){
    m_stateArr[stoi(index,nullptr,2)] = newState;
}
void Processor::setTagAt(string index, string newTag){
    m_tagArr[stoi(index,nullptr,2)] = newTag;
}