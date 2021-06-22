#pragma once

#include <fty/rest/runner.h>

namespace fty {

class Delete : public rest::Runner
{
public:
    INIT_REST("rest_communication_DELETE");

public:
    unsigned run() override;

private:
    // clang-format off
    Permissions m_permissions = {
        { rest::User::Profile::Admin, rest::Access::Delete }
    };
    // clang-format on
};

} // namespace fty
