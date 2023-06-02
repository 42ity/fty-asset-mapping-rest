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
#include "src/listget.h"
#include "requestContext.h"

using Catch::Matchers::Contains;

TEST_CASE("listget")
{
    UT::RequestContext rc("GET", "/api/v1/admin/communication-data/communications");
/*
    rc.setArgs({
        { "asset", "theAsset" },
        { "service", "theService" },
        { "credential", "theCredential" },
        { "protocol", "theProtocol" },
        { "port", "thePort" },
    });
*/

    SECTION("Dashboard")
    {
        rc.setUserDashboard();
        fty::ListGet runner(rc.request(), rc.reply(), rc.params());

        const std::string e0{"Permission not defined"};
        CHECK_THROWS_WITH(runner.run(), Contains(e0));
    }

    SECTION("Admin")
    {
        rc.setUserAdmin();
        fty::ListGet runner(rc.request(), rc.reply(), rc.params());
        try {
            unsigned int status = runner.run();
            CHECK(status == HTTP_OK); // empty reply().out()
            //CHECK(rc.reply().out().tellp() == 5); // "[\n \n]"
        }
        catch (const std::exception& e) {
            const std::string e1{"Malamute error"}; // pass UT on Jenkins
            std::string ex{e.what()};
            CHECK(ex.find(e1) != std::string::npos);
        }
    }
}
