#pragma once

#include <ratio>

namespace sv {



template<typename ScaleRatio, typename UnscaledValueType = double>
class ScaledValue {

    template<typename , typename> friend class ScaledValue;

public:

    // true_value == unscaled_value * scale::num / scale::den

    using scale = ScaleRatio;
    using classtype = ScaledValue<ScaleRatio, UnscaledValueType>;
    using unscaled_value_type = UnscaledValueType;

    constexpr ScaledValue():m_unscaled_value(0){}
    constexpr ScaledValue(unscaled_value_type const& v):m_unscaled_value(v){} //delayed rescaling
    constexpr ScaledValue(classtype const&) = default;
    constexpr ScaledValue(classtype &&) = default;

    template<typename OtherScale>
    using s_divide = std::ratio_divide<scale, OtherScale>;

    template<typename S, typename V>
    constexpr ScaledValue(ScaledValue<S, V> const& other):m_unscaled_value((other.m_unscaled_value*s_divide<S>::den)/(s_divide<S>::num)){}

    classtype& operator=(classtype const& v) = default;

    template< typename T = unscaled_value_type>
    constexpr T trueValue()const{return static_cast<T>((m_unscaled_value*scale::num)/scale::den);}

    constexpr unscaled_value_type unscaledValue()const{return m_unscaled_value;}




    template<typename S, typename V>
    classtype& operator+=(ScaledValue<S, V> const& r){ m_unscaled_value += r.m_unscaled_value*s_divide<S>::den/s_divide<S>::num; return *this; }

    template<typename S, typename V>
    classtype& operator-=(ScaledValue<S, V> const& r){ m_unscaled_value -= r.m_unscaled_value*s_divide<S>::den/s_divide<S>::num; return *this; }

    template<typename S, typename V>
    classtype& operator*=(ScaledValue<S, V> const& r){ m_unscaled_value *= r.m_unscaled_value*S::num/S::den; return *this; }

    template<typename S, typename V>
    classtype& operator/=(ScaledValue<S, V> const& r){ m_unscaled_value /= r.m_unscaled_value*S::num/S::den; return *this; }


private:


    unscaled_value_type m_unscaled_value; //is always relative to scale, to get unscaled value ScaleRatio<std::ratio<1>>(scaled).value();
};



}


