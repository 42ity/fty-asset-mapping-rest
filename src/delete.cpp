#include "delete.h"
#include "helpers_asset_mapping_rest.h"
#include <cam_accessor.h>
#include <fty/rest/component.h>
#include <fty/string-utils.h>

namespace fty {

unsigned Delete::run()
{
    rest::User user(m_request);
    if (auto ret = checkPermissions(user.profile(), m_permissions); !ret) {
        throw rest::Error(ret.error());
    }

    restapi::Path path(m_request.path());

    try {
        cam::Accessor accessor(restapi::CLIENT_ID, 1000, restapi::END_POINT);

        // extract data from the path: <URL_PREFIX>/communications/<id_item>
        const std::string& idItem = path.getItem(restapi::URL_PREFIX_SIZE + 1);

        // extract the id
        std::vector<std::string> idArray = fty::split(idItem, "+");

        // try to save it
        accessor.removeMapping(idArray.at(0), idArray.at(1), idArray.at(2));

        m_reply << "{}";
    } catch (const cam::CamMappingDoesNotExistException& /*e*/) {
        throw rest::errors::BadRequestDocument("Communication item does not exist"_tr);
    } catch (const std::exception& e) {
        throw rest::errors::Internal("Error while updating a communication item: {}"_tr.format(e.what()));
    }

    return HTTP_OK;
}

} // namespace fty

registerHandler(fty::Delete)
