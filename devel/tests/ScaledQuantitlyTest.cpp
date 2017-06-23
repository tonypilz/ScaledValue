#include "ScaledQuantitlyTest.h"

#include "../../../units/include/units.h"
#include "tools/SingleFile.h"


#include <ostream>
#include <iostream>
#include <ios>
using namespace unit;
using namespace singleFile::sv;

using SvMilli = ScaledValue<std::milli,double>;
using SvKilo = ScaledValue<std::kilo,double>;
using Sv1 = ScaledValue<std::ratio<1>,double>;

constexpr Quantity<u::newton,Sv1> s_newton {1.0};
constexpr Quantity<u::unitless,Sv1> s_unitLess{1.0};

constexpr   Quantity<u::unitless,Sv1> operator"" _n ( long double v )  {return Quantity<u::unitless,Sv1> {static_cast<double>(v)};}
constexpr   Quantity<u::unitless,SvKilo> operator"" _kilo ( long double v )  {return Quantity<u::unitless,SvKilo> {static_cast<double>(v)};}
constexpr   Quantity<u::unitless,SvMilli> operator"" _milli ( long double v )  {return Quantity<u::unitless,SvMilli> {static_cast<double>(v)};}


int run(int i)
{
    auto x = 2.0_kilo * s_newton;
    x+= Quantity<u::newton,Sv1>{i};
    auto b = Quantity<u::newton,Sv1>{x}; //rescale a to scale 1
    return b.magnitude().value();
}

ScaledQuantitlyTest::ScaledQuantitlyTest()
{
    run(7);

    auto a = 2.0_kilo * s_newton + 3.0_n * s_newton + 4.0_milli * s_newton; //combine different scales
    auto b = Quantity<u::newton,Sv1>{a}; //rescale a to scale 1

    std::cout.precision(8);
    std::cout << "a = "<<  a << "   b = " << b << std::endl; // "a = 2.003004*kiloN   b = 2003.004N"

}
