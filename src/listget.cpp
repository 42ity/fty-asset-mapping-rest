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

#include "listget.h"
#include "helpers_asset_mapping_rest.h"
#include <cam_accessor.h>
#include <fty_common_json.h>
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
        rootSi.setCategory(cxxtools::SerializationInfo::Array);

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

        // Send reply.
        m_reply << JSON::writeToString(rootSi);
    } catch (const std::exception& e) {
        throw rest::errors::Internal("Error while getting list of communication: {}"_tr.format(e.what()));
    }

    return HTTP_OK;
}

} // namespace fty

registerHandler(fty::ListGet)
