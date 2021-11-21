#include "pwcard.h"

#include <iostream>

int main(int argc, char *argv[])
{
    if (argc == 1) {
        std::cerr << "Usage: pwcard NUMBER" << std::endl;
        return EXIT_FAILURE;
    }

    uint64_t seed;
    try {
        seed = std::stoull(argv[1], nullptr, 16);
    } catch (const std::exception &exc) {
        std::cerr << exc.what() << std::endl;
        return EXIT_FAILURE;
    }

    PwCard pwcard(seed);
    for (auto &&line : pwcard.generate())
        std::cout << line << std::endl;

    return EXIT_SUCCESS;
}
