#pragma once

#include <fty/rest/runner.h>

namespace fty {

class Put : public rest::Runner
{
public:
    INIT_REST("rest_communication_PUT");

public:
    unsigned run() override;

private:
    // clang-format off
    Permissions m_permissions = {
        { rest::User::Profile::Admin, rest::Access::Update }
    };
    // clang-format on
};

} // namespace fty
