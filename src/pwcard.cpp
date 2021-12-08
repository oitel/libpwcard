#include "pwcard/pwcard.h"
#include "shuffle.h"

PwCard PwCard::generate(seed_type seed, int options)
{
    PwCard result;

    linear_congruential_engine g(seed);

    static constexpr std::array<symbol_type, column_count> init_header = {
        0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87,
        0x88, 0x89, 0x8A, 0x8B, 0x8C, 0x8D, 0x8E, 0x8F,
        0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97,
        0x98, 0x99, 0x9A, 0x9B, 0x9C,
    };
    result.header = init_header;
    shuffle(result.header.begin(), result.header.end(), g);

    static constexpr std::array<symbol_type, 76> init_symbols = {
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
    static constexpr size_t snippet_size = 4;
    #define _______ "\0\0\0\0"
    #define B1(S) S "\0\0\0"
    #define B2(S) S "\0\0"
    #define B3(S) S "\0"
    static constexpr char code_page[] =
        _______ _______ _______ B1("#") B1("$") B1("%") B1("&") _______
        B1("(") B1(")") B1("*") B1("+") _______ _______ _______ B1("/")
        B1("0") B1("1") B1("2") B1("3") B1("4") B1("5") B1("6") B1("7")
        B1("8") B1("9") _______ _______ B1("<") _______ B1(">") B1("?")
        B1("@") B1("A") B1("B") B1("C") B1("D") B1("E") B1("F") B1("G")
        B1("H") _______ B1("J") B1("K") B1("L") B1("M") B1("N") _______
        B1("P") B1("Q") B1("R") B1("S") B1("T") B1("U") B1("V") B1("W")
        B1("X") B1("Y") B1("Z") B1("[") B1("\\")B1("]") _______ _______
        _______ B1("a") B1("b") B1("c") B1("d") B1("e") B1("f") B1("g")
        B1("h") _______ B1("j") B1("k") _______ B1("m") B1("n") _______
        B1("p") B1("q") B1("r") B1("s") B1("t") B1("u") B1("v") B1("w")
        B1("x") B1("y") B1("z") B1("{") _______ B1("}") _______ _______
        B3("■") B3("□") B3("▲") B3("△") B3("○") B3("●") B3("★") B3("☂")
        B3("☀") B3("☁") B3("☹") B3("☺") B3("♠") B3("♣") B3("♥") B3("♦")
        B3("♫") B3("€") B2("¥") B2("£") B1("$") B1("!") B1("?") B2("¡")
        B2("¿") B3("⊙") B3("◐") B3("◩") B3("�") _______ _______ _______
    ;
    #undef B3
    #undef B2
    #undef B1
    #undef ____
    static_assert(sizeof(code_page) == 128 * snippet_size + 1, "code page has invalid size");
    return code_page + snippet_size * (symbol - 0x20);
}

char16_t PwCard::to_utf16(symbol_type symbol)
{
    #define ____ u'\0'
    static constexpr std::array<char16_t, 128> code_page {
        ____, ____, ____, u'#', u'$', u'%', u'&', ____,
        u'(', u')', u'*', u'+', ____, ____, ____, u'/',
        u'0', u'1', u'2', u'3', u'4', u'5', u'6', u'7',
        u'8', u'9', ____, ____, u'<', ____, u'>', u'?',
        u'@', u'A', u'B', u'C', u'D', u'E', u'F', u'G',
        u'H', ____, u'J', u'K', u'L', u'M', u'N', ____,
        u'P', u'Q', u'R', u'S', u'T', u'U', u'V', u'W',
        u'X', u'Y', u'Z', u'[', u'\\',u']', ____, ____,
        ____, u'a', u'b', u'c', u'd', u'e', u'f', u'g',
        u'h', ____, u'j', u'k', ____, u'm', u'n', ____,
        u'p', u'q', u'r', u's', u't', u'u', u'v', u'w',
        u'x', u'y', u'z', u'{', ____, u'}', ____, ____,
        u'■', u'□', u'▲', u'△', u'○', u'●', u'★', u'☂',
        u'☀', u'☁', u'☹', u'☺', u'♠', u'♣', u'♥', u'♦',
        u'♫', u'€', u'¥', u'£', u'$', u'!', u'?', u'¡',
        u'¿', u'⊙', u'◐', u'◩', u'�', ____, ____, ____,
    };
    #undef ____
    return code_page[symbol - 0x20];
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
