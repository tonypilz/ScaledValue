#include "ScaledQuantitlyTest.h"
#include "TestMain.h"


#include <src/ScaledValue.h>
#include <src/ScaledValueOperations.h>
#include <src/ScaledValuePrinting.h>
#include <src/ScaledValueMath.h>

#include <sstream>
#include <ratio>
#include <iostream>
#include <cassert>
#include <complex>


namespace sv {
namespace tests {

using SV1 = ScaledValue<std::kilo>;
using SV2 = ScaledValue<std::deci>;

static_assert( SV1{5} * SV2{3} == SV1{1.5},"");
static_assert( SV1{5} / SV2{4} == SV1{12.5},"");

namespace T1
{
    //(4*5/6 + 30*8/9)*6/5 == 36
    //(4*5/6 - 30*8/9)*6/5 == 28
    using A = ScaledValue<std::ratio<5,6>>;
    using B = ScaledValue<std::ratio<8,9>>;
    static_assert(A{4}+B{30} == A{(4.0*5/6 + 30.0*8/9)*6/5},"");
    static_assert(A{4}-B{30} == A{(4.0*5/6 - 30.0*8/9)*6/5},"");
    static_assert(A{B{3}} == A{3.0*8/9*6/5},"");
}

namespace T2 {
    constexpr ScaledValue<std::ratio<2,5>,long long> a{13}; //5.2
    constexpr ScaledValue<std::ratio<3,7>,long long> b{11}; //4.71428571429
    constexpr ScaledValue<std::ratio<13,5>,long long> a_differentRepr{2};

    static_assert(a==a,"");


    static_assert(a==a_differentRepr,"");
    static_assert(a<=a_differentRepr,"");
    static_assert(a>=a_differentRepr,"");
    static_assert((a<a_differentRepr)==false,"");
    static_assert((a!=a_differentRepr)==false,"");

    static_assert(a!=b,"");
    static_assert(a>b,"");
    static_assert(a>=b,"");
    static_assert(b<a,"");
    static_assert(b<=a,"");
    static_assert((a<b)==false,"");
    static_assert((b>a)==false,"");
}

namespace T3 {
    constexpr ScaledValue<std::ratio<2,-5>,long long> a{13}; //-5.2
    constexpr ScaledValue<std::ratio<3,7>,long long> b{11}; //4.71428571429
    constexpr ScaledValue<std::ratio<13,5>,long long> a_differentRepr{-2};

    static_assert(a==a,"");

    static_assert(a==a_differentRepr,"");
    static_assert(a<=a_differentRepr,"");
    static_assert(a>=a_differentRepr,"");
    static_assert((a<a_differentRepr)==false,"");
    static_assert((a!=a_differentRepr)==false,"");

    static_assert(a!=b,"");
    static_assert(a<b,"");
    static_assert(a<=b,"");
    static_assert(b>a,"");
    static_assert(b>=a,"");
    static_assert((a>b)==false,"");
    static_assert((b<a)==false,"");
}

namespace T4 {
    constexpr ScaledValue<std::ratio<2,-5>,long long> a{13}; //-5.2
    constexpr ScaledValue<std::ratio<6,-7>,long long> b{11}; //-4.71428571429
    constexpr ScaledValue<std::ratio<13,5>,long long> a_differentRepr{-2};

    static_assert(a==a,"");


    static_assert(a==a_differentRepr,"");
    static_assert(a<=a_differentRepr,"");
    static_assert(a>=a_differentRepr,"");
    static_assert((a<a_differentRepr)==false,"");
    static_assert((a!=a_differentRepr)==false,"");

    static_assert(a!=b,"");
    static_assert(a>b,"");
    static_assert(a>=b,"");
    static_assert(b<a,"");
    static_assert(b<=a,"");
    static_assert((a<b)==false,"");
    static_assert((b>a)==false,"");
}

namespace T1
{
    using A = ScaledValue<std::ratio<5,6>>;
    using B = ScaledValue<std::ratio<8,9>>;
    static_assert(A{4}+B{30} == A{(4.0*5/6 + 30.0*8/9)*6/5},"");
    static_assert(A{4}-B{30} == A{(4.0*5/6 - 30.0*8/9)*6/5},"");
}

namespace T5
{
    using A = ScaledValue<std::ratio<5,6>>;
    using B = ScaledValue<std::ratio<-8,9>>;
    using C = ScaledValue<std::ratio< 8,9>>;

    static_assert(math::abs(A{-2})==A{2},"");
    static_assert(math::abs(A{2})==A{2},"");

    static_assert(math::abs(B{-2})==C{2},"");
    static_assert(math::abs(B{ 2})==C{2},"");

}
void print_test(){

    {
        std::ostringstream s;
        s << ScaledValue<std::ratio<2,-5>>{13};
        if (s.str()!="13*(-2/5)") assert(false);
    }
    {
        std::ostringstream s;
        s << ScaledValue<std::ratio<2>>{13};
        if (s.str()!="13*2") assert(false);
    }
    {
        std::ostringstream s;
        s << ScaledValue<std::ratio<-2>>{13};
        if (s.str()!="13*-2") assert(false);
    }
    {
        std::ostringstream s;
        s << ScaledValue<std::milli>{13};
        if (s.str()!="13*milli") assert(false);
    }
    {
        std::ostringstream s;
        s << ScaledValue<std::deca>{13};
        if (s.str()!="13*deca") assert(false);
    }

}


void complex_test()
{
    using C = std::complex<double>;

    {
        const bool b = (ScaledValue<std::ratio<5,6>,C>{C{1,2}} +
                        ScaledValue<std::ratio<7,8>,double>{5}) ==
                ScaledValue<std::ratio<5,6>,C>{C{(1.0*5/6+5.0*7/8)*6.0/5,
                                                 (2.0*5/6+0.0*7/8)*6.0/5}};

        assert(b);
    }
}

void math_test()
{
     using A = ScaledValue<std::ratio<10,2>>;

    {
        const bool b = (math::sqrt(A{5}) == A{1});
        assert(b);
    }

    {
        const bool b = (math::pow(A{5},3.0) == A{5}*A{5}*A{5});
        assert(b);
    }
}
TestMain::TestMain()
{
    print_test();
    complex_test();

    //std::cout<<(  ScaledValue<std::milli>{13}) << "\n";

    ScaledQuantitlyTest{};
}

}
}
