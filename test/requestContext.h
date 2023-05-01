#pragma once

#include <fty_common_rest_helpers.h> //UserInfo
#include <tnt/tntnet.h>
#include <tnt/httprequest.h>
#include <tnt/httpreply.h>

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
        m_request->getRequestScope().put<UserInfo, tnt::NullDestroyPolicy>("UserInfo user", &m_userInfo);
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
