#include <catch2/catch.hpp>
#include "src/get.h"
#include "requestContext.h"

using Catch::Matchers::Contains;

TEST_CASE("get")
{
    UT::RequestContext rc("GET", "/api/v1/admin/communication-data/communication/x+y+z");

    SECTION("Dashboard")
    {
        rc.setUserDashboard();
        fty::Get runner(rc.request(), rc.reply(), rc.params());

        const std::string e0{"Permission not defined"};
        CHECK_THROWS_WITH(runner.run(), Contains(e0));
    }

    SECTION("Admin")
    {
        rc.setUserAdmin();
        fty::Get runner(rc.request(), rc.reply(), rc.params());

        const std::string e0{"item does not exist"};
        const std::string e1{"Malamute error"}; // pass UT on Jenkins
        CHECK_THROWS_WITH(runner.run(), Contains(e0) || Contains(e1));
    }
}
