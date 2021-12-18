#define CATCH_CONFIG_MAIN
#include <catch2/catch.hpp>

#include <pwcard/pwcard.h>

TEST_CASE("Conversion to text")
{
    SECTION("UTF-8")
    {
        REQUIRE(PwCard::to_utf8(0x30)[0] == '0');
    }

    SECTION("UTF-16")
    {
        REQUIRE(PwCard::to_utf16(0x30) == u'0');
    }
}
