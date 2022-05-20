/*
 * Copyright (c) 2021-2022 Artur Sharafutdinov
 * Licensed under the MIT license. See LICENSE file for details.
 */

/**
 * @file PasswordCard generation library
 *
 * libpwcard is a library for generating PasswordCards from https://www.passwordcard.org/
 * The algorithm is defined at https://www.passwordcard.org/algorithm.html
 */

#ifndef PWCARD_H
#define PWCARD_H

#include <array>
#include <cstdint>
#include <string>

/**
 * @brief Card header and grid
 *
 * Symbols (in both header and grid) are encoded with single-byte code page.
 * Use methods `to_utf8` and `to_utf16` to convert symbols to readable characters.
 */
struct PwCard
{
    static constexpr size_t column_count = 29;
    static constexpr size_t row_count = 8;

    using symbol_type = uint8_t;
    using line_type = std::array<symbol_type, column_count>;

    /**
     * @brief Header symbol line
     */
    line_type header;
    /**
     * @brief Grid symbol lines
     */
    std::array<line_type, row_count> rows;

    /**
     * @brief Card generation option flags.
     */
    enum options {
        /**  */
        none = 0x0,
        /** Use only digits for lower half of a card */
        area_with_only_digits = 0x1,
        /** Use non-alphanumeric symbols for even columns*/
        include_symbols = 0x2,
    };

    using seed_type = uint64_t;
    /**
     * @brief Generate card.
     *
     * @param seed card number
     * @param options generation options
     * @return generated card
     */
    static PwCard generate(seed_type seed, int options = none);

    /**
     * @brief Convert symbol code to null-terminated UTF-8 sequence.
     *
     * The sequences are static and must not be freed after use.
     * Unsupported symbol codes refers to NUL.
     *
     * @param symbol symbol code
     * @return UTF-8 sequence
     */
    static const char *to_utf8(symbol_type symbol);
    /**
     * @brief Convert symbol code to UTF-16 code point.
     *
     * Unsupported symbol codes refers to NUL.
     *
     * @param symbol symbol code
     * @return UTF-16 code point
     */
    static char16_t to_utf16(symbol_type symbol);

    /**
     * @brief Convert symbol line to UTF-8 string.
     *
     * Unsupported symbol codes will be omitted.
     *
     * @param line symbol line
     * @return UTF-8 string
     */
    static std::string to_utf8(const PwCard::line_type &line);
    /**
     * @brief Convert symbol line to UTF-16 string.
     *
     * Unsupported symbol codes will be converted to NUL.
     *
     * @param line symbol line
     * @return UTF-16 string
     */
    static std::u16string to_utf16(const PwCard::line_type &line);
};

#endif // PWCARD_H
