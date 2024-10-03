#ifndef __LENGTH_H__
#define __LENGTH_H__

#include "constexprMath.hpp"

#include "cmath"
#include <stdexcept>
#include <utility>

namespace ConvertX
{

    enum class LengthUnit
    {
        FEMTOMETER,
        PICOMETER,
        NANOMETER,
        MICRON,
        MICROMETER,
        MILLIMETER,
        CENTIMETER,
        DECIMETER,
        METER,
        DECAMETER,
        HECTOMETER,
        KILOMETER,
        INCH,
        FEET,
        YARDS,
        MILE,
        NAUTICALMILES,
        LIGHTYEAR,
        ASTRONOMICALUNIT,
        PARSECS,
    };

    template <LengthUnit BaseUnit = LengthUnit::METER>
    class Length
    {
        double _value = 0;

        constexpr double convertToMeter() const
        {
            switch (BaseUnit)
            {
            case LengthUnit::FEMTOMETER: return _value * Math::constexpr_pow(10.0, -15);
            case LengthUnit::PICOMETER: return _value * 0.000'000'000'001;
            case LengthUnit::NANOMETER: return _value * 0.000'000'001;
            case LengthUnit::MICRON: [[fallthrough]];
            case LengthUnit::MICROMETER: return _value * 0.000'001;
            case LengthUnit::MILLIMETER: return _value * 0.001;
            case LengthUnit::CENTIMETER: return _value * 0.01;
            case LengthUnit::DECIMETER: return _value * 0.1;
            case LengthUnit::METER: return _value;
            case LengthUnit::DECAMETER: return _value * 10;
            case LengthUnit::HECTOMETER: return _value * 100;
            case LengthUnit::KILOMETER: return _value * 1000;
            case LengthUnit::INCH: return _value * 0.0254;
            case LengthUnit::FEET: return _value * 0.30480000000000217017600000001545;
            case LengthUnit::YARDS: return _value * 0.91440000000000651052800000004635;
            case LengthUnit::MILE: return _value * 1609.3440000000102812619571200657;
            case LengthUnit::NAUTICALMILES: return _value * 1852;
            case LengthUnit::LIGHTYEAR: return _value * 9.4607304725808 * Math::constexpr_pow(10.0, 15);
            case LengthUnit::ASTRONOMICALUNIT: return _value * 149597870691; ;
            case LengthUnit::PARSECS: return _value * 3.0856776 * Math::constexpr_pow(10.0, 16);
            default:
                throw std::runtime_error("not a conversion unit");
                // std::unreachable();
            }
        }

    public:
        constexpr double convertTo(const LengthUnit unit) const
        {
            if (unit == BaseUnit)
                return _value;
            switch (unit)
            {
            case LengthUnit::FEMTOMETER: return convertToMeter() * Math::constexpr_pow(10.0, 15);
            case LengthUnit::PICOMETER: return convertToMeter() * 1'000'000'000'000;
            case LengthUnit::NANOMETER: return convertToMeter() * 1'000'000'000;
            case LengthUnit::MICRON: [[fallthrough]];
            case LengthUnit::MICROMETER: return convertToMeter() * 1'000'000;
            case LengthUnit::MILLIMETER: return convertToMeter() * 1000;
            case LengthUnit::CENTIMETER: return convertToMeter() * 100;
            case LengthUnit::DECIMETER: return convertToMeter() * 10;
            case LengthUnit::METER: return convertToMeter();
            case LengthUnit::DECAMETER: return convertToMeter() * 0.1;
            case LengthUnit::HECTOMETER: return convertToMeter() * 0.01;
            case LengthUnit::KILOMETER: return convertToMeter() * 0.001;
            case LengthUnit::INCH: return convertToMeter() * 39.370078740157;
            case LengthUnit::FEET: return convertToMeter() * 3.2808398950131;
            case LengthUnit::YARDS: return convertToMeter() * 1.0936132983377;
            case LengthUnit::MILE: return convertToMeter() * 0.00062137119223733;
            case LengthUnit::NAUTICALMILES: return convertToMeter() * 0.00053995680345572354211663066954644;
            case LengthUnit::LIGHTYEAR: return convertToMeter() * 1.0570008340246 * Math::constexpr_pow(10.0, -16);
            case LengthUnit::ASTRONOMICALUNIT: return convertToMeter() * 6.6845871226706 * Math::constexpr_pow(10.0, -12);
            case LengthUnit::PARSECS: return convertToMeter() * 3.2407792700054 * Math::constexpr_pow(10.0, -17);
            default:
                throw std::runtime_error("not a conversion unit");
                // std::unreachable();
            }
        }

