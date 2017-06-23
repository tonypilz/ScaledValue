// Example program

#include "tests/TestMain.h"
#include "tools/SingleFileTester.h"
#include <tools/SingleFileGenerator.h>
#include <iostream>

int main()
{
    sv::tests::TestMain{};
    SingleFileTester{};

    std::cout<<__FILE__<<" finished\n";

    return 0;
}

