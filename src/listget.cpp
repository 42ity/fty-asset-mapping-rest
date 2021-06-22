#include "listget.h"
#include "helpers_asset_mapping_rest.h"
#include <cam_accessor.h>
#include <cxxtools/jsonserializer.h>
#include <fty/rest/component.h>

namespace fty {

unsigned ListGet::run()
{
    rest::User user(m_request);
    if (auto ret = checkPermissions(user.profile(), m_permissions); !ret) {
        throw rest::Error(ret.error());
    }

    restapi::Path path(m_request.path());

    auto asset      = m_request.queryArg<std::string>("asset");
    auto service    = m_request.queryArg<std::string>("service");
    auto credential = m_request.queryArg<std::string>("credential");
    auto protocol   = m_request.queryArg<std::string>("protocol");
    auto port       = m_request.queryArg<std::string>("port");

    try {
        // get the data
        cam::Accessor accessor(restapi::CLIENT_ID, 1000, restapi::END_POINT);
        auto          mappings = accessor.getAllMappings();

        cxxtools::SerializationInfo rootSi;

        // filter the data
        for (const cam::CredentialAssetMapping& mapping : mappings) {
            // skip the mapping if the filter on asset is not satisfy
            if (asset && mapping.m_assetId != *asset) {
                continue;
            }

            // skip the mapping if the filter on service is not satisfy
            if (service && mapping.m_serviceId != *service) {
                continue;
            }

            // skip the mapping if the filter on credential is not satisfy
            if (credential && mapping.m_credentialId != *credential) {
                continue;
            }

            // skip the mapping if the filter on protocol is not satisfy
            if (protocol && mapping.m_protocol != *protocol) {
                continue;
            }

            // skip the mapping if the filter on port is not satisfy
            if (port && mapping.m_port != *port) {
                continue;
            }

            cxxtools::SerializationInfo si;
            si <<= mapping;

            // add the id
            si.addMember("id") <<= restapi::createId(mapping);

            // add in the list
            rootSi.addMember("") <<= si;
        }

        rootSi.setCategory(cxxtools::SerializationInfo::Array);

        // Send reply.
        std::stringstream        output;
        cxxtools::JsonSerializer ser(output);
        ser.serialize(rootSi);
        m_reply << output.str();
    } catch (const std::exception& e) {
        throw rest::errors::Internal("Error while getting list of communication: {}"_tr.format(e.what()));
    }

    return HTTP_OK;
}

} // namespace fty

registerHandler(fty::ListGet)
