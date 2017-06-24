#pragma once

#include "ScaledValue.h"
#include <ctgmath>
#include <type_traits>
#include <ratio>

namespace sv {

template <typename S>
using AbsRatio = typename std::conditional<(S::num>0) ,S , std::ratio<-S::num,S::den>>::type;


template <typename S, typename T>
constexpr auto
abs(ScaledValue<S, T> const& q)
        -> ScaledValue<AbsRatio<S>, decltype(abs(q.value()))>
{
    using std::abs;
    return ScaledValue<AbsRatio<S>, decltype(abs(q.value()))>{
                                             abs(q.value())};
}

template <typename S, typename T>
constexpr auto
sqrt(ScaledValue<S, T> const& q)
         -> ScaledValue<S,decltype(sqrt(q.value()*S::num/S::den)*S::den/S::num)>
{
    using std::sqrt;
    return ScaledValue<S, decltype(sqrt(q.value()*S::num/S::den)*S::den/S::num)>{
                                   sqrt(q.value()*S::num/S::den)*S::den/S::num};
}

template <typename S, typename T>
constexpr auto
pow(ScaledValue<S, T> const& q, T const& exponent )
       ->  ScaledValue<S,decltype(pow(q.value()*S::num/S::den,exponent)*S::den/S::num)>
{
    using std::pow;
    return ScaledValue<S, decltype(pow(q.value()*S::num/S::den,exponent)*S::den/S::num)>{
                                   pow(q.value()*S::num/S::den,exponent)*S::den/S::num};
}


} //sv


