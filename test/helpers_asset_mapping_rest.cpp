/*  =========================================================================
    Copyright (C) 2018 - 2020 Eaton

    This program is free software; you can redistribute it and/or modify
    it under the terms of the GNU General Public License as published by
    the Free Software Foundation; either version 2 of the License, or
    (at your option) any later version.

    This program is distributed in the hope that it will be useful,
    but WITHOUT ANY WARRANTY; without even the implied warranty of
    MERCHANTABILITY or FITNESS FOR A PARTICULAR PURPOSE.  See the
    GNU General Public License for more details.

    You should have received a copy of the GNU General Public License along
    with this program; if not, write to the Free Software Foundation, Inc.,
    51 Franklin Street, Fifth Floor, Boston, MA 02110-1301 USA.
    =========================================================================
*/

#include <catch2/catch.hpp>
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
    CHECK(createId(mapping) == "++");
}
