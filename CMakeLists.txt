cmake_minimum_required(VERSION 3.13)
cmake_policy(VERSION 3.13)

########################################################################################################################

project(fty-asset-mapping-rest
    VERSION 1.0.0
    DESCRIPTION "Credentials Asset Mapping REST API"
)

########################################################################################################################
find_package(fty-cmake PATHS ${CMAKE_BINARY_DIR}/fty-cmake)
########################################################################################################################

set(PROJECT_NAME_UNDERSCORE fty_asset_mapping_rest)

etn_target(shared ${PROJECT_NAME_UNDERSCORE}
    SOURCES
        src/helpers_asset_mapping_rest.cc
        src/helpers_asset_mapping_rest.h
        src/delete.h
        src/delete.cpp
        src/get.h
        src/get.cpp
        src/put.h
        src/put.cpp
        src/listget.h
        src/listget.cpp
        src/listpost.h
        src/listpost.cpp
    USES
        cxxtools
        tntnet
        fty-cmake-rest
        fty-utils
        fty-pack
        fty_common
        fty_security_wallet
    TARGET_DESTINATION
        ${CMAKE_INSTALL_PREFIX}/lib/bios
)

########################################################################################################################

etn_test_target(${PROJECT_NAME_UNDERSCORE}
    SOURCES
        main.cpp
        helpers_asset_mapping_rest.cpp
        src/*.cpp
    SUBDIR
        test
)

########################################################################################################################

install(FILES ${PROJECT_SOURCE_DIR}/resources/41_asset-mapping-rest.xml DESTINATION "${CMAKE_INSTALL_FULL_SYSCONFDIR}/tntnet/bios.d")

########################################################################################################################
