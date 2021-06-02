cmake_minimum_required(VERSION 3.13)
cmake_policy(VERSION 3.13)

########################################################################################################################

project(fty-asset-mapping-rest
    VERSION 1.0.0
    DESCRIPTION "Asset mapping REST API"
)

########################################################################################################################
find_package(fty-cmake PATHS ${CMAKE_BINARY_DIR}/fty-cmake)
########################################################################################################################

etn_target(shared ${PROJECT_NAME}
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
        fty-cmake-rest
        fty-utils
        czmq
        cxxtools
        fty_common
        fty_security_wallet
        tntnet
    TARGET_DESTINATION /usr/lib/bios
)

########################################################################################################################

etn_test_target(${PROJECT_NAME}
    SOURCES
        main.cpp
    SUBDIR
        test
)

########################################################################################################################

install(FILES ${PROJECT_SOURCE_DIR}/resources/41_asset-mapping-rest.xml DESTINATION "${CMAKE_INSTALL_FULL_SYSCONFDIR}/tntnet/bios.d")

########################################################################################################################

# etn_configure_file(
#     conf/XX_project.xml.in
#     TARGET      ${PROJECT_NAME}
#     DESTINATION /etc/tntnet/bios.d
# )

########################################################################################################################
