#include "processor.h"
Processor::Processor()
{
    for(int i = 0; i < 512; i++)
    {
        m_tagArr[i] = -1;
        m_stateArr[i] = 'I';
    }
}
Processor::~Processor(){}
void Processor::run(int proc, bool rw, string strHex)
{
    //activated processors' decision branch based on 
    //current state of cache line at supplied index
    string index = parseIndex(strHex);
    string tag = parseTag(strHex);
    char state = getStateAt(index);
    switch (state)
    {
    case 'I':
        //I dont have data, look elsewhere
        invalid(rw, tag, index);
        break;
    case 'E':
        //I am the only one with the data
        exclusive(rw, tag, index);
        break;
    case 'M':
        //I have modified the data must 
        modified(rw, tag, index);
        break;
    case 'S':
        shared(rw, tag, index);
        break;
    case 'O':
        owner(rw, tag, index);
        break;
    default:
        break;
    }
}
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
void Processor::setStateAt(string index, char newState)
{
    m_stateArr[stoi(index,nullptr,2)] = newState;
}
void Processor::setTagAt(string index, string newTag)
{
    m_tagArr[stoi(index,nullptr,2)] = newTag;
}
void Processor::setProcessors(Processor& a, Processor& b, Processor& c)
{
    p_A = &a;
    p_B = &b;
    p_C = &c;
}
void Processor::invalid(bool rw, string tag, string index)
{
    //read
    if(rw == false)
    {
        if(p_A->busRead(tag, index) ||
           p_B->busRead(tag, index) ||
           p_C->busRead(tag, index)) 
        {
            //update tag in my own cache
            setTagAt(index, tag);//..(,getTagAt(index))
            //Data in a shared state now
            setStateAt(index, 'S');
        }
        else
        {
            //load from mem(nobody else has it)
            setTagAt(index, tag);
            //Exclusive owner of data now
            setStateAt(index, 'E');
        }        
    }
    //write
    else if(rw == true)
    {
        p_A->busReadX(tag, index);
        p_B->busReadX(tag, index);
        p_C->busReadX(tag, index);
        //write data to cache tag line
        setTagAt(index, tag);
        //Modified state dirty cache line
        setStateAt(index, 'M');
    }
}
void Processor::exclusive(bool rw, string tag, string index)
{   //read
    if(rw == false)
    {
        //return to exclusive state
    }
    else if(rw == true)
    {
        //change to modified state
        setTagAt(index, tag);
        setStateAt(index, 'E');
    }
}
void Processor::modified(bool rw, string tag, string index)
{
    //read
    if(rw == false)
    {
        //clean as it should be
        if(getTagAt(index) == tag)
        {
            //return to modified state
        }
    }
    //write
    else if(rw == true)
    {
        //clean
        if(getTagAt(index) == tag)
        {
            //return to modified state
        }
        //dirty/miss
        else
        {
            //dirty writeback
            //return to modified state
            setTagAt(index, tag);
        }
        
    }
}
void Processor::shared(bool rw, string tag, string index)
{
    //read
    if(rw == false)
    {
        //clean
        if(getTagAt(index) == tag)
        {
            //return to shared state
        }
        //dirty find it in the owner and read from there
    }
    //write
    else if(rw == true)
    {
        p_A->busUpgrade(tag, index);
        p_B->busUpgrade(tag, index);
        p_C->busUpgrade(tag, index);
        setTagAt(index, tag);
        setStateAt(index, 'M');
    }

}
void Processor::owner(bool rw, string tag, string index)
{
    //read
    if(rw == false)
    {
        
    }
    //write
    else if(rw == true)
    {
        p_A->busUpgrade(tag, index);
        p_B->busUpgrade(tag, index);
        p_C->busUpgrade(tag, index);
        setTagAt(index, tag);
        setStateAt(index, 'M');
    }
}

bool Processor::busRead(string tag, string index)
{
    //cache hit return true
     if(getTagAt(index) == tag)
    {
        char state = getStateAt(index);
        if(state == 'E')
        {
            //flush send this proc data back "update tag"
            setStateAt(index, 'S');
        }
        else if(state == 'M')
        {
            //flush send this proc data back "update tag"
            setStateAt(index, 'O');
        }
        else if(state == 'S')
        {
            //setStateAt(index, 'S');            
        }
        else if(state == 'O')
        {
            //flush send this proc data back "update tag"
            //setStateAt(index, 'O')            
        }
        return(true);
    }
    //I dont have it might have to get it from memory
    return(false);
}
bool Processor::busReadX(string tag, string index)
{
    if(getTagAt(index) == tag)
    {
        char state = getStateAt(index);
        if(state == 'E'){
            //flush $2$
            //setTagAt(index, tag);
            setStateAt(index, 'I');
        }
        else if(state == 'M'){
           //Dirty Writeback
           dirtyWriteBack++;
           //flush $2$
           //setTagAt(index, tag);
            setStateAt(index, 'I');
        }
        else if(state == 'S'){
            //setTagAt(index, tag);
            setStateAt(index, 'I');
        }
        else if(state == 'O'){
            //Dirty Writeback
            dirtyWriteBack++;
            //flush $2$
            setStateAt(index, 'I');
        }
    }    
}
bool Processor::busUpgrade(string tag, string index)
{
    if(getTagAt(index) == tag)
    {
        char state = getStateAt(index);
        if(state == 'S'){
            //Invalidation++
            setStateAt(index, 'I');
        }
        else if(state == 'O'){
            //Invalidation++
            setStateAt(index, 'I');
        }
    }
}
void Processor::printResults()
{
    cout << "Dirty Writebacks: " << dirtyWriteBack << '\n';
}