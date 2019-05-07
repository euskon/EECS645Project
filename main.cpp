#include "processor.h"
#include "traceParse.h"
int main(int argc, char* argv[])
{
    if(argc > 0)
    {
        traceParse exec;
        exec.printTraces();
    }
}