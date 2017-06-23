#pragma once

namespace sv {



template<typename ScaleRatio, typename TArithmetic = double>
class ScaledValue {

    template<typename , typename> friend class ScaledValue;

public:

    using scale = ScaleRatio;
    using classtype = ScaledValue<ScaleRatio, TArithmetic>;
    using value_type = TArithmetic;

    constexpr ScaledValue(value_type const& v):m_value(v){}
    constexpr ScaledValue(classtype const& v):m_value(v.m_value){}

    template<typename S, typename V>
    constexpr ScaledValue(ScaledValue<S, V> const& other):m_value((other.m_value*S::num*scale::den)/(S::den*scale::num)){}

    classtype operator=(classtype const& v){ m_value = v.m_value; return *this;}

    constexpr value_type value()const{return m_value;}
    void setValue(classtype const& v){m_value = v.m_value;}

    template<typename S, typename V>
    classtype& operator+=(ScaledValue<S, V> const& r){

        m_value += r.m_value*scale::den*S::num/scale::num/S::den;
        return *this;
    }

    template<typename S, typename V>
    classtype& operator-=(ScaledValue<S, V> const& r){

        m_value -= r.m_value*scale::den*S::num/scale::num/S::den;

        return *this;
    }

    template<typename S, typename V>
    classtype& operator*=(ScaledValue<S, V> const& r){

        m_value *= r.m_value*S::num/S::den;

        return *this;
}

    template<typename S, typename V>
    classtype& operator/=(ScaledValue<S, V> const& r){

        m_value /= r.m_value*S::num/S::den;

        return *this;
    }

private:


    value_type m_value; //is always relative to scale, to get unscaled value ScaleRatio<std::ratio<1>>(scaled).value();
};

}


