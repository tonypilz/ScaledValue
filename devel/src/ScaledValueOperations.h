#pragma once

#include "ScaledValue.h"
#include <ratio>

namespace sv {

template< typename LS, typename LV,
          typename RS, typename RV>
constexpr auto
operator*(ScaledValue<LS, LV> const& l,
          ScaledValue<RS, RV> const& r)
        -> ScaledValue<LS, decltype(l.unscaledValue()*LV{RS::num}*r.unscaledValue()/LV{RS::den})>
{
    return ScaledValue<LS, decltype(l.unscaledValue()*LV{RS::num}*r.unscaledValue()/LV{RS::den})>{
                                    l.unscaledValue()*LV{RS::num}*r.unscaledValue()/LV{RS::den}};
}




template< typename LS, typename LV,
          typename RS, typename RV>
constexpr auto
operator/(ScaledValue<LS, LV> const& l,
          ScaledValue<RS, RV> const& r)
        -> ScaledValue<LS, decltype(l.unscaledValue()*LV{RS::den}/LV{RS::num}/r.unscaledValue())>
{
    return ScaledValue<LS, decltype(l.unscaledValue()*LV{RS::den}/LV{RS::num}/r.unscaledValue())>{
                                    l.unscaledValue()*LV{RS::den}/LV{RS::num}/r.unscaledValue()};
}


template< typename LS, typename LV,
          typename RS, typename RV>
constexpr auto
operator+(ScaledValue<LS, LV> const& l,
          ScaledValue<RS, RV> const& r)
        -> ScaledValue<LS, decltype(l.unscaledValue() + (r.unscaledValue()*RV{LS::den*RS::num})/RV{LS::num*RS::den})>
{
    return ScaledValue<LS, decltype(l.unscaledValue() + (r.unscaledValue()*RV{LS::den*RS::num})/RV{LS::num*RS::den})>{
                                    l.unscaledValue() + (r.unscaledValue()*RV{LS::den*RS::num})/RV{LS::num*RS::den}};
}


template< typename LS, typename LV,
          typename RS, typename RV>
constexpr auto
operator-(ScaledValue<LS, LV> const& l,
          ScaledValue<RS, RV> const& r)
        -> ScaledValue<LS, decltype(l.unscaledValue() - (r.unscaledValue()*RV{LS::den*RS::num})/RV{LS::num*RS::den})>
{
    return ScaledValue<LS, decltype(l.unscaledValue() - (r.unscaledValue()*RV{LS::den*RS::num})/RV{LS::num*RS::den})>{
                                    l.unscaledValue() - (r.unscaledValue()*RV{LS::den*RS::num})/RV{LS::num*RS::den}};
}

template< typename S, typename V, typename U>
constexpr auto
operator-(ScaledValue<S, V> const& l)
        -> ScaledValue<S, decltype(-l.unscaledValue())>
{
    return ScaledValue<S, decltype(-l.unscaledValue())>{
                                   -l.unscaledValue()};
}

template< typename LS, typename LV,
          typename RS, typename RV>
constexpr bool
operator==(ScaledValue<LS, LV> const& l,
           ScaledValue<RS, RV> const& r)
{
    return (l.unscaledValue()*LV{LS::num*RS::den})==
           (r.unscaledValue()*RV{RS::num*LS::den});
}




template< typename LS, typename LV,
          typename RS, typename RV>
constexpr bool
operator!=(ScaledValue<LS, LV> const& l,
           ScaledValue<RS, RV> const& r)
{
    return (l==r)==false;
}


template< typename LS, typename LV,
          typename RS, typename RV>
constexpr bool
operator<(ScaledValue<LS, LV> const& l,
          ScaledValue<RS, RV> const& r)
{
    return l.unscaledValue()*LV{LS::num*RS::den} <
           r.unscaledValue()*RV{RS::num*LS::den}; //avoid division due to rounding, X::den is always > 0
}


template< typename LS, typename LV,
          typename RS, typename RV>
constexpr bool
operator<=(ScaledValue<LS, LV> const& l,
           ScaledValue<RS, RV> const& r)
{
    return l.unscaledValue()*LV{LS::num*RS::den} <=
           r.unscaledValue()*RV{RS::num*LS::den}; //avoid division due to rounding, X::den is always > 0
}


template< typename LS, typename LV,
          typename RS, typename RV>
constexpr bool
operator>(ScaledValue<LS, LV> const& l,
          ScaledValue<RS, RV> const& r)
{
    return (l<=r)==false;
}


template< typename LS, typename LV,
          typename RS, typename RV>
constexpr bool
operator>=(ScaledValue<LS, LV> const& l,
           ScaledValue<RS, RV> const& r)
{
    return (l<r)==false;
}






} //sv

