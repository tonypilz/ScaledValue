#pragma once

#include "ScaledValue.h"

namespace sv {

template< typename LScale, typename LTValue,
          typename RScale, typename RTValue>
constexpr auto
operator*(ScaledValue<LScale, LTValue> const& l,
          ScaledValue<RScale, RTValue> const& r)
        -> ScaledValue<LScale, decltype((l.value()*r.value()*RScale::num)/RScale::den)>
{
    return ScaledValue<LScale, decltype((l.value()*r.value()*RScale::num)/RScale::den)>{
                                        (l.value()*r.value()*RScale::num)/RScale::den};
}


template< typename LScale, typename LTValue,
          typename RScale, typename RTValue>
constexpr auto
operator/(ScaledValue<LScale, LTValue> const& l,
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
operator+(ScaledValue<LScale, LTValue> const& l,
          ScaledValue<RScale, RTValue> const& r)
        -> ScaledValue<LScale, decltype(l.value() + (r.value()*LScale::den*RScale::num)/(LScale::num*RScale::den))>
{
    return ScaledValue<LScale, decltype(l.value() + (r.value()*LScale::den*RScale::num)/(LScale::num*RScale::den))>{
                                        l.value() + (r.value()*LScale::den*RScale::num)/(LScale::num*RScale::den)};
}


template< typename LScale, typename LTValue,
          typename RScale, typename RTValue>
constexpr auto
operator-(ScaledValue<LScale, LTValue> const& l,
          ScaledValue<RScale, RTValue> const& r)
        -> ScaledValue<LScale, decltype(l.value() - (r.value()*LScale::den*RScale::num)/(LScale::num*RScale::den))>
{
    return ScaledValue<LScale, decltype(l.value() - (r.value()*LScale::den*RScale::num)/(LScale::num*RScale::den))>{
                                        l.value() - (r.value()*LScale::den*RScale::num)/(LScale::num*RScale::den)};
}


template< typename LScale, typename LTValue,
          typename RScale, typename RTValue>
constexpr bool
operator==(ScaledValue<LScale, LTValue> const& l,
           ScaledValue<RScale, RTValue> const& r)
{
    return (l.value()*LTValue{(LScale::num*RScale::den)})==
           (r.value()*RTValue{(RScale::num*LScale::den)});
}


template< typename LScale, typename LTValue,
          typename RScale, typename RTValue>
constexpr bool
operator!=(ScaledValue<LScale, LTValue> const& l,
           ScaledValue<RScale, RTValue> const& r)
{
    return (l==r)==false;
}


template< typename LScale, typename LTValue,
          typename RScale, typename RTValue>
constexpr bool
operator<(ScaledValue<LScale, LTValue> const& l,
          ScaledValue<RScale, RTValue> const& r)
{
    return l.value()*(LScale::num*RScale::den) <
           r.value()*(RScale::num*LScale::den); //avoid division due to rounding, X::den is always > 0
}


template< typename LScale, typename LTValue,
          typename RScale, typename RTValue>
constexpr bool
operator<=(ScaledValue<LScale, LTValue> const& l,
           ScaledValue<RScale, RTValue> const& r)
{
    return l.value()*(LScale::num*RScale::den) <=
           r.value()*(RScale::num*LScale::den); //avoid division due to rounding, X::den is always > 0
}


template< typename LScale, typename LTValue,
          typename RScale, typename RTValue>
constexpr bool
operator>(ScaledValue<LScale, LTValue> const& l,
          ScaledValue<RScale, RTValue> const& r)
{
    return (l<=r)==false;
}


template< typename LScale, typename LTValue,
          typename RScale, typename RTValue>
constexpr bool
operator>=(ScaledValue<LScale, LTValue> const& l,
           ScaledValue<RScale, RTValue> const& r)
{
    return (l<r)==false;
}


} //sv

