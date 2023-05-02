#include <catch2/catch.hpp>
#include "src/put.h"
#include "requestContext.h"

using Catch::Matchers::Contains;

TEST_CASE("put")
{
    UT::RequestContext rc("PUT", "/api/v1/admin/communication-data/communications/assetId+service+protocol");
    const std::string body = R"(
    {
        "cam_asset_FAKE": "epdu-1234",
        "cam_credential": "3af37fc9-6797-460b-a396-5c99cde3f594",
        "cam_extended_info": [],
        "cam_port": 442,
        "cam_protocol": "mass_management",
        "cam_service": "mass_device_management",
        "cam_status": 0
    }
    )";
    rc.setBody(body); // creds. asset mapping payload (faked, missing 'cam_asset')

    SECTION("Dashboard")
    {
        rc.setUserDashboard();
        fty::Put runner(rc.request(), rc.reply(), rc.params());

        const std::string e0{"Permission not defined"};
        CHECK_THROWS_WITH(runner.run(), Contains(e0));
    }

    SECTION("Admin")
    {
        rc.setUserAdmin();
        fty::Put runner(rc.request(), rc.reply(), rc.params());

        const std::string e0{"Missing info"};
        const std::string e1{"Malamute error"}; // pass UT on Jenkins
        CHECK_THROWS_WITH(runner.run(), Contains(e0) || Contains(e1));
    }
}
