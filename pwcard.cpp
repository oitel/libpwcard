#include "pwcard.h"
#include "shuffle.h"

#include <unordered_map>

PwCard PwCard::generate(seed_type seed, int options)
{
    PwCard result;

    linear_congruential_engine g(seed);

    static const std::array<symbol_type, column_count> init_header = {
        0xE0, 0xE1, 0xE2, 0xE3, 0xE4, 0xE5, 0xE6, 0xE7,
        0xE8, 0xE9, 0xEA, 0xEB, 0xEC, 0xED, 0xEE, 0xEF,
        0xF0, 0xF1, 0xF2, 0xF3, 0xF4, 0xF5, 0xF6, 0xF7,
        0xF8, 0xF9, 0xFA, 0xFB, 0xFC,
    };
    result.header = init_header;
    shuffle(result.header.begin(), result.header.end(), g);

    static const std::array<symbol_type, 76> init_symbols = {
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
        0x3F, 0xF1, 0x2B, 0x7B, 0x7D, 0x5B, 0x5D, 0x28,
        0x29, 0x2F, 0x5C,
    };
    uniform_int_distribution D;
    uniform_int_distribution::param_type
            default_params(2, 56),
            only_digits_params(0, 9),
            include_symbols_params(2, 75);

    for (auto r = 0u; r < row_count; ++r) {
        auto &row = result.rows[r];

        for (auto c = 0u; c < column_count; ++c) {
            auto &symbol = row[c];

            auto params = default_params;
            if (r >= 4 && (options & area_with_only_digits))
                params = only_digits_params;
            else if (c % 2 == 0 && (options & include_symbols))
                params = include_symbols_params;

            auto i = D(g, params);
            symbol = init_symbols[i];
        }
    }

    return result;
}

const char *PwCard::to_utf8(symbol_type symbol)
{
    static const std::unordered_map<symbol_type, const char *> symbol_map {
                                               {0x23, "#"}, {0x24, "$"}, {0x25, "%"}, {0x26, "&"},
        {0x28, "("}, {0x29, ")"}, {0x2A, "*"}, {0x2B, "+"},                                        {0x2F, "/"},
        {0x30, "0"}, {0x31, "1"}, {0x32, "2"}, {0x33, "3"}, {0x34, "4"}, {0x35, "5"}, {0x36, "6"}, {0x37, "7"},
        {0x38, "8"}, {0x39, "9"},                           {0x3C, "<"},              {0x3E, ">"}, {0x3F, "?"},
        {0x40, "@"}, {0x41, "A"}, {0x42, "B"}, {0x43, "C"}, {0x44, "D"}, {0x45, "E"}, {0x46, "F"}, {0x47, "G"},
        {0x48, "H"},              {0x4A, "J"}, {0x4B, "K"}, {0x4C, "L"}, {0x4D, "M"}, {0x4E, "N"},
        {0x50, "P"}, {0x51, "Q"}, {0x52, "R"}, {0x53, "S"}, {0x54, "T"}, {0x55, "U"}, {0x56, "V"}, {0x57, "W"},
        {0x58, "X"}, {0x59, "Y"}, {0x5A, "Z"}, {0x5B, "["}, {0x5C, "\\"},{0x5D, "]"},
                     {0x61, "a"}, {0x62, "b"}, {0x63, "c"}, {0x64, "d"}, {0x65, "e"}, {0x66, "f"}, {0x67, "g"},
        {0x68, "h"},              {0x6A, "j"}, {0x6B, "k"},              {0x6D, "m"}, {0x6E, "n"},
        {0x70, "p"}, {0x71, "q"}, {0x72, "r"}, {0x73, "s"}, {0x74, "t"}, {0x75, "u"}, {0x76, "v"}, {0x77, "w"},
        {0x78, "x"}, {0x79, "y"}, {0x7A, "z"}, {0x7B, "{"},              {0x7D, "}"},
        {0xE0, "■"}, {0xE1, "□"}, {0xE2, "▲"}, {0xE3, "△"}, {0xE4, "○"}, {0xE5, "●"}, {0xE6, "★"}, {0xE7, "☂"},
        {0xE8, "☀"}, {0xE9, "☁"}, {0xEA, "☹"}, {0xEB, "☺"}, {0xEC, "♠"}, {0xED, "♣"}, {0xEE, "♥"}, {0xEF, "♦"},
        {0xF0, "♫"}, {0xF1, "€"}, {0xF2, "¥"}, {0xF3, "£"}, {0xF4, "$"}, {0xF5, "!"}, {0xF6, "?"}, {0xF7, "¡"},
        {0xF8, "¿"}, {0xF9, "⊙"}, {0xFA, "◐"}, {0xFB, "◩"}, {0xFC, "�"},
    };
    auto it = symbol_map.find(symbol);
    return it != symbol_map.end() ? it->second : "\0";
}

