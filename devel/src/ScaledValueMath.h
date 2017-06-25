#pragma once

#include "ScaledValue.h"
#include <ctgmath>
#include <type_traits>
#include <ratio>

namespace sv {

template <typename S>
using AbsRatio = typename std::conditional<(S::num>0) ,S , std::ratio<-S::num,S::den>>::type;


template <typename S, typename V>
constexpr auto
abs(ScaledValue<S, V> const& q)
        -> ScaledValue<AbsRatio<S>, decltype(abs(q.unscaledValue()))>
{
    using std::abs;
    return ScaledValue<AbsRatio<S>, decltype(abs(q.unscaledValue()))>{
                                             abs(q.unscaledValue())};
}

template <typename S, typename V>
constexpr auto
sqrt(ScaledValue<S, V> const& q)
        -> ScaledValue<S, decltype(sqrt(q.unscaledValue()*V{S::num/S::den})*V{S::den/S::num})>
{
    using std::sqrt;
    return ScaledValue<S, decltype(sqrt(q.unscaledValue()*V{S::num}/V{S::den})*V{S::den}/V{S::num})>{
                                   sqrt(q.unscaledValue()*V{S::num}/V{S::den})*V{S::den}/V{S::num}};
}

template <typename S, typename V>
constexpr auto
pow(ScaledValue<S, V> const& q, V const& exponent )
       ->  ScaledValue<S, decltype(pow(q.unscaledValue()*V{S::num}/V{S::den},exponent)*V{S::den}/V{S::num})>
{
    using std::pow;
    return ScaledValue<S, decltype(pow(q.unscaledValue()*V{S::num}/V{S::den},exponent)*V{S::den}/V{S::num})>{
                                   pow(q.unscaledValue()*V{S::num}/V{S::den},exponent)*V{S::den}/V{S::num}};
}


} //sv


