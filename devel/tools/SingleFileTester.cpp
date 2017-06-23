#include "SingleFileTester.h"

#include "SingleFile.h"



int run_si(int ) {


    std::cout<<singleFile::sv::ScaledValue<std::ratio<2,-5>>{13}<<"\n";
    return 0;
}



SingleFileTester::SingleFileTester()
{

    run_si(4);

    std::cout<<__FILE__<<"\n";


}
