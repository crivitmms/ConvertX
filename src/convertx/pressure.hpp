#ifndef __PRESSURE_H__
#define __PRESSURE_H__

#include <utility>

namespace ConvertX
{

    enum class PressureUnit
    {
        PA,
        KPA,
        BAR,
        PSI,
        ATMOSPHERE
    };

    template <PressureUnit BaseUnit = PressureUnit::BAR>
    class Pressure
    {
        double _value = 0;
        constexpr double convertToBar() const
        {
            switch (BaseUnit)
            {
            case PressureUnit::PA: return _value * 0.000'01;
            case PressureUnit::KPA: return _value * 0.01;
            case PressureUnit::BAR: return _value;
            case PressureUnit::PSI: return _value * 0.0689475728;
            case PressureUnit::ATMOSPHERE: return _value * 1.01325;
            default:
                throw std::runtime_error("not a conversion unit");
                // std::unreachable();
            }
        }

    public:
        constexpr double convertTo(const PressureUnit unit) const
        {
            if (unit == BaseUnit)
                return _value;
            switch (unit)
            {
            case PressureUnit::PA: return convertToBar() * 100'000;
            case PressureUnit::KPA: return convertToBar() * 100;
            case PressureUnit::BAR: return convertToBar();
            case PressureUnit::PSI: return convertToBar() * 14.503773800722;
            case PressureUnit::ATMOSPHERE: return convertToBar() * 0.98692326671601;
            default:
                throw std::runtime_error("not a conversion unit");
                // std::unreachable();
            }
        }

        constexpr Pressure(double value = 0) :
            _value(value) {};

        template <PressureUnit IncommingUnit>
        constexpr Pressure(const Pressure<IncommingUnit> rhs) :
            _value(rhs.convertTo(BaseUnit))
        {
        }

        constexpr double getvalue() const
        {
            return _value;
        }

        constexpr PressureUnit getUnitType() const
        {
            return BaseUnit;
        }

        template <PressureUnit IncommingUnit>
        constexpr Pressure<BaseUnit> &operator=(const Pressure<IncommingUnit> &other)
        {
            _value = other.convertTo(BaseUnit);
            return *this;
        }
        template <typename T>
        constexpr Pressure<BaseUnit> &operator=(const T &other)
        {
            _value = other;
            return *this;
        }

        template <PressureUnit IncommingUnit>
        constexpr Pressure<BaseUnit> &operator+=(const Pressure<IncommingUnit> &other)
        {
            _value += other.convertTo(BaseUnit);
            return *this;
        }
        template <typename T>
        constexpr Pressure<BaseUnit> &operator+=(const T other)
        {
            _value += other;
            return *this;
        }

        template <PressureUnit IncommingUnit>
        constexpr Pressure<BaseUnit> operator+(const Pressure<IncommingUnit> &other)
        {
            return Pressure<BaseUnit>(_value + other.convertTo(BaseUnit));
        }
        template <typename T>
        constexpr Pressure<BaseUnit> operator+(const T other)
        {
            return Pressure<BaseUnit>(_value + other);
        }

        template <PressureUnit IncommingUnit>
        constexpr Pressure<BaseUnit> &operator-=(const Pressure<IncommingUnit> &other)
        {
            _value -= other.convertTo(BaseUnit);
            return *this;
        }
        template <typename T>
        constexpr Pressure<BaseUnit> &operator-=(const T other)
        {
            _value -= other;
            return *this;
        }

        template <PressureUnit IncommingUnit>
        constexpr Pressure<BaseUnit> operator-(const Pressure<IncommingUnit> &other)
        {
            return Pressure<BaseUnit>(_value - other.convertTo(BaseUnit));
        }
        template <typename T>
        constexpr Pressure<BaseUnit> operator-(const T other)
        {
            return Pressure<BaseUnit>(_value - other);
        }

        template <typename T>
        constexpr Pressure<BaseUnit> operator*=(const T other)
        {
            _value *= other;
            return *this;
        }

        template <typename T>
        constexpr Pressure<BaseUnit> operator*(const T other)
        {
            return Pressure<BaseUnit>(_value * other);
        }

        template <typename T>
        constexpr Pressure<BaseUnit> operator/=(const T other)
        {
            _value /= other;
            return *this;
        }

        template <typename T>
        constexpr Pressure<BaseUnit> operator/(const T other)
        {
            return Pressure<BaseUnit>(_value / other);
        }

        template <PressureUnit IncommingUnit>
        constexpr Pressure<BaseUnit> operator%=(const Pressure<IncommingUnit> &other)
        {
            _value %= other.convertTo(BaseUnit);
            return *this;
        }
        template <typename T>
        constexpr Pressure<BaseUnit> operator%=(const T other)
        {
            _value = fmod(_value, other);
            return *this;
        }

        template <PressureUnit IncommingUnit>
        constexpr Pressure<BaseUnit> operator%(const Pressure<IncommingUnit> &other)
        {
            return Pressure<BaseUnit>(_value % other.convertTo(BaseUnit));
        }
        template <typename T>
        constexpr Pressure<BaseUnit> operator%(const T other)
        {
            return Pressure<BaseUnit>(fmod(_value, other));
        }

        constexpr Pressure<BaseUnit> &operator++()
        {
            _value++;
            return *this;
        }
        constexpr Pressure<BaseUnit> operator++(int)
        {
            Pressure<BaseUnit> old = *this;
            _value++;
            return old;
        }

        template <PressureUnit IncommingUnit>
        constexpr bool operator<(const Pressure<IncommingUnit> &other)
        {
            return _value < other.convertTo(BaseUnit);
        }
        template <PressureUnit IncommingUnit>
        constexpr bool operator>(const Pressure<IncommingUnit> &other)
        {
            return _value > other.convertTo(BaseUnit);
        }
    };

}   // namespace ConvertX

#endif   // __PRESSURE_H__