#include "pwcard.h"

#include <iostream>

int main(int argc, char *argv[])
{
    if (argc == 1) {
        std::cerr << "Usage: pwcard NUMBER" << std::endl;
        return EXIT_FAILURE;
    }

    PwCard::seed_type seed;
    try {
        seed = std::stoull(argv[1], nullptr, 16);
    } catch (const std::exception &exc) {
        std::cerr << exc.what() << std::endl;
        return EXIT_FAILURE;
    }

    const auto pwcard = PwCard::generate(seed);
    std::cout << PwCard::to_utf8(pwcard.header) << std::endl;
    for (auto &&row : pwcard.rows)
        std::cout << PwCard::to_utf8(row) << std::endl;

    return EXIT_SUCCESS;
}