        constexpr Length(double value = 0) :
            _value(value) {};

        template <LengthUnit IncommingUnit>
        constexpr Length(const Length<IncommingUnit> rhs) :
            _value(rhs.convertTo(BaseUnit))
        {
        }

        constexpr double getvalue() const
        {
            return _value;
        }

        constexpr LengthUnit getUnitType() const
        {
            return BaseUnit;
        }

        template <LengthUnit IncommingUnit>
        constexpr Length<BaseUnit> &operator=(const Length<IncommingUnit> &other)
        {
            _value = other.convertTo(BaseUnit);
            return *this;
        }
        template <typename T>
        constexpr Length<BaseUnit> &operator=(const T &other)
        {
            _value = other;
            return *this;
        }

        template <LengthUnit IncommingUnit>
        constexpr Length<BaseUnit> &operator+=(const Length<IncommingUnit> &other)
        {
            _value += other.convertTo(BaseUnit);
            return *this;
        }
        template <typename T>
        constexpr Length<BaseUnit> &operator+=(const T other)
        {
            _value += other;
            return *this;
        }

        template <LengthUnit IncommingUnit>
        constexpr Length<BaseUnit> operator+(const Length<IncommingUnit> &other)
        {
            return Length<BaseUnit>(_value + other.convertTo(BaseUnit));
        }
        template <typename T>
        constexpr Length<BaseUnit> operator+(const T other)
        {
            return Length<BaseUnit>(_value + other);
        }

        template <LengthUnit IncommingUnit>
        constexpr Length<BaseUnit> &operator-=(const Length<IncommingUnit> &other)
        {
            _value -= other.convertTo(BaseUnit);
            return *this;
        }
        template <typename T>
        constexpr Length<BaseUnit> &operator-=(const T other)
        {
            _value -= other;
            return *this;
        }

        template <LengthUnit IncommingUnit>
        constexpr Length<BaseUnit> operator-(const Length<IncommingUnit> &other)
        {
            return Length<BaseUnit>(_value - other.convertTo(BaseUnit));
        }
        template <typename T>
        constexpr Length<BaseUnit> operator-(const T other)
        {
            return Length<BaseUnit>(_value - other);
        }

        template <typename T>
        constexpr Length<BaseUnit> operator*=(const T other)
        {
            _value *= other;
            return *this;
        }

        template <typename T>
        constexpr Length<BaseUnit> operator*(const T other)
        {
            return Length<BaseUnit>(_value * other);
        }

        template <typename T>
        constexpr Length<BaseUnit> operator/=(const T other)
        {
            _value /= other;
            return *this;
        }

        template <typename T>
        constexpr Length<BaseUnit> operator/(const T other)
        {
            return Length<BaseUnit>(_value / other);
        }

        template <LengthUnit IncommingUnit>
        constexpr Length<BaseUnit> operator%=(const Length<IncommingUnit> &other)
        {
            _value %= other.convertTo(BaseUnit);
            return *this;
        }
        template <typename T>
        constexpr Length<BaseUnit> operator%=(const T other)
        {
            _value = fmod(_value, other);
            return *this;
        }

        template <LengthUnit IncommingUnit>
        constexpr Length<BaseUnit> operator%(const Length<IncommingUnit> &other)
        {
            return Length<BaseUnit>(_value % other.convertTo(BaseUnit));
        }
        template <typename T>
        constexpr Length<BaseUnit> operator%(const T other)
        {
            return Length<BaseUnit>(fmod(_value, other));
        }

        constexpr Length<BaseUnit> &operator++()
        {
            _value++;
            return *this;
        }
        constexpr Length<BaseUnit> operator++(int)
        {
            Length<BaseUnit> old = *this;
            _value++;
            return old;
        }

        template <LengthUnit IncommingUnit>
        constexpr bool operator<(const Length<IncommingUnit> &other)
        {
            return _value < other.convertTo(BaseUnit);
        }
        template <LengthUnit IncommingUnit>
        constexpr bool operator>(const Length<IncommingUnit> &other)
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

        template <LengthUnit IncomingUnit>
        constexpr bool equal(const Length<IncomingUnit> &other, const double maxdiff = std::numeric_limits<double>::epsilon()) const
        {
            return std::abs(_value - other.convertTo(BaseUnit)) <= maxdiff;
        }
        
    };

}   // namespace ConvertX

#endif   // __LENGTH_H__