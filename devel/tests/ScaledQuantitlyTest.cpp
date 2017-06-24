#include "ScaledQuantitlyTest.h"



//#include "../../../units/devel/src/unit/unitHelper.h"
//#include "../../../units/devel/src/quantity/Quantity.h"
//#include "../../../units/devel/src/quantity/quantityDefinitionsSI.h"
//#include "../../../units/devel/src/quantity/quantityMath.h"

#include <src/ScaledValue.h>
#include <src/ScaledValueMath.h>
#include <src/ScaledValueOperations.h>
#include <src/ScaledValuePrinting.h>
#include "../../../units/include/units.h"
using namespace unit;
using namespace sv;

using SvMilli = ScaledValue<std::milli,double>;
using SvKilo = ScaledValue<std::kilo,double>;
using Sv1 = ScaledValue<std::ratio<1>,double>;

constexpr Quantity<u::newton,Sv1> s_newton {1.0};
constexpr Quantity<u::unitless,Sv1> s_unitLess{1.0};

//constexpr   Quantity<u::unitless,Sv1> operator"" _n ( long double v )  {return Quantity<u::unitless,Sv1> {static_cast<double>(v)};}
constexpr   Quantity<u::unitless,SvKilo> operator"" _kilo ( long double v )  {return Quantity<u::unitless,SvKilo> {static_cast<double>(v)};}
constexpr   Quantity<u::unitless,SvMilli> operator"" _milli ( long double v )  {return Quantity<u::unitless,SvMilli> {static_cast<double>(v)};}


//int run(int i)
//{
//    auto x = 2.0_kilo * s_newton;
//    x+= Quantity<u::newton,Sv1>{i};
//    auto b = Quantity<u::newton,Sv1>{x}; //rescale a to scale 1
//    return b.magnitude().value();
//}


ScaledQuantitlyTest::ScaledQuantitlyTest()
{
    //run(7);


    //define unit values on different scales
    auto a = 2.0_kilo * s_newton;
    auto b = 500.0_milli * s_newton;

    //combination
    auto c = a + b;
    auto d = a * b;

    //math
    auto e = sqrt(d);

    //conversion
    auto f = Quantity<u::newton,Sv1>{b};

    std::cout << a << std::endl; // prints "2*kiloN"
    std::cout << b << std::endl; // prints "500*milliN"
    std::cout << c << std::endl; // prints "2.0005*kiloN"
    std::cout << d << std::endl; // prints "1*kilom^2kg^2s^-4" which is 1*kilo N^2
    std::cout << e << std::endl; // prints "0.0316228*kiloN"
    std::cout << f << std::endl; // prints "0.5N"
}
