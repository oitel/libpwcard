#ifndef UNIFORM_INT_DISTRIBUTION_H
#define UNIFORM_INT_DISTRIBUTION_H

#include "linear_congruential_engine.h"

#include <cstdint>

class uniform_int_distribution
{
public:
    using result_type = int32_t;

    class param_type
    {
        friend class uniform_int_distribution;
        result_type a, b;

    public:
        param_type(result_type a, result_type b);
    };

    uniform_int_distribution();

    result_type operator ()(linear_congruential_engine &g, const param_type &param) const;
};

#endif // UNIFORM_INT_DISTRIBUTION_H
