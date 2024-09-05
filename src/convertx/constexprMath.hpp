#ifndef __CONSTEXPRMATH_H__
#define __CONSTEXPRMATH_H__

namespace ConvertX
{
    namespace Math
    {

        constexpr double constexpr_pow(double base, int exp)
        {
            if (exp == 0)
            {
                return 1.0;
            }
            else if (exp > 0)
            {
                double result = 1.0;
                for (int i = 0; i < exp; ++i)
                {
                    result *= base;
                }
                return result;
            }
            else
            {
                double result = 1.0;
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