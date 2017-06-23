#pragma once

#include "ScaledValue.h"

#include <iostream>
#include <ratio>



namespace sv {

namespace {

template<typename ratio>
std::ostream& printRatio(std::ostream& s, const char* prefixIfNonEmpty, const char* suffixIfNonEmpty){

    if (ratio::num==ratio::den) return s;

    s<<prefixIfNonEmpty;

    if (ratio::den==1) {
        s << ratio::num << suffixIfNonEmpty;
        return s;
    }
    s<<"(" << ratio::num << "/" << ratio::den << ")" << suffixIfNonEmpty;
    return s;
}

template<> inline std::ostream& printRatio<std::atto>(std::ostream& s, const char* px, const char* sx){return s << px << "atto" << sx;}
template<> inline std::ostream& printRatio<std::femto>(std::ostream& s, const char* px, const char* sx){return s << px << "femto" << sx;}
template<> inline std::ostream& printRatio<std::pico>(std::ostream& s, const char* px, const char* sx){return s << px << "pico" << sx;}
template<> inline std::ostream& printRatio<std::nano>(std::ostream& s, const char* px, const char* sx){return s << px << "nano" << sx;}
template<> inline std::ostream& printRatio<std::micro>(std::ostream& s, const char* px, const char* sx){return s << px << "micro" << sx;}
template<> inline std::ostream& printRatio<std::milli>(std::ostream& s, const char* px, const char* sx){return s << px << "milli" << sx;}
template<> inline std::ostream& printRatio<std::centi>(std::ostream& s, const char* px, const char* sx){return s << px << "centi" << sx;}
template<> inline std::ostream& printRatio<std::deci>(std::ostream& s, const char* px, const char* sx){return s << px << "deci" << sx;}
template<> inline std::ostream& printRatio<std::deca>(std::ostream& s, const char* px, const char* sx){return s << px << "deca" << sx;}
template<> inline std::ostream& printRatio<std::hecto>(std::ostream& s, const char* px, const char* sx){return s << px << "hecto" << sx;}
template<> inline std::ostream& printRatio<std::kilo>(std::ostream& s, const char* px, const char* sx){return s << px << "kilo" << sx;}
template<> inline std::ostream& printRatio<std::mega>(std::ostream& s, const char* px, const char* sx){return s << px << "mega" << sx;}
template<> inline std::ostream& printRatio<std::giga>(std::ostream& s, const char* px, const char* sx){return s << px << "giga" << sx;}
template<> inline std::ostream& printRatio<std::tera>(std::ostream& s, const char* px, const char* sx){return s << px << "tera" << sx;}
template<> inline std::ostream& printRatio<std::peta>(std::ostream& s, const char* px, const char* sx){return s << px << "peta" << sx;}
template<> inline std::ostream& printRatio<std::exa>(std::ostream& s, const char* px, const char* sx){return s << px << "exa" << sx;}


}

template<typename Scale, typename TValue>
std::ostream& operator<<(std::ostream& s, ScaledValue<Scale,TValue> const& v){

    s << v.value();

    printRatio<typename ScaledValue<Scale,TValue>::scale>(s,"*","");

    return s;
}

}


