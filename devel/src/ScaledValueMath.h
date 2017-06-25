#pragma once

#include "ScaledValue.h"
#include <ctgmath>
#include <type_traits>
#include <ratio>

namespace sv {

template <typename S>
using AbsRatio = typename std::conditional<(S::num>0) ,S , std::ratio<-S::num,S::den>>::type;


template <typename S, typename V, typename U>
constexpr auto
abs(ScaledValue<S, V, U> const& q)
        -> ScaledValue<AbsRatio<S>, V, decltype(abs(q.unscaledValue()))>
{
    using std::abs;
    return ScaledValue<AbsRatio<S>, V, decltype(abs(q.unscaledValue()))>{
                                                abs(q.unscaledValue())};
}

template <typename S, typename V, typename U>
constexpr auto
sqrt(ScaledValue<S, V, U> const& q)
        -> ScaledValue<S, V, decltype(sqrt(q.unscaledValue()*S::num/S::den)*S::den/S::num)>
{
    using std::sqrt;
    return ScaledValue<S, V, decltype(sqrt(q.unscaledValue()*S::num/S::den)*S::den/S::num)>{
                                      sqrt(q.unscaledValue()*S::num/S::den)*S::den/S::num};
}

template <typename S, typename V, typename U>
constexpr auto
pow(ScaledValue<S, V, U> const& q, V const& exponent )
       ->  ScaledValue<S, V, decltype(pow(q.unscaledValue()*S::num/S::den,exponent)*S::den/S::num)>
{
    using std::pow;
    return ScaledValue<S, V, decltype(pow(q.unscaledValue()*S::num/S::den,exponent)*S::den/S::num)>{
                                      pow(q.unscaledValue()*S::num/S::den,exponent)*S::den/S::num};
}


} //sv


