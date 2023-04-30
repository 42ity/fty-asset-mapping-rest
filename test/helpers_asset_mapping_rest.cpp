#include <catch2/catch.hpp>
#include <fty/string-utils.h>
#include "src/helpers_asset_mapping_rest.h"

TEST_CASE("helpers_asset_mapping_rest - path")
{
    using namespace restapi;

    SECTION("empty")
    {
        Path path("");
        CHECK(path.getPathStr().empty());
        CHECK(path.getNumberOfItem() == 0);
        CHECK_THROWS(path.getItem(0));
    }

    SECTION("root")
    {
        std::string p = "/";
        Path path(p);
        CHECK(path.getPathStr() == p);
        CHECK(path.getNumberOfItem() == 0);
        CHECK_THROWS(path.getItem(0));
    }

    SECTION("single")
    {
        std::string p = "/0";
        Path path(p);
        CHECK(path.getPathStr() == p);
        CHECK(path.getNumberOfItem() == 1);
        CHECK(path.getItem(0) == "0");
        CHECK_THROWS(path.getItem(1));
    }

    SECTION("nominal")
    {
        std::string p = "/0/1/2/3";
        Path path(p);
        CHECK(path.getPathStr() == p);
        CHECK(path.getNumberOfItem() == 4);
        CHECK(path.getItem(0) == "0");
        CHECK(path.getItem(1) == "1");
        CHECK(path.getItem(2) == "2");
        CHECK(path.getItem(3) == "3");
        CHECK_THROWS(path.getItem(4));
    }

    SECTION("limit")
    {
        std::string p = "///0////1///2///";
        Path path(p);
        CHECK(path.getPathStr() == p);
        CHECK(path.getNumberOfItem() == 3);
        CHECK(path.getItem(0) == "0");
        CHECK(path.getItem(1) == "1");
        CHECK(path.getItem(2) == "2");
        CHECK_THROWS(path.getItem(3));
    }
}

TEST_CASE("helpers_asset_mapping_rest - createId")
{
    using namespace restapi;

    const cam::CredentialAssetMapping mapping; // empty
    CHECK_NOTHROW(createId(mapping));
    CHECK(fty::split(createId(mapping), "+").size() == 0); // "++"
}
