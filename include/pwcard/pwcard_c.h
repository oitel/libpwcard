#ifndef PWCARD_C_H
#define PWCARD_C_H

#include <stdint.h>
#include <uchar.h>

#define PWCARD_COLUMN_COUNT 29
#define PWCARD_ROW_COUNT 8

typedef uint8_t pwcard_symbol_t;
typedef pwcard_symbol_t pwcard_line_t[PWCARD_COLUMN_COUNT];
typedef pwcard_line_t pwcard_table_t[PWCARD_ROW_COUNT];

#define PWCARD_AREA_WITH_ONLY_DIGITS 0x1
#define PWCARD_INCLUDE_SYMBOLS 0x2

void pwcard_generate(pwcard_line_t *header, pwcard_table_t *table, uint64_t seed, int options);

const char *pwcard_symbol_to_utf8(pwcard_symbol_t sym);
char16_t pwcard_symbol_to_utf16(pwcard_symbol_t sym);

size_t pwcard_line_utf8_length(const pwcard_symbol_t *src, size_t count);
void pwcard_line_to_utf8(char *dest, const pwcard_symbol_t *src, size_t count);
void pwcard_line_to_utf16(char16_t *dest, const pwcard_symbol_t *src, size_t count);

#endif // PWCARD_C_H
