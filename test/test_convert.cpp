#include <catch2/catch.hpp>

#include <pwcard/pwcard.h>

using namespace Catch::Matchers;

TEST_CASE("Conversion to text")
{
    SECTION("UTF-8")
    {
        REQUIRE(PwCard::to_utf8(0x30)[0] == '0');
        REQUIRE_THAT(PwCard::to_utf8(0x91), Equals("€"));
    }

    SECTION("UTF-16")
    {
        REQUIRE(PwCard::to_utf16(0x30) == u'0');
        REQUIRE(PwCard::to_utf16(0x91) == u'€');
    }
}
