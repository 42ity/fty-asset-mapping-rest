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

#pragma once

#include <cxxtools/log.h> // tntnet13/cxxtools10 : fix missed cxxtools::LogConfiguration ref.
#include <tnt/tntnet.h>
#include <tnt/httprequest.h>
#include <tnt/httpreply.h>

#include <fty_common_rest_helpers.h> //UserInfo

namespace UT {

class RequestContext {
public:
    RequestContext() = delete;
    RequestContext(const std::string& method, const std::string& uri)
    {
        m_request = new tnt::HttpRequest(m_app);
        m_reply = new tnt::HttpReply(m_oss);
        if (!(m_request && m_reply)) {
            throw std::runtime_error("RequestContext ctor failed");
        }

        m_request->setMethod(method.c_str());
        m_request->setPathInfo(uri);
        m_request->getRequestScope().put<UserInfo, tnt::NullDestroyPolicy>("UserInfo%user", &m_userInfo);
    };

    ~RequestContext()
    {
        if (m_request) { delete m_request; m_request = nullptr; }
        if (m_reply) { delete m_reply; m_reply = nullptr; }
    }

    void setUserAdmin() noexcept
        { m_userInfo.profile(BiosProfile::Admin); }
    void setUserDashboard() noexcept
        { m_userInfo.profile(BiosProfile::Dashboard); }

    void setHeader(const std::string& header, const std::string& value) const noexcept
        { m_request->setHeader(header, value); }
    void setArgs(const std::map<std::string, std::string>& args) const noexcept
        { m_request->setArgs(args); }
    void setBody(const std::string& body) const noexcept
        { m_request->setBody(body); }

    tnt::HttpRequest& request() noexcept
        { return *m_request; }
    tnt::HttpReply& reply() noexcept
        { return *m_reply; }
    tnt::QueryParams& params() noexcept
        { return m_params; }

private:
    tnt::Tntnet m_app;
    tnt::HttpRequest* m_request{nullptr};
    std::ostringstream m_oss;
    tnt::HttpReply* m_reply{nullptr};
    tnt::QueryParams m_params;
    UserInfo m_userInfo;
};

} // namespace
