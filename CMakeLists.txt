cmake_minimum_required(VERSION 3.10 FATAL_ERROR)
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)


option(NO_OS "Turn off build for os" OFF)

# build output directories

if(NO_OS)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY $<0:>${CMAKE_BINARY_DIR}/bin)
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY $<0:>${CMAKE_BINARY_DIR}/bin)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY $<0:>${CMAKE_BINARY_DIR}/lib)
set(CMAKE_PDB_OUTPUT_DIRECTORY $<0:>${CMAKE_BINARY_DIR}/lib)
set(EXECUTABLE_OUTPUT_PATH $<0:>${CMAKE_BINARY_DIR}/bin)
else()
# Output dir: everything goes to build/output/
set(OUTPUT_ROOT ${CMAKE_BINARY_DIR}/output)

set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${OUTPUT_ROOT}/usr/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${OUTPUT_ROOT}/usr/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${OUTPUT_ROOT}/usr/lib)
set(CMAKE_PDB_OUTPUT_DIRECTORY     ${OUTPUT_ROOT}/usr/lib)
set(CMAKE_INSTALL_PREFIX           ${OUTPUT_ROOT}/usr)

# Optional: make `make install` populate ${OUTPUT_ROOT}
include(GNUInstallDirs)
endif()

# cpp standard options

set(CMAKE_CONFIGURATION_TYPES Debug Release)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS ON)
set(CMAKE_CXX_STANDARD 17)

project(GenesisOs C CXX)

# enable console logging

if(${CMAKE_BUILD_TYPE} MATCHES Debug)
    add_definitions(-DGC_DEBUG)
endif(${CMAKE_BUILD_TYPE} MATCHES Debug)

add_subdirectory(vendor/glm)
add_subdirectory(vendor/glad)
# add_subdirectory(vendor/entt)
# add_subdirectory(vendor/imgui)
 add_subdirectory(vendor/spdlog)
# set(ASSIMP_BUILD_TESTS OFF)
# set(ASSIMP_INSTALL OFF)
# set(ASSIMP_BUILD_ASSIMP_TOOLS OFF CACHE BOOL "" FORCE)
# set(ASSIMP_BUILD_SAMPLES OFF CACHE BOOL "" FORCE)
# add_subdirectory(vendor/assimp)
# set(YAML_CPP_BUILD_CONTRIB OFF)
# set(YAML_CPP_BUILD_TOOLS OFF)
# set(YAML_CPP_BUILD_TESTS OFF)
# set(YAML_BUILD_SHARED_LIBS OFF)
# add_subdirectory(vendor/yaml-cpp)
# set(USE_STATIC_MSVC_RUNTIME_LIBRARY ON)
# add_subdirectory(vendor/JoltPhysics/build)
# add_subdirectory(vendor/ImGuiFileDialog)

add_subdirectory(genesis-core)
add_subdirectory(genesis-3Dengine)
add_subdirectory(genesis-ui)
