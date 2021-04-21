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
        fty-cmake-rest
        czmq
        cxxtools
        fty_common
        fty_common_logging
        fty_common_mlm
        fty_common_rest
        fty_security_wallet
        tntdb
        tntnet
    TARGET_DESTINATION /usr/lib/bios
)

########################################################################################################################

# Get the ecpp
file(GLOB ECPP_FILES
  ecpp/*.ecpp
)

# Transform ecpp files
fty_ecppbuilder(
  TARGET ${PROJECT_NAME}
  WORKDIR src
  ECPP
    ${ECPP_FILES}
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