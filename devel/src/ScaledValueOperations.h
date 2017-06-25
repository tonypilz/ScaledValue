#pragma once

#include "ScaledValue.h"
#include <ratio>

namespace sv {

template< typename LS, typename LV, typename LU,
          typename RS, typename RV, typename RU>
constexpr auto
operator*(ScaledValue<LS, LV, LU> const& l,
          ScaledValue<RS, RV, RU> const& r)
        -> ScaledValue<LS, LV, decltype((l.unscaledValue()*r.unscaledValue()*RS::num)/RS::den)>
{
    return ScaledValue<LS, LV, decltype((l.unscaledValue()*r.unscaledValue()*RS::num)/RS::den)>{
                                        (l.unscaledValue()*r.unscaledValue()*RS::num)/RS::den};
}




template< typename LS, typename LV, typename LU,
          typename RS, typename RV, typename RU>
constexpr auto
operator/(ScaledValue<LS, LV, LU> const& l,
          ScaledValue<RS, RV, RU> const& r)
        -> ScaledValue<LS, LV, decltype((l.unscaledValue()*(RS::num*RS::den))/r.unscaledValue())>
{
    return ScaledValue<LS, LV, decltype((l.unscaledValue()*(RS::num*RS::den))/r.unscaledValue())>{
                                        (l.unscaledValue()*(RS::num*RS::den))/r.unscaledValue()};
}


template< typename LS, typename LV, typename LU,
          typename RS, typename RV, typename RU>
constexpr auto
operator+(ScaledValue<LS, LV, LU> const& l,
          ScaledValue<RS, RV, RU> const& r)
        -> ScaledValue<LS, LV, decltype(l.unscaledValue() + (r.unscaledValue()*LS::den*RS::num)/(LS::num*RS::den))>
{
    return ScaledValue<LS, LV, decltype(l.unscaledValue() + (r.unscaledValue()*LS::den*RS::num)/(LS::num*RS::den))>{
                                        l.unscaledValue() + (r.unscaledValue()*LS::den*RS::num)/(LS::num*RS::den)};
}


template< typename LS, typename LV, typename LU,
          typename RS, typename RV, typename RU>
constexpr auto
operator-(ScaledValue<LS, LV, LU> const& l,
          ScaledValue<RS, RV, RU> const& r)
        -> ScaledValue<LS, LV, decltype(l.unscaledValue() - (r.unscaledValue()*LS::den*RS::num)/(LS::num*RS::den))>
{
    return ScaledValue<LS, LV, decltype(l.unscaledValue() - (r.unscaledValue()*LS::den*RS::num)/(LS::num*RS::den))>{
                                        l.unscaledValue() - (r.unscaledValue()*LS::den*RS::num)/(LS::num*RS::den)};
}

template< typename S, typename V, typename U>
constexpr auto
operator-(ScaledValue<S, V, U> const& l)
        -> ScaledValue<S, V, decltype(-l.unscaledValue())>
{
    return ScaledValue<S, V, decltype(-l.unscaledValue())>{
                                      -l.unscaledValue()};
}

template< typename LS, typename LV, typename LU,
          typename RS, typename RV, typename RU>
constexpr bool
operator==(ScaledValue<LS, LV, LU> const& l,
           ScaledValue<RS, RV, RU> const& r)
{
    return (l.unscaledValue()*LU{LS::num*RS::den})==
           (r.unscaledValue()*RU{RS::num*LS::den});
}




template< typename LS, typename LV, typename LU,
          typename RS, typename RV, typename RU>
constexpr bool
operator!=(ScaledValue<LS, LV, LU> const& l,
           ScaledValue<RS, RV, RU> const& r)
{
    return (l==r)==false;
}


template< typename LS, typename LV, typename LU,
          typename RS, typename RV, typename RU>
constexpr bool
operator<(ScaledValue<LS, LV, LU> const& l,
          ScaledValue<RS, RV, RU> const& r)
{
    return l.unscaledValue()*(LS::num*RS::den) <
           r.unscaledValue()*(RS::num*LS::den); //avoid division due to rounding, X::den is always > 0
}


template< typename LS, typename LV, typename LU,
          typename RS, typename RV, typename RU>
constexpr bool
operator<=(ScaledValue<LS, LV, LU> const& l,
           ScaledValue<RS, RV, RU> const& r)
{
    return l.unscaledValue()*(LS::num*RS::den) <=
           r.unscaledValue()*(RS::num*LS::den); //avoid division due to rounding, X::den is always > 0
}


template< typename LS, typename LV, typename LU,
          typename RS, typename RV, typename RU>
constexpr bool
operator>(ScaledValue<LS, LV, LU> const& l,
          ScaledValue<RS, RV, RU> const& r)
{
    return (l<=r)==false;
}


template< typename LS, typename LV, typename LU,
          typename RS, typename RV, typename RU>
constexpr bool
operator>=(ScaledValue<LS, LV, LU> const& l,
           ScaledValue<RS, RV, RU> const& r)
{
    return (l<r)==false;
}






} //sv

