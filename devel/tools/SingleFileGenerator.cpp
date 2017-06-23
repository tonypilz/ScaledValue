#include "SingleFileGenerator.h"

//1. enable defines
//2. recompile with #QMAKE_CXXFLAGS += -E
//3. open SingleFileGenerator.o with texteditor
//4. remove "#.+" (regex)
//5. replace "\r\n +\r\n" -> "\r\n\r\n" (regex)
//6. remove "\}(\r\n)+namespace sv \{\r\n" (regex)
//7. copy the unit-namespace to SingleFile.h
//8. add includes
//9. beautify everything except milli-block and everything starting at namespace u

//#define _GLIBCXX_IOSFWD 1
//#define _GLIBCXX_OSTREAM 1
//#define _GLIBCXX_RATIO 1
//#define _GLIBCXX_CTGMATH 1
//#define _GLIBCXX_TYPE_TRAITS 1
//#define _GLIBCXX_IOSTREAM 1
//#define _GLIBCXX_SSTREAM 1
//#define _GLIBCXX_STRING	1
//#define _GLIBCXX_ISTREAM 1


////all

#include <src/ScaledValue.h>
#include <src/ScaledValueMath.h>
#include <src/ScaledValueOperations.h>
#include <src/ScaledValuePrinting.h>



SingleFileGenerator::SingleFileGenerator()
{

}
