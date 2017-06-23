#pragma once

#include "ScaledValue.h"
#include <ctgmath>
#include <type_traits>
#include <ratio>

namespace sv {
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
}


