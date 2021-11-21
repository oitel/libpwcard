#ifndef SHUFFLE_H
#define SHUFFLE_H

#include "linear_congruential_engine.h"
#include "uniform_int_distribution.h"

#include <algorithm>

template <class RandomIt>
void shuffle(RandomIt first, RandomIt last, linear_congruential_engine &g)
{
    uniform_int_distribution D;
    using param = uniform_int_distribution::param_type;

    auto n = std::distance(first, last);
    for (auto i = n - 1; i > 0; --i) {
        auto j = D(g, param(0, i));
        std::swap(first[i], first[j]);
    }
}

#endif // SHUFFLE_H
