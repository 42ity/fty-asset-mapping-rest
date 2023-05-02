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
#include "src/delete.h"
#include "requestContext.h"

using Catch::Matchers::Contains;

TEST_CASE("delete")
{
    UT::RequestContext rc("DELETE", "/api/v1/admin/communication-data/communications/assetId+service+protocol");

    SECTION("Dashboard")
    {
        rc.setUserDashboard();
        fty::Delete runner(rc.request(), rc.reply(), rc.params());

        const std::string e0{"Permission not defined"};
        CHECK_THROWS_WITH(runner.run(), Contains(e0));
    }

    SECTION("Admin")
    {
        rc.setUserAdmin();
        fty::Delete runner(rc.request(), rc.reply(), rc.params());

        const std::string e0{"item does not exist"};
        const std::string e1{"Malamute error"}; // pass UT on Jenkins
        CHECK_THROWS_WITH(runner.run(), Contains(e0) || Contains(e1));
    }
}
