#ifndef PWCARD_H
#define PWCARD_H

#include <array>
#include <cstdint>
#include <string>
#include <vector>

struct PwCard
{
    static constexpr size_t column_count = 29;
    static constexpr size_t row_count = 8;

    using symbol_type = uint8_t;
    using line_type = std::array<symbol_type, column_count>;

    line_type header;
    std::array<line_type, row_count> rows;

    enum options {
        none = 0x0,
        area_with_only_digits = 0x1,
        include_symbols = 0x2,
    };

    using seed_type = uint64_t;
    static PwCard generate(seed_type seed, int options = none);

    static const char *to_utf8(symbol_type symbol);
    static char16_t to_utf16(symbol_type symbol);

    static std::string to_utf8(const PwCard::line_type &line);
    static std::u16string to_utf16(const PwCard::line_type &line);
};

#endif // PWCARD_H
