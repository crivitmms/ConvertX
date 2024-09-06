#ifndef __CONSTEXPRMATH_H__
#define __CONSTEXPRMATH_H__

namespace ConvertX
{
    namespace Math
    {

        template<typename T>
        constexpr inline T constexpr_pow(T base, int exp)
        {
            if (exp == 0)
            {
                return 1.0;
            }
            else if (exp > 0)
            {
                T result = 1.0;
                for (int i = 0; i < exp; ++i)
                {
                    result *= base;
                }
                return result;
            }
            else
            {
                T result = 1.0;
                for (int i = 0; i < -exp; ++i)
                {
                    result *= base;
                }
                return 1.0 / result;
            }
        }
    }   // namespace math
}   // namespace ConvertX

#endif   // __CONSTEXPRMATH_H__