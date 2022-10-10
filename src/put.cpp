#include "put.h"
#include "helpers_asset_mapping_rest.h"
#include <cam_accessor.h>
#include <fty/rest/component.h>

namespace fty {

unsigned Put::run()
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

        // extract the data
        cam::CredentialAssetMapping mapping;
        m_request.body() >>= mapping;

        if (idItem != restapi::createId(mapping)) {
            throw std::runtime_error("Mismatch id");
        }

        // try to save it
        accessor.updateMapping(mapping);

        m_reply << "{}";
    } catch (const cam::CamMappingDoesNotExistException& /*e*/) {
        throw rest::errors::BadRequestDocument("Communication item does not exist"_tr);
    } catch (const std::exception& e) {
        throw rest::errors::Internal("Error while updating a communication item: {}"_tr.format(e.what()));
    }

    return HTTP_OK;
}

} // namespace fty

registerHandler(fty::Put)
