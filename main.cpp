#include "processor.h"
#include "traceParse.h"
int main(int argc, char* argv[])
{
    if(argc > 0)
    {
        //parse the traces
        traceParse exec;
        exec.printTraces();
        //init processors
        Processor p_0;
        Processor p_1;
        Processor p_2;
        Processor p_3;
        p_0.setProcessors(p_1, p_2, p_3);
        p_1.setProcessors(p_0, p_2, p_3);
        p_2.setProcessors(p_0, p_1, p_3);
        p_3.setProcessors(p_0, p_1, p_2);
        //executing p_0 -> p_3 in that order 
        //ensures identical tag&index occur 
        //in p_0 first and p_3 last
        for(int i = 0; i < exec.getTraceVectorSize(); i++)
        {
            //get trace
            tuple<int,int,bool,string> curr = exec.getTraceAt(i);
            //select base processor the instruction involves
            //p_0
            if(get<0>(curr) == 0){
                p_0.run(get<0>(curr), get<2>(curr), get<3>(curr));
            }
            //p_1
            else if(get<0>(curr) == 1){
                p_1.run(get<0>(curr), get<2>(curr), get<3>(curr));
            }
            //p_2
            else if(get<0>(curr) == 2){
                p_2.run(get<0>(curr), get<2>(curr), get<3>(curr));
            }
            //p_3
            else if(get<0>(curr) == 3){
                p_3.run(get<0>(curr), get<2>(curr), get<3>(curr));
            }
        }
    }
}
