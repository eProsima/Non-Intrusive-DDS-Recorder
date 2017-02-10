set(CPACK_PACKAGE_NAME ${PROJECT_NAME})

set(CPACK_PACKAGE_DESCRIPTION_SUMMARY "${CPACK_PACKAGE_NAME} - ${${PROJECT_NAME}_DESCRIPTION_SUMMARY}")

set(CPACK_PACKAGE_DESCRIPTION "${${PROJECT_NAME}_DESCRIPTION}")

set(CPACK_PACKAGE_VENDOR "eProsima")
set(CPACK_PACKAGE_CONTACT "eProsima Support <support@eprosima.com>")

set(CPACK_PACKAGE_VERSION_MAJOR ${PROJECT_MAJOR_VERSION})
set(CPACK_PACKAGE_VERSION_MINOR ${PROJECT_MINOR_VERSION})
set(CPACK_PACKAGE_VERSION_PATH ${PROJECT_MICRO_VERSION})
set(CPACK_PACKAGE_VERSION ${PROJECT_VERSION}) 
set(CPACK_RESOURCE_FILE_LICENSE "${PROJECT_SOURCE_DIR}/doc/licencias/DDSRECORDER_LICENSE.txt")

###############################################################################
# Platform and architecture dependant
###############################################################################
if(WIN32)
    set(CPACK_GENERATOR NSIS)

    if(CMAKE_CL_64)
        set(INSTALLER_SUFFIX Win64)
    else()
        set(INSTALLER_SUFFIX Win32)
    endif()

    configure_file(${PROJECT_SOURCE_DIR}/cmake/packaging/windows/WindowsPackaging.cmake.in ${PROJECT_BINARY_DIR}/cmake/packaging/windows/WindowsPackaging.cmake @ONLY)
    configure_file(${PROJECT_SOURCE_DIR}/cmake/packaging/windows/NSISPackaging.cmake.in ${PROJECT_BINARY_DIR}/cmake/packaging/windows/NSISPackaging.cmake @ONLY)

    # Update CMAKE_MODULE_PATH to find NSIS.template.in
    set(CMAKE_MODULE_PATH ${CMAKE_MODULE_PATH} "${PROJECT_SOURCE_DIR}/cmake/packaging/windows")

    # Set cpack project config file.
    set(CPACK_PROJECT_CONFIG_FILE ${PROJECT_BINARY_DIR}/cmake/packaging/windows/WindowsPackaging.cmake)
endif()

include(CPack)
