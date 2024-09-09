#ifndef __BYTESIZE_H__
#define __BYTESIZE_H__

#include "constexprMath.hpp"
#include "memory"

namespace ConvertX
{

    enum class DataUnit
    {
        BITS,
        NIBBLE,
        BYTES,
        KILOBYTES,
        MEGABYTES,
        GIGABYTES,
        TERABYTES,
        PETABYTES,
        EXABYTES,
        ZETTABYTES,
        YOTTABYTES
    };

    template <DataUnit BaseUnit = DataUnit::BYTES>
    class DataSize
    {
        double _value = 0;

        constexpr double convertToByte() const
        {
            switch (BaseUnit)
            {
            case DataUnit::BITS: return _value / 8;
            case DataUnit::NIBBLE: return _value / 4;
            case DataUnit::BYTES: return _value;
            case DataUnit::KILOBYTES: return _value * 1024.0;
            case DataUnit::MEGABYTES: return _value * Math::constexpr_pow(1024.0, 2);
            case DataUnit::GIGABYTES: return _value * Math::constexpr_pow(1024.0, 3);
            case DataUnit::TERABYTES: return _value * Math::constexpr_pow(1024.0, 4);
            case DataUnit::PETABYTES: return _value * Math::constexpr_pow(1024.0, 5);
            case DataUnit::EXABYTES: return _value * Math::constexpr_pow(1024.0, 6);
            case DataUnit::ZETTABYTES: return _value * Math::constexpr_pow(1024.0, 7);
            case DataUnit::YOTTABYTES: return _value * Math::constexpr_pow(1024.0, 8);
            default:
                throw std::runtime_error("not a conversion unit");
                // std::unreachable();
            }
        }

    public:
        constexpr double convertTo(const DataUnit unit) const
        {
            if (unit == BaseUnit)
                return _value;
            switch (unit)
            {
            case DataUnit::BITS: return convertToByte() * 8;
            case DataUnit::NIBBLE: return convertToByte() * 4;
            case DataUnit::BYTES: return convertToByte();
            case DataUnit::KILOBYTES: return convertToByte() / 1024.0;
            case DataUnit::MEGABYTES: return convertToByte() / Math::constexpr_pow(1024.0, 2);
            case DataUnit::GIGABYTES: return convertToByte() / Math::constexpr_pow(1024.0, 3);
            case DataUnit::TERABYTES: return convertToByte() / Math::constexpr_pow(1024.0, 4);
            case DataUnit::PETABYTES: return convertToByte() / Math::constexpr_pow(1024.0, 5);
            case DataUnit::EXABYTES: return convertToByte() / Math::constexpr_pow(1024.0, 6);
            case DataUnit::ZETTABYTES: return convertToByte() / Math::constexpr_pow(1024.0, 7);
            case DataUnit::YOTTABYTES: return convertToByte() / Math::constexpr_pow(1024.0, 8);
            default:
                throw std::runtime_error("not a conversion unit");
                // std::unreachable();
            }
        }

        constexpr DataSize(double value = 0) :
            _value(value) {};

        template <DataUnit IncommingUnit>
        constexpr DataSize(const DataSize<IncommingUnit> rhs) :
            _value(rhs.convertTo(BaseUnit))
        {
        }

        constexpr double getvalue() const
        {
            return _value;
        }

        constexpr DataUnit getUnitType() const
        {
            return BaseUnit;
        }

        template <DataUnit IncommingUnit>
        constexpr DataSize<BaseUnit> &operator=(const DataSize<IncommingUnit> &other)
        {
            _value = other.convertTo(BaseUnit);
            return *this;
        }
        template <typename T>
        constexpr DataSize<BaseUnit> &operator=(const T &other)
        {
            _value = other;
            return *this;
        }

        template <DataUnit IncommingUnit>
        constexpr DataSize<BaseUnit> &operator+=(const DataSize<IncommingUnit> &other)
        {
            _value += other.convertTo(BaseUnit);
            return *this;
        }
        template <typename T>
        constexpr DataSize<BaseUnit> &operator+=(const T other)
        {
            _value += other;
            return *this;
        }