char16_t PwCard::to_utf16(symbol_type symbol)
{
    static const std::unordered_map<symbol_type, char16_t> symbol_map {
                                                  {0x23, u'#'}, {0x24, u'$'}, {0x25, u'%'}, {0x26, u'&'},
        {0x28, u'('}, {0x29, u')'}, {0x2A, u'*'}, {0x2B, u'+'},                                           {0x2F, u'/'},
        {0x30, u'0'}, {0x31, u'1'}, {0x32, u'2'}, {0x33, u'3'}, {0x34, u'4'}, {0x35, u'5'}, {0x36, u'6'}, {0x37, u'7'},
        {0x38, u'8'}, {0x39, u'9'},                             {0x3C, u'<'},               {0x3E, u'>'}, {0x3F, u'?'},
        {0x40, u'@'}, {0x41, u'A'}, {0x42, u'B'}, {0x43, u'C'}, {0x44, u'D'}, {0x45, u'E'}, {0x46, u'F'}, {0x47, u'G'},
        {0x48, u'H'},               {0x4A, u'J'}, {0x4B, u'K'}, {0x4C, u'L'}, {0x4D, u'M'}, {0x4E, u'N'},
        {0x50, u'P'}, {0x51, u'Q'}, {0x52, u'R'}, {0x53, u'S'}, {0x54, u'T'}, {0x55, u'U'}, {0x56, u'V'}, {0x57, u'W'},
        {0x58, u'X'}, {0x59, u'Y'}, {0x5A, u'Z'}, {0x5B, u'['}, {0x5C, u'\\'},{0x5D, u']'},
                      {0x61, u'a'}, {0x62, u'b'}, {0x63, u'c'}, {0x64, u'd'}, {0x65, u'e'}, {0x66, u'f'}, {0x67, u'g'},
        {0x68, u'h'},               {0x6A, u'j'}, {0x6B, u'k'},               {0x6D, u'm'}, {0x6E, u'n'},
        {0x70, u'p'}, {0x71, u'q'}, {0x72, u'r'}, {0x73, u's'}, {0x74, u't'}, {0x75, u'u'}, {0x76, u'v'}, {0x77, u'w'},
        {0x78, u'x'}, {0x79, u'y'}, {0x7A, u'z'}, {0x7B, u'{'},               {0x7D, u'}'},
        {0xE0, u'■'}, {0xE1, u'□'}, {0xE2, u'▲'}, {0xE3, u'△'}, {0xE4, u'○'}, {0xE5, u'●'}, {0xE6, u'★'}, {0xE7, u'☂'},
        {0xE8, u'☀'}, {0xE9, u'☁'}, {0xEA, u'☹'}, {0xEB, u'☺'}, {0xEC, u'♠'}, {0xED, u'♣'}, {0xEE, u'♥'}, {0xEF, u'♦'},
        {0xF0, u'♫'}, {0xF1, u'€'}, {0xF2, u'¥'}, {0xF3, u'£'}, {0xF4, u'$'}, {0xF5, u'!'}, {0xF6, u'?'}, {0xF7, u'¡'},
        {0xF8, u'¿'}, {0xF9, u'⊙'}, {0xFA, u'◐'}, {0xFB, u'◩'}, {0xFC, u'�'},
    };
    auto it = symbol_map.find(symbol);
    return it != symbol_map.end() ? it->second : u'\0';
}

std::string PwCard::to_utf8(const line_type &line)
{
    std::string result;
    result.reserve(line.size());
    for (auto &&symbol : line)
        result.append(to_utf8(symbol));
    return result;
}

std::u16string PwCard::to_utf16(const line_type &line)
{
    std::u16string result(line.size(), u'\0');
    for (auto i = 0u; i < line.size(); ++i)
        result[i] = to_utf16(line[i]);
    return result;
}
