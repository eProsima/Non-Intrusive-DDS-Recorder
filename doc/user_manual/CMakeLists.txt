# Copyright 2026 Proyectos y Sistemas de Mantenimiento SL (eProsima).
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     http://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

###############################################################################
# CMake build rules for Non-Intrusive DDS Recorder documentation
###############################################################################
cmake_minimum_required(VERSION 3.20)

set(NI_DDSRECORDER_VERSION "${PROJECT_VERSION}")

project(ni_ddsrecorder_docs VERSION ${NI_DDSRECORDER_VERSION} LANGUAGES C CXX)

# In case CMake version less than 3.24, add the option CMAKE_COMPILE_WARNING_AS_ERROR.
if (${CMAKE_VERSION} VERSION_LESS "3.24")
    option(CMAKE_COMPILE_WARNING_AS_ERROR "Treat warnings as errors" OFF)
endif()

####################################################################################################
# Find Sphinx
####################################################################################################
set(CMAKE_MODULE_PATH "${PROJECT_SOURCE_DIR}/cmake" ${CMAKE_MODULE_PATH})
find_package(Sphinx REQUIRED)

####################################################################################################
# Build Sphinx documentation
####################################################################################################
# It is possible to build and run tests without generating the documentation output. This saves time
# while developing, since generating the documentation from the RSTs takes quite some time.
set(SPHINX_SOURCE "${PROJECT_SOURCE_DIR}")

# CMake project always build the documentaion using HTML builder. Users can always build with
# other builders using sphinx directly
set(DDSRECORDER_DOCS_BUILDER html)

# Generate the sphinx documentation
add_custom_target(Sphinx ALL
    COMMAND
    ${SPHINX_EXECUTABLE}
    $<$<BOOL:${CMAKE_COMPILE_WARNING_AS_ERROR}>:-W>
    -b ${DDSRECORDER_DOCS_BUILDER}
    -d "${PROJECT_BINARY_DIR}/doctrees"
    ${SPHINX_SOURCE}
    ${PROJECT_BINARY_DIR}/${DDSRECORDER_DOCS_BUILDER}
    WORKING_DIRECTORY ${CMAKE_CURRENT_BINARY_DIR}
    COMMENT "Generating documentation with Sphinx")


enable_testing()
include(CTest)
if (BUILD_TESTING)
    add_subdirectory(test)
endif()

# Install the generated docs
install(DIRECTORY ${PROJECT_BINARY_DIR}/${DDSRECORDER_DOCS_BUILDER}
    DESTINATION .
    COMPONENT ${DDSRECORDER_DOCS_BUILDER}
    PATTERN ".buildinfo" EXCLUDE)
set(CPACK_COMPONENT_EXAMPLES_DISPLAY_NAME "DDSRecorder-docs ${DDSRECORDER_DOCS_BUILDER}")
set(CPACK_COMPONENT_EXAMPLES_DESCRIPTION
    "eProsima Non-Intrusive DDS-Recorder documetation in ${DDSRECORDER_DOCS_BUILDER} format")
set(CPACK_COMPONENTS_ALL ${CPACK_COMPONENTS_ALL} ${DDSRECORDER_DOCS_BUILDER})