        template <DataUnit IncommingUnit>
        constexpr DataSize<BaseUnit> operator+(const DataSize<IncommingUnit> &other)
        {
            return DataSize<BaseUnit>(_value + other.convertTo(BaseUnit));
        }
        template <typename T>
        constexpr DataSize<BaseUnit> operator+(const T other)
        {
            return DataSize<BaseUnit>(_value + other);
        }

        template <DataUnit IncommingUnit>
        constexpr DataSize<BaseUnit> &operator-=(const DataSize<IncommingUnit> &other)
        {
            _value -= other.convertTo(BaseUnit);
            return *this;
        }
        template <typename T>
        constexpr DataSize<BaseUnit> &operator-=(const T other)
        {
            _value -= other;
            return *this;
        }

        template <DataUnit IncommingUnit>
        constexpr DataSize<BaseUnit> operator-(const DataSize<IncommingUnit> &other)
        {
            return DataSize<BaseUnit>(_value - other.convertTo(BaseUnit));
        }
        template <typename T>
        constexpr DataSize<BaseUnit> operator-(const T other)
        {
            return DataSize<BaseUnit>(_value - other);
        }

        template <typename T>
        constexpr DataSize<BaseUnit> operator*=(const T other)
        {
            _value *= other;
            return *this;
        }

        template <typename T>
        constexpr DataSize<BaseUnit> operator*(const T other)
        {
            return DataSize<BaseUnit>(_value * other);
        }

        template <typename T>
        constexpr DataSize<BaseUnit> operator/=(const T other)
        {
            _value /= other;
            return *this;
        }

        template <typename T>
        constexpr DataSize<BaseUnit> operator/(const T other)
        {
            return DataSize<BaseUnit>(_value / other);
        }

        template <DataUnit IncommingUnit>
        constexpr DataSize<BaseUnit> operator%=(const DataSize<IncommingUnit> &other)
        {
            _value %= other.convertTo(BaseUnit);
            return *this;
        }
        template <typename T>
        constexpr DataSize<BaseUnit> operator%=(const T other)
        {
            _value = fmod(_value, other);
            return *this;
        }

        template <DataUnit IncommingUnit>
        constexpr DataSize<BaseUnit> operator%(const DataSize<IncommingUnit> &other)
        {
            return DataSize<BaseUnit>(_value % other.convertTo(BaseUnit));
        }
        template <typename T>
        constexpr DataSize<BaseUnit> operator%(const T other)
        {
            return DataSize<BaseUnit>(fmod(_value, other));
        }

        constexpr DataSize<BaseUnit> &operator++()
        {
            _value++;
            return *this;
        }
        constexpr DataSize<BaseUnit> operator++(int)
        {
            DataSize<BaseUnit> old = *this;
            _value++;
            return old;
        }
    };

#ifndef NO_LITERALS

#define DEFINE_DATASIZE_LITERAL(Unit, Suffix)                                                                                                        \
    constexpr DataSize<DataUnit::Unit> operator""_##Suffix(long double value)                                                                        \
    {                                                                                                                                                \
        return DataSize<DataUnit::Unit>(value);                                                                                                      \
    }                                                                                                                                                \
    constexpr DataSize<DataUnit::Unit> operator""_##Suffix(unsigned long long value)                                                                 \
    {                                                                                                                                                \
        return DataSize<DataUnit::Unit>(value);                                                                                                      \
    }

    DEFINE_DATASIZE_LITERAL(BITS, bits)
    DEFINE_DATASIZE_LITERAL(NIBBLE, nibble)
    DEFINE_DATASIZE_LITERAL(BYTES, bytes)
    DEFINE_DATASIZE_LITERAL(KILOBYTES, kib)
    DEFINE_DATASIZE_LITERAL(MEGABYTES, mib)
    DEFINE_DATASIZE_LITERAL(GIGABYTES, gib)
    DEFINE_DATASIZE_LITERAL(TERABYTES, tib)
    DEFINE_DATASIZE_LITERAL(PETABYTES, pib)
    DEFINE_DATASIZE_LITERAL(EXABYTES, eib)
    DEFINE_DATASIZE_LITERAL(ZETTABYTES, zib)
    DEFINE_DATASIZE_LITERAL(YOTTABYTES, yib)

#undef DEFINE_DATASIZE_LITERAL

#endif

}   // namespace ConvertX

#endif   // __BYTESIZE_H__