# ScaledValue
A lightweight, compile-time, single header-file library class for representing (eg double-) values on different scales built on c++11 with no dependencies.


# Latest Release - v1.0.0

Initial release.

## Tested on
 - gcc-5.3.0

## Compiles Under
 - icc-16 + 17
 - gcc-7 .. gcc-4.7
 - ARM gcc 5.4
 - ARM64 gcc 5.4
 - MIPS gcc 5.4
 - clang 4.0 .. clang 3.4
 
# Contents
- [ScaledValue](#scaledvalue)
- [Latest Release - v1.1.0](#latest-release---v100)
  - [Tested on](#tested-on)
  - [Compiles Under](#compiles-under)
- [Contents](#contents)
- [Description](#description)
- [Limitations](#limitations)
- [Getting Started Guide](#getting-started-guide)


# Description

The library allows to represent a (e.g. double) value on a scale. The following example illustrates the idea: 


```cpp
#include <ScaledValue.h>

int main() {

    using namespace sv;
    
    //define values on different scales
    auto seconds_a = ScaledValue<std::nano>{500}; // represents 5 nanoseconds
    auto seconds_b = ScaledValue<std::micro>{9};  // represents 9 microseconds

    //combination
    auto seconds_c = seconds_a + seconds_b;
    auto seconds_d = seconds_a * seconds_b;
    bool greater = seconds_a > seconds_b; //greater==false

    //math operations
    auto seconds_e = math::pow(seconds_b,0.5); 

    //conversions
    auto seconds_f = ScaledValue<std::nano>{seconds_b};

    //printing
    std::cout<< seconds_b <<std::endl; // prints "9*micro"
    std::cout<< seconds_c <<std::endl; // prints "9500*nano"
    std::cout<< seconds_d <<std::endl; // prints "0.0045*nano"
    std::cout<< seconds_e <<std::endl; // prints "2645.75*micro" // see *
    std::cout<< seconds_f <<std::endl; // prints "9000*nano"
    
    return 0;
}
```

Working on a specific scale incurs no runtime overhead (on -O1). The library is small (~200 sloc), tested, easy to understand and easy to extend to specific user needs. It can be used together with the [units](https://github.com/tonypilz/units) library.

*Note that since the true value of `seconds_b` is actually 9e-6 (seconds), the root is taken from this value rather than from 9 yielding 0.00264575 (seconds) and not 3.

# Limitations
Scales are compile time properties so they cannot be used in a dynamic fashion*. Printing of scaled values is rather simple but can be adjusted if needed. Not all math functions from <cmath> are defined, but they are also simple to add.

* Dynamic behaviour can be introduced by using `std::variant` (c++17) with this class.

# Getting Started Guide
The library consists of a single file ([ScaledValue.h](include/ScaledValue.h)). To incorporate the library into your project, simply copy the header into a location in your include path and include it as seen in the [Description](#description).

