#pragma once

#include <ctgmath>
#include <type_traits>
#include <ratio>
#include <iostream>
#include <ratio>

namespace sv {


template<typename ScaleRatio, typename TArithmetic = double>
class ScaledValue {

    template<typename , typename> friend class ScaledValue;

public:

    using scale = ScaleRatio;
    using classtype = ScaledValue<ScaleRatio, TArithmetic>;
    using value_type = TArithmetic;

    constexpr ScaledValue(value_type const& v):m_value(v){}
    constexpr ScaledValue(classtype const& v):m_value(v.m_value){}

    template<typename S, typename V>
    constexpr ScaledValue(ScaledValue<S, V> const& other):m_value((other.m_value*S::num*scale::den)/(S::den*scale::num)){}

    classtype operator=(classtype const& v){ m_value = v.m_value; return *this;}

    constexpr value_type value()const{return m_value;}
    void setValue(classtype const& v){m_value = v.m_value;}

    template<typename S, typename V>
    classtype& operator+=(ScaledValue<S, V> const& r){

        m_value += r.m_value*scale::den*S::num/scale::num/S::den;
        return *this;
    }

    template<typename S, typename V>
    classtype& operator-=(ScaledValue<S, V> const& r){

        m_value -= r.m_value*scale::den*S::num/scale::num/S::den;

        return *this;
    }

    template<typename S, typename V>
    classtype& operator*=(ScaledValue<S, V> const& r){

        m_value *= r.m_value*S::num/S::den;

        return *this;
}

    template<typename S, typename V>
    classtype& operator/=(ScaledValue<S, V> const& r){

        m_value /= r.m_value*S::num/S::den;

        return *this;
    }

private:


    value_type m_value;
};

namespace math {



template <typename S>
using AbsRatio = typename std::conditional<(S::num>0) ,S , std::ratio<-S::num,S::den>>::type;

template <typename S, typename T>
constexpr ScaledValue<AbsRatio<S>, decltype(std::abs(T{}))>
abs(ScaledValue<S, T> const& q) {
    return ScaledValue<AbsRatio<S>, decltype(std::abs(T{}))>{
                                              std::abs(q.value())};
}

template <typename S, typename T>
constexpr ScaledValue<S,decltype(std::sqrt(T{}*S::num/S::den)*S::den/S::num)>
sqrt(ScaledValue<S, T> const& q) {
    return ScaledValue<S, decltype(std::sqrt(q.value()*S::num/S::den)*S::den/S::num)>{
                                    std::sqrt(q.value()*S::num/S::den)*S::den/S::num};
}

template <typename S, typename T>
constexpr ScaledValue<S,decltype(std::pow(T{}*S::num/S::den,T{})*S::den/S::num)>
pow(ScaledValue<S, T> const& q, T const& exponent ) {
    return ScaledValue<S, decltype(std::pow(q.value()*S::num/S::den,exponent)*S::den/S::num)>{
                                    std::pow(q.value()*S::num/S::den,exponent)*S::den/S::num};
}


}

template< typename LScale, typename LTValue,
          typename RScale, typename RTValue>
constexpr auto
operator*(
    ScaledValue<LScale, LTValue> const& l,
    ScaledValue<RScale, RTValue> const& r)
        -> ScaledValue<LScale, decltype((l.value()*r.value()*RScale::num)/RScale::den)>
{
    return ScaledValue<LScale, decltype((l.value()*r.value()*RScale::num)/RScale::den)>{
                                        (l.value()*r.value()*RScale::num)/RScale::den};
}

template< typename LScale, typename LTValue,
          typename RScale, typename RTValue>
constexpr auto
operator/(
    ScaledValue<LScale, LTValue> const& l,
    ScaledValue<RScale, RTValue> const& r)
-> ScaledValue<LScale, decltype((l.value()*(RScale::num*RScale::den))/r.value())>
{
    return ScaledValue<LScale,
                      decltype((l.value()*(RScale::num*RScale::den))/r.value())>{
                               (l.value()*(RScale::num*RScale::den))/r.value()};
}

template< typename LScale, typename LTValue,
          typename RScale, typename RTValue>
constexpr auto
operator+(
    ScaledValue<LScale, LTValue> const& l,
    ScaledValue<RScale, RTValue> const& r)
        -> ScaledValue<LScale, decltype(l.value() + (r.value()*LScale::den*RScale::num)/(LScale::num*RScale::den))>
{
    return ScaledValue<LScale, decltype(l.value() + (r.value()*LScale::den*RScale::num)/(LScale::num*RScale::den))>{
                                        l.value() + (r.value()*LScale::den*RScale::num)/(LScale::num*RScale::den)};
}

template< typename LScale, typename LTValue,
          typename RScale, typename RTValue>
constexpr auto
operator-(
    ScaledValue<LScale, LTValue> const& l,
    ScaledValue<RScale, RTValue> const& r)
        -> ScaledValue<LScale, decltype(l.value() - (r.value()*LScale::den*RScale::num)/(LScale::num*RScale::den))>
{
    return ScaledValue<LScale, decltype(l.value() - (r.value()*LScale::den*RScale::num)/(LScale::num*RScale::den))>{
                                        l.value() - (r.value()*LScale::den*RScale::num)/(LScale::num*RScale::den)};
}



template< typename LScale, typename LTValue,
          typename RScale, typename RTValue>
constexpr bool operator==(
    ScaledValue<LScale, LTValue> const& l,
    ScaledValue<RScale, RTValue> const& r)
{
    return (l.value()*LTValue{(LScale::num*RScale::den)})==
           (r.value()*RTValue{(RScale::num*LScale::den)});
}

template< typename LScale, typename LTValue,
          typename RScale, typename RTValue>
constexpr bool operator!=(
    ScaledValue<LScale, LTValue> const& l,
    ScaledValue<RScale, RTValue> const& r)
{
    return (l==r)==false;
}


template< typename LScale, typename LTValue,
          typename RScale, typename RTValue>
constexpr bool operator<(
    ScaledValue<LScale, LTValue> const& l,
    ScaledValue<RScale, RTValue> const& r)
{
    return l.value()*(LScale::num*RScale::den) <
           r.value()*(RScale::num*LScale::den);
}

template< typename LScale, typename LTValue,
          typename RScale, typename RTValue>
constexpr bool operator<=(
    ScaledValue<LScale, LTValue> const& l,
    ScaledValue<RScale, RTValue> const& r)
{
    return l.value()*(LScale::num*RScale::den) <=
           r.value()*(RScale::num*LScale::den);
}

template< typename LScale, typename LTValue,
          typename RScale, typename RTValue>
constexpr bool operator>(
    ScaledValue<LScale, LTValue> const& l,
    ScaledValue<RScale, RTValue> const& r)
{
    return (l<=r)==false;
}

template< typename LScale, typename LTValue,
          typename RScale, typename RTValue>
constexpr bool operator>=(
    ScaledValue<LScale, LTValue> const& l,
    ScaledValue<RScale, RTValue> const& r)
{
    return (l<r)==false;
}


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
