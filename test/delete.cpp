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
