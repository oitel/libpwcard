#include "pwcard/pwcard.h"
extern "C" {
#include "pwcard/pwcard_c.h"
}
#include "linear_congruential_engine.h"
#include "shuffle.h"
#include "uniform_int_distribution.h"

#include <cstring>

void pwcard_generate(pwcard_line_t *header, pwcard_table_t *table, uint64_t seed, int options)
{
    linear_congruential_engine g(seed);

    static constexpr std::array<pwcard_symbol_t, PWCARD_COLUMN_COUNT> init_header = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87,
        0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F,
        0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97,
        0x98, 0x99, 0x9A, 0x9B, 0x9C,
    };
    std::memcpy(header, init_header.data(), init_header.size());
    shuffle(header, header + PWCARD_COLUMN_COUNT, g);

    static constexpr std::array<pwcard_symbol_t, 76> init_symbols = {
        0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
        0x38, 0x39,
              0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67,
        0x68,       0x6A, 0x6B,       0x6D, 0x6E,
        0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77,
        0x78, 0x79, 0x7A,
              0x41, 0x42, 0x43, 0x44, 0x45, 0x46, 0x47,
        0x48,       0x4A, 0x4B, 0x4C, 0x4D, 0x4E,
        0x50, 0x51, 0x52, 0x53, 0x54, 0x55, 0x56, 0x57,
        0x58, 0x59, 0x5A,
        0x40, 0x23, 0x24, 0x25, 0x26, 0x2A, 0x3C, 0x3E,
        0x3F, 0x91, 0x2B, 0x7B, 0x7D, 0x5B, 0x5D, 0x28,
        0x29, 0x2F, 0x5C,
    };
    static const uniform_int_distribution::param_type
            default_params(2, 56),
            only_digits_params(0, 9),
            include_symbols_params(2, 75);

    uniform_int_distribution D;
    for (auto r = 0u; r < PWCARD_ROW_COUNT; ++r) {
        auto *row = table[r];

        for (auto c = 0u; c < PWCARD_COLUMN_COUNT; ++c) {
            auto *symbol = row[c];

            auto params = default_params;
            if (r >= 4 && (options & PWCARD_AREA_WITH_ONLY_DIGITS))
                params = only_digits_params;
            else if (c % 2 == 0 && (options & PWCARD_INCLUDE_SYMBOLS))
                params = include_symbols_params;

            auto i = D(g, params);
            *symbol = init_symbols[i];
        }
    }
}

const char *pwcard_symbol_to_utf8(pwcard_symbol_t sym)
{
    return PwCard::to_utf8(sym);
}

char16_t pwcard_symbol_to_utf16(pwcard_symbol_t sym)
{
    return PwCard::to_utf16(sym);
}

size_t pwcard_line_utf8_length(const pwcard_symbol_t *src, size_t count)
{
    size_t length = 0;
    for (auto i = 0u; i < count; ++i) {
        auto snippet = PwCard::to_utf8(src[i]);
        length += std::strlen(snippet);
    }
    return length;
}

void pwcard_line_to_utf8(char *dest, const pwcard_symbol_t *src, size_t count)
{
    for (auto i = 0u; i < count; ++i) {
        auto snippet = PwCard::to_utf8(src[i]);
        auto length = std::strlen(snippet);
        strncpy(dest, snippet, length);
        dest += length;
    }
}
