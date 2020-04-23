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

#include "fty_asset_mapping_rest_classes.h"

namespace restapi
{
    Path::Path(const std::string & pathStr)
        : m_pathStr(pathStr)
    {
        m_items = splitString(m_pathStr.substr (0, m_pathStr.find ("?")), '/');
    }

    const std::string & Path::getPathStr() const
    {
        return m_pathStr;
    }
    const std::string & Path::getItem(size_t index) const
    {
        return m_items.at(index);
    }

    size_t Path::getNumberOfItem() const
    {
        return m_items.size();
    }

    std::string createId(const cam::CredentialAssetMapping & mapping)
    {
        return mapping.m_assetId+"+"+mapping.m_serviceId+"+"+mapping.m_protocol;
    }

    std::vector<std::string> splitString(const std::string & str, char separator)
    {
        std::stringstream stream;
        stream << str;

        std::vector<std::string> items;

        std::string item;

        while(std::getline(stream, item, separator))
        {
            if(!item.empty())
            {
                items.push_back(item);
            }
        }

        return items;
    }
}

