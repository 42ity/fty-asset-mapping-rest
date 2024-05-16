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
#include "src/listpost.h"
#include "requestContext.h"

using Catch::Matchers::Contains;

TEST_CASE("listpost")
{
    UT::RequestContext rc("POST", "/api/v1/admin/communication-data/communications");
    const std::string body = R"(
    {
        "cam_asset_FAKE": "epdu-1234",
        "cam_credential": "3af37fc9-6797-460b-a396-5c99cde3f594",
        "cam_extended_info": [],
        "cam_port": 443,
        "cam_protocol": "mass_management",
        "cam_service": "mass_device_management",
        "cam_status": 0
    }
    )";
    rc.setBody(body); // creds. asset mapping payload (faked, missing 'cam_asset')

    SECTION("Dashboard")
    {
        rc.setUserDashboard();
        fty::ListPost runner(rc.request(), rc.reply(), rc.params());

        const std::string e0{"Permission not defined"};
        CHECK_THROWS_WITH(runner.run(), Contains(e0));
    }

    SECTION("Admin")
    {
        rc.setUserAdmin();
        fty::ListPost runner(rc.request(), rc.reply(), rc.params());

        const std::string e0{"Error while creating a communication item"}; // cam_asset_FAKE
        const std::string e1{"Malamute error"}; // pass UT on Jenkins
        CHECK_THROWS_WITH(runner.run(), Contains(e0) || Contains(e1));
    }
}
