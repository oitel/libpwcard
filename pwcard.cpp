#include "pwcard.h"
#include "shuffle.h"

PwCard::PwCard(uint64_t seed)
    : m_seed(seed)
{}

std::vector<std::string> PwCard::generate() const
{
    linear_congruential_engine g(m_seed);

    std::vector<std::string> lines;

    static const std::vector<std::string> init_header = {
        "■", "□", "▲", "△", "○", "●", "★", "☂", "☀", "☁", "☹", "☺", "♠", "♣",
        "♥", "♦", "♫", "€", "¥", "£", "$", "!", "?", "¡", "¿", "⊙", "◐", "◩", "�",
    };
    auto header = init_header;
    shuffle(header.begin(), header.end(), g);

    // ...
    std::string header_line;
    for (auto column = 0u; column < 29u; ++column)
        header_line.append(header[column]);
    lines.emplace_back(std::move(header_line));

    static std::vector<std::string> init_symbols = {
        "2", "3", "4", "5", "6", "7", "8", "9", "a", "b", "c", "d", "e", "f",
        "g", "h", "j", "k", "m", "n", "p", "q", "r", "s", "t", "u", "v", "w",
        "x", "y", "z", "A", "B", "C", "D", "E", "F", "G", "H", "J", "K", "L",
        "M", "N", "P", "Q", "R", "S", "T", "U", "V", "W", "X", "Y", "Z",
    };
    uniform_int_distribution D;
    uniform_int_distribution::param_type param(0, init_symbols.size() - 1);

    for (auto row = 0u; row < 8u; ++row) {
        std::string line;
        for (auto column = 0u; column < 29u; ++column) {
            auto i = D(g, param);
            line.append(init_symbols[i]);
        }
        lines.emplace_back(std::move(line));
    }

    return lines;
}
