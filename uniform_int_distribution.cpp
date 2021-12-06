#include "uniform_int_distribution.h"

uniform_int_distribution::param_type::param_type(result_type a, result_type b)
    : a(a)
    , b(b)
{}

uniform_int_distribution::uniform_int_distribution()
{}

uniform_int_distribution::result_type uniform_int_distribution::operator ()(linear_congruential_engine &g, const param_type &param) const
{
    auto const n = param.b - param.a + 1;
    if ((n & -n) == n) { // checks if n is power of 2
        return (static_cast<int64_t>(n) * (result_type)(g() >> 17)) >> 31;
    }
    result_type bits, val;
    do {
        bits = (result_type)(g() >> 17);
        val = bits % n;
    } while (bits - val + (n - 1) < 0); // checks integer overflow to provide uniform distribution
    return val + param.a;
}
