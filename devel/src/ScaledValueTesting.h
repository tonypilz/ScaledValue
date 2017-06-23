#pragma once

#include <arithmeticScaling/ScaledValue.h>
#include <arithmeticScaling/ScaledValuePrinting.h>
#include <arithmeticScaling/ScaledValueOperations.h>


int foo()
{

    {
        ScaledValue<std::ratio<1000>> x{5.3};

        ScaledValue<std::ratio<1,1000>> y{8.3};



        std::cout<<(x*y)<<"\n";

        x+=y;

        x*=y;
        x/=y;
        x-=y;
        ++x;
        --x;

        std::cout<<x<<"\n";

    }

    {
        using X = Value<::unit::u::newton,ScaledValue<std::ratio<1000>>>;
        X x{X::value_type{5.3}};

        using Y = Value<::unit::u::newton,ScaledValue<std::ratio<1,1000>>>;
        Y y{Y::value_type{8.3}};


        std::cout<<(x*y)<<"\n";

        x+=y;
        std::cout<<x<<"\n";
        x*=y;
        x/=y;
        x-=y;
        ++x;
        --x;

 //       using Z =  Value<newton,ScaledValue<std::ratio<1000001,1000>>>;

        auto z = x + y;

        using Z = Value<newton,ScaledValue<std::ratio<1000001,1000>>>;

        auto zz = static_ratio_cast<std::ratio<1000>>(z.magnitude());

         X zx{zz};

         x = zx;

//        x = static_ratio_cast<std::ratio<1000>>(x + y);
//        x = x - y;
//        x = x * y;
//        x = x / y;


        std::cout<<__LINE__ << ": " << x<<"\n";

    }




}
