#include "linear_congruential_engine.h"

linear_congruential_engine::linear_congruential_engine(result_type seed)
    : m_seed((seed ^ A) & M)
{}

linear_congruential_engine::result_type linear_congruential_engine::operator ()()
{
    m_seed = (m_seed * A + C) & M;
    return m_seed;
}
