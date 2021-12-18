#include <catch2/catch.hpp>

#include <pwcard/pwcard.h>

struct generate_test_data
{
    PwCard::seed_type seed;
    std::string header;
    std::array<std::string, PwCard::row_count> rows;
};

TEST_CASE("Card generation")
{
    auto expected_data = GENERATE(
        generate_test_data {
            0x8e602a74a6222e22,
            "□▲!�●¿△★¥$○?■£♫◩¡☺☹♥€☂♦♣☁☀⊙♠◐",
            {
                "Z43CBHeYSdcnwppphgWrcrv7U8HJj",
                "Y6YLDDaPkBUTMTvsGQJXq7WkLGxVw",
                "ZdqMChYUksHv65JJ6GbygQLfBPnZh",
                "HYQr9vwNNZuh78wC2qjXRPTHVkuje",
                "uC4Dcd6fnydTEcVSHyKSczzfE46F3",
                "QmBPA57Vmmr3AyymjxyXDfKy5YWEB",
                "tpp5mg5qSNv56LdYXzhgYCyKpZpzq",
                "Cc4ugrtyvruSRxsrPrmc4s7Gn5Dua",
            },
        },
        generate_test_data {
            0xaf2b38aa65663113,
            "♣★◩☹⊙£☺□☁♦●¡$€☀△☂◐▲�♠?♥¥○■¿!♫",
            {
                "p9DQWjZsuks4XH7fLtLUqz43fQNB6",
                "627mNwuEzWtzfYExapQFb3gNLzejm",
                "AG3X3AWRDYyadd4STDnXhxR2M5M6w",
                "b7VmpDQ9mKBLmSAeWhejqrWTHpeQ6",
                "dNg9JAGcqvpgHabse3kUbCddLw3A8",
                "vAjq47F3xBKRhp6hTyFxZpcCpSS4f",
                "bQMbZTxEGYpA3LA7D9mC9ppQ2uRQW",
                "mXjjkvWNmsZ7EHDKqFywPPHwhTDdU",
            },
        }
    );

    auto actual_data = PwCard::generate(expected_data.seed);
    REQUIRE(PwCard::to_utf8(actual_data.header) == expected_data.header);
    for (auto row = 0; row < PwCard::row_count; ++row)
        REQUIRE(PwCard::to_utf8(actual_data.rows[row]) == expected_data.rows[row]);
}
