#pragma once

#include <ratio>

namespace sv {



template<typename ScaleRatio, typename TrueValueType = double, typename UnscaledValueType = TrueValueType>
class ScaledValue {

    template<typename , typename, typename> friend class ScaledValue;

public:

    // true_value == unscaled_value * scale::num / scale::den

    using scale = ScaleRatio;
    using classtype = ScaledValue<ScaleRatio, TrueValueType, UnscaledValueType>;
    using true_value_type = TrueValueType;
    using unscaled_value_type = UnscaledValueType;

    template<typename OtherScale>
    using p_scale = std::ratio_multiply<scale,OtherScale>;
    template<typename OtherScale>
    using q_scale = std::ratio_divide<scale,OtherScale>;

    constexpr ScaledValue():m_unscaled_value(0){}
    constexpr ScaledValue(unscaled_value_type const& v):m_unscaled_value(v){} //delayed rescaling
    constexpr ScaledValue(classtype const&) = default;
    constexpr ScaledValue(classtype &&) = default;

    template<typename S, typename V>
    constexpr ScaledValue(ScaledValue<S, V> const& other):m_unscaled_value((other.m_unscaled_value*q_scale<S>::num)/(q_scale<S>::den)){}

    classtype& operator=(classtype const& v) = default;

    constexpr true_value_type trueValue()const{return static_cast<true_value_type>((m_unscaled_value*scale::num)/scale::den);}

    constexpr unscaled_value_type unscaledValue()const{return m_unscaled_value;}

    void setTrueValue(true_value_type const& v){ m_unscaled_value = static_cast<UnscaledValueType>((v * scale::den)/scale::num); }
    void setUnscaledValue(unscaled_value_type const& v){m_unscaled_value = v;}


    template<typename S, typename V, typename U>
    classtype& operator+=(ScaledValue<S, V, U> const& r){

        m_unscaled_value += r.m_unscaled_value*scale::den*S::num/scale::num/S::den;
        return *this;
    }

    template<typename S, typename V, typename U>
    classtype& operator-=(ScaledValue<S, V, U> const& r){

        m_unscaled_value -= r.m_unscaled_value*scale::den*S::num/scale::num/S::den;

        return *this;
    }

    template<typename S, typename V, typename U>
    classtype& operator*=(ScaledValue<S, V, U> const& r){

        m_unscaled_value *= r.m_unscaled_value*S::num/S::den;

        return *this;
}

    template<typename S, typename V, typename U>
    classtype& operator/=(ScaledValue<S, V, U> const& r){

        m_unscaled_value /= r.m_unscaled_value*S::num/S::den;

        return *this;
    }


private:


    unscaled_value_type m_unscaled_value; //is always relative to scale, to get unscaled value ScaleRatio<std::ratio<1>>(scaled).value();
};



}


