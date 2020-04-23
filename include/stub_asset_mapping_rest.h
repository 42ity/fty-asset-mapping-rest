/*  =========================================================================
    stub_asset_mapping_rest - REST API for asset mapping

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

#ifndef STUB_ASSET_MAPPING_REST_H_INCLUDED
#define STUB_ASSET_MAPPING_REST_H_INCLUDED

#ifdef __cplusplus
extern "C" {
#endif

//  @interface
//  Create a new stub_asset_mapping_rest
FTY_ASSET_MAPPING_REST_EXPORT stub_asset_mapping_rest_t *
    stub_asset_mapping_rest_new (void);

//  Destroy the stub_asset_mapping_rest
FTY_ASSET_MAPPING_REST_EXPORT void
    stub_asset_mapping_rest_destroy (stub_asset_mapping_rest_t **self_p);

//  Self test of this class
FTY_ASSET_MAPPING_REST_EXPORT void
    stub_asset_mapping_rest_test (bool verbose);

//  @end

#ifdef __cplusplus
}
#endif

#endif
