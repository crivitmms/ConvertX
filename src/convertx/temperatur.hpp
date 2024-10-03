#ifndef __TEMPERATUR_H__
#define __TEMPERATUR_H__

namespace ConvertX
{

    enum class TemperaturUnit
    {
        CELSIUS,
        KELVIN,
        FAHRENHEIT,
        RANKINE
    };

    template <TemperaturUnit BaseUnit = TemperaturUnit::KELVIN>
    class Temperatur
    {
        double _value = 0;
        constexpr double convertToKelvin() const
        {
            switch (BaseUnit)
            {
            case TemperaturUnit::CELSIUS: return _value + 273.15;
            case TemperaturUnit::KELVIN: return _value;
            case TemperaturUnit::FAHRENHEIT: return (_value - 32) * 5 / 9 + 273.15;
            case TemperaturUnit::RANKINE: return _value * 5 / 9;
            default:
                throw std::runtime_error("not a conversion unit");
                // std::unreachable();
            }
        }
        constexpr double convertToKelvinDiff() const
        {
            switch (BaseUnit)
            {
            case TemperaturUnit::CELSIUS: return _value;
            case TemperaturUnit::KELVIN: return _value;
            case TemperaturUnit::FAHRENHEIT: return (_value) * 5 / 9;
            case TemperaturUnit::RANKINE: return _value * 5 / 9;
            default:
                throw std::runtime_error("not a conversion unit");
                // std::unreachable();
            }
        }

    public:
        constexpr double convertToDiff(const TemperaturUnit unit) const
        {
            if (unit == BaseUnit)
                return _value;
            switch (unit)
            {
            case TemperaturUnit::CELSIUS: return convertToKelvinDiff();
            case TemperaturUnit::KELVIN: return convertToKelvinDiff();
            case TemperaturUnit::FAHRENHEIT: return convertToKelvinDiff() * 9 / 5;
            case TemperaturUnit::RANKINE: return convertToKelvinDiff() * 9 / 5;
            default:
                throw std::runtime_error("not a conversion unit");
                // std::unreachable();
            }
        }

        constexpr double convertTo(const TemperaturUnit unit) const
        {
            if (unit == BaseUnit)
                return _value;
            switch (unit)
            {
            case TemperaturUnit::CELSIUS: return convertToKelvin() - 273.15;
            case TemperaturUnit::KELVIN: return convertToKelvin();
            case TemperaturUnit::FAHRENHEIT: return (convertToKelvin() - 273.15) * 9 / 5 + 32;
            case TemperaturUnit::RANKINE: return convertToKelvin() * 9 / 5;
            default:
                throw std::runtime_error("not a conversion unit");
                // std::unreachable();
            }
        }

        constexpr Temperatur(double value = 0) :
            _value(value) {};

        template <TemperaturUnit IncommingUnit>
        constexpr Temperatur(const Temperatur<IncommingUnit> rhs) :
            _value(rhs.convertTo(BaseUnit))
        {
        }

        constexpr double getvalue() const
        {
            return _value;
        }

        constexpr TemperaturUnit getUnitType() const
        {
            return BaseUnit;
        }

        template <TemperaturUnit IncommingUnit>
        constexpr Temperatur<BaseUnit> &operator=(const Temperatur<IncommingUnit> &other)
        {
            _value = other.convertTo(BaseUnit);
            return *this;
        }
        template <typename T>
        constexpr Temperatur<BaseUnit> &operator=(const T &other)
        {
            _value = other;
            return *this;
        }

        template <TemperaturUnit IncommingUnit>
        constexpr Temperatur<BaseUnit> &operator+=(const Temperatur<IncommingUnit> &other)
        {
            _value += other.convertToDiff(BaseUnit);
            return *this;
        }
        template <typename T>
        constexpr Temperatur<BaseUnit> &operator+=(const T other)
        {
            _value += other;
            return *this;
        }

        template <TemperaturUnit IncommingUnit>
        constexpr Temperatur<BaseUnit> operator+(const Temperatur<IncommingUnit> &other)
        {
            return Temperatur<BaseUnit>(_value + other.convertToDiff(BaseUnit));
        }
        template <typename T>
        constexpr Temperatur<BaseUnit> operator+(const T other)
        {
            return Temperatur<BaseUnit>(_value + other);
        }

        template <TemperaturUnit IncommingUnit>
        constexpr Temperatur<BaseUnit> &operator-=(const Temperatur<IncommingUnit> &other)
        {
            _value -= other.convertToDiff(BaseUnit);
            return *this;
        }
        template <typename T>
        constexpr Temperatur<BaseUnit> &operator-=(const T other)
        {
            _value -= other;
            return *this;
        }

        template <TemperaturUnit IncommingUnit>
        constexpr Temperatur<BaseUnit> operator-(const Temperatur<IncommingUnit> &other)
        {
            return Temperatur<BaseUnit>(_value - other.convertToDiff(BaseUnit));
        }
        template <typename T>
        constexpr Temperatur<BaseUnit> operator-(const T other)
        {
            return Temperatur<BaseUnit>(_value - other);
        }

        template <typename T>
        constexpr Temperatur<BaseUnit> operator*=(const T other)
        {
            _value *= other;
            return *this;
        }
        template <typename T>
        constexpr Temperatur<BaseUnit> operator*(const T other)
        {
            return Temperatur<BaseUnit>(_value * other);
        }

        template <typename T>
        constexpr Temperatur<BaseUnit> operator/=(const T other)
        {
            _value /= other;
            return *this;
        }

        template <typename T>
        constexpr Temperatur<BaseUnit> operator/(const T other)
        {
            return Temperatur<BaseUnit>(_value / other);
        }

        template <typename T>
        constexpr Temperatur<BaseUnit> operator%=(const T other)
        {
            _value = fmod(_value, other);
            return *this;
        }

        template <typename T>
        constexpr Temperatur<BaseUnit> operator%(const T other)
        {
            return Temperatur<BaseUnit>(fmod(_value, other));
        }

        constexpr Temperatur<BaseUnit> &operator++()
        {
            _value++;
            return *this;
        }
        constexpr Temperatur<BaseUnit> operator++(int)
        {
            Temperatur<BaseUnit> old = *this;
            _value++;
            return old;
        }

        template <TemperaturUnit IncommingUnit>
        constexpr bool operator<(const Temperatur<IncommingUnit> &other)
        {
            return _value < other.convertTo(BaseUnit);
        }
        template <TemperaturUnit IncommingUnit>
        constexpr bool operator>(const Temperatur<IncommingUnit> &other)
        {
            return _value > other.convertTo(BaseUnit);
        }

        template <typename T>
        constexpr bool operator<(const T other)
        {
            return _value < other;
        }
        template <typename T>
        constexpr bool operator>(const T other)
        {
            return _value > other;
        }

        template <typename T>
        constexpr bool equal(const T &other, const T &maxdiff = std::numeric_limits<T>::epsilon()) const
        {
            return std::abs(_value - other) <= maxdiff;
        }

        template <TemperaturUnit IncomingUnit>
        constexpr bool equal(const Temperatur<IncomingUnit> &other, const double maxdiff = std::numeric_limits<double>::epsilon()) const
        {
            return std::abs(_value - other.convertTo(BaseUnit)) <= maxdiff;
        }

    };

}   // namespace ConvertX
#endif   // __TEMPERATUR_H__