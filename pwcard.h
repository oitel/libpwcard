#ifndef PWCARD_H
#define PWCARD_H

#include <cstdint>
#include <string>
#include <vector>

class PwCard
{
    uint64_t m_seed;

public:
    explicit PwCard(uint64_t seed);

    std::vector<std::string> generate() const;
};

#endif // PWCARD_H
