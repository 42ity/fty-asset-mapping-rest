/*  =========================================================================
    restapi_helpers - Helpers

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

#include "cam_accessor.h"

namespace restapi
{
    static constexpr char END_POINT[] = "ipc://@/malamute";
    static constexpr char CLIENT_ID[] = "fty-asset-mapping-rest";

    std::string createId(const cam::CredentialAssetMapping & mapping);
    std::vector<std::string> splitString(const std::string & str, char separator);

    //URL_PREFIX = /api/v1/admin/communication-data/
    static constexpr size_t URL_PREFIX_SIZE = 4;

    class Path
    {
    public:
        Path(const std::string & pathStr);

        const std::string & getPathStr() const;
        const std::string & getItem(size_t index) const;
        size_t getNumberOfItem() const;

    private:
        std::string m_pathStr;
        std::vector<std::string> m_items;
    };
   
} //namepace restapi
