#include <catch2/catch.hpp>
#include "src/listget.h"
#include "requestContext.h"
#include <fty_common_json.h>

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
