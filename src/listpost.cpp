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

#include "listpost.h"
#include "helpers_asset_mapping_rest.h"
#include <cam_accessor.h>
#include <fty_common_json.h>
#include <fty/rest/component.h>

namespace fty {

unsigned ListPost::run()
{
    rest::User user(m_request);
    if (auto ret = checkPermissions(user.profile(), m_permissions); !ret) {
        throw rest::Error(ret.error());
    }

    restapi::Path path(m_request.path());

    try {
        cam::Accessor accessor(restapi::CLIENT_ID, 1000, restapi::END_POINT);

        // extract the data
        cam::CredentialAssetMapping mapping;
        m_request.body() >>= mapping;

        // try to save it
        accessor.createMapping(mapping);

        std::string newId = restapi::createId(mapping);

        std::string locationNewItem = (path.getPathStr() + "/" + newId);

        // Send reply.
        cxxtools::SerializationInfo si;
        si.addMember("id") <<= newId;

        m_reply << JSON::writeToString(si);
    } catch (const cam::CamMappingAlreadyExistsException& /*e*/) {
        throw rest::errors::BadRequestDocument("Communication item already exist"_tr);
    } catch (const std::exception& e) {
        throw rest::errors::Internal("Error while creating a communication item: {}"_tr.format(e.what()));
    }

    return HTTP_OK;
}

} // namespace fty

registerHandler(fty::ListPost)
