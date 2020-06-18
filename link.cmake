#Add sources to the project
sos_sdk_add_subdirectory(SOS_SOURCELIST src)
file(GLOB_RECURSE HEADER_SOURCES ${CMAKE_SOURCE_DIR}/include/*)
list(APPEND SOS_SOURCELIST ${HEADER_SOURCES})

set(SOS_CONFIG release)
set(SOS_ARCH link)
set(SOS_OPTION "")
set(SOS_DEFINITIONS SFFS_IS_FULL_FEATURED=0)
include(${SOS_TOOLCHAIN_CMAKE_PATH}/sos-lib.cmake)

set(SOS_CONFIG release)
set(SOS_ARCH link)
set(SOS_OPTION full)
set(SOS_DEFINITIONS SFFS_IS_FULL_FEATURED=1)
include(${SOS_TOOLCHAIN_CMAKE_PATH}/sos-lib.cmake)

