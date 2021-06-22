#pragma once

#include <fty/rest/runner.h>

namespace fty {

class ListPost : public rest::Runner
{
public:
    INIT_REST("rest_communications_POST");

public:
    unsigned run() override;

private:
    // clang-format off
    Permissions m_permissions = {
        { rest::User::Profile::Admin, rest::Access::Create }
    };
    // clang-format on
};

} // namespace fty
