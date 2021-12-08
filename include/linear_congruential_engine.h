#ifndef LINEAR_CONGRUENTIAL_ENGINE_H
#define LINEAR_CONGRUENTIAL_ENGINE_H

#include <cstdint>

class linear_congruential_engine
{
public:
    using result_type = uint64_t;

    explicit linear_congruential_engine(result_type seed);

    result_type operator ()();

private:
    static constexpr result_type M = 0xffffffffffff;
    static constexpr result_type A = 0x0005deece66d;
    static constexpr result_type C = 0x00000000000b;

    result_type m_seed;
};

#endif // LINEAR_CONGRUENTIAL_ENGINE_H
