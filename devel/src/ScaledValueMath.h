#pragma once

#include "ScaledValue.h"
#include <ctgmath>
#include <type_traits>
#include <ratio>

namespace sv {
namespace math {

using std::ratio;
using std::abs;
using std::sqrt;
using std::pow;
using std::conditional;

template <typename S>
using AbsRatio = typename conditional<(S::num>0) ,S , ratio<-S::num,S::den>>::type;

template <typename S, typename T>
constexpr ScaledValue<AbsRatio<S>, decltype(abs(T{}))>
abs(ScaledValue<S, T> const& q) {
    return ScaledValue<AbsRatio<S>, decltype(abs(T{}))>{
                                              abs(q.value())};
}

template <typename S, typename T>
constexpr ScaledValue<S,decltype(sqrt(T{}*S::num/S::den)*S::den/S::num)>
sqrt(ScaledValue<S, T> const& q) {
    return ScaledValue<S, decltype(sqrt(q.value()*S::num/S::den)*S::den/S::num)>{
                                    sqrt(q.value()*S::num/S::den)*S::den/S::num};
}

template <typename S, typename T>
constexpr ScaledValue<S,decltype(pow(T{}*S::num/S::den,T{})*S::den/S::num)>
pow(ScaledValue<S, T> const& q, T const& exponent ) {
    return ScaledValue<S, decltype(pow(q.value()*S::num/S::den,exponent)*S::den/S::num)>{
                                    pow(q.value()*S::num/S::den,exponent)*S::den/S::num};
}


}
}


