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
    INCLUDE_DIRS
        include
    SOURCES
        src/*.cc
    USES
        czmq
        cxxtools
        fty_common
        fty_common_logging
        fty_common_mlm
        fty_common_rest
        fty_security_wallet
        tntdb
)

########################################################################################################################

# # Get the ecpp
# file(GLOB ECPP_FILES
#   ecpp/*.ecpp
# )

# # Transform ecpp files
# fty_ecppbuilder(
#   TARGET ${PROJECT_NAME}
#   WORKDIR src
#   ECPP
#     ${ECPP_FILES}
# )

########################################################################################################################

etn_test_target(${PROJECT_NAME}
    SOURCES
        # fty_common_rest_utils_web.cc
        main.cpp
    SUBDIR
        test
)

########################################################################################################################

install(FILES 41_asset-mapping-rest.xml DESTINATION "/etc/tntnet/bios.d")

########################################################################################################################