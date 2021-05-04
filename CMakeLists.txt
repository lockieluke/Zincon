cmake_minimum_required(VERSION 3.18)
project(Zincon)

set(CMAKE_CXX_STANDARD 17)

# Set architecture
if (NOT DEFINED ARCH)
    string(TOLOWER ${CMAKE_SYSTEM_PROCESSOR} ARCH)
endif()

# Setup Apple Silicon
if (${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
    # Specify its an Apple Silicon-powered machine
    if (${ARCH} STREQUAL "arm64")
        set(CMAKE_APPLE_SILICON_PROCESSOR "arm64")
    endif()

    # Install vcpkg with homebrew
    include("/opt/homebrew/Cellar/vcpkg/2020.11-1/libexec/scripts/buildsystems/vcpkg.cmake")
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    # Install vcpkg to %localappdata%\Programs\vcpkg
    include("$ENV{LOCALAPPDATA}/Programs/vcpkg/scripts/buildsystems/vcpkg.cmake")
endif()

# Set alias for vcpkg
set(VCPKG_ROOT "${Z_VCPKG_ROOT_DIR}")

# Platform Announcement
message("Compiling for ${CMAKE_SYSTEM_NAME}...")

set(CMAKE_BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build)

set(MAIN_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
set(RENDERER_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/renderer/renderer.cpp)
set(PARSER_SOURCE ${CMAKE_CURRENT_SOURCE_DIR}/src/parser/html.cpp)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

# Bundle as .app on Darwin
if (${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
    set(MACOSX_BUNDLE_BUNDLE_NAME ${PROJECT_NAME})
    add_executable(${PROJECT_NAME} MACOSX_BUNDLE ${MAIN_SOURCES} ${RENDERER_SOURCES} ${PARSER_SOURCE})
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    add_executable(${PROJECT_NAME} ${MAIN_SOURCES} ${RENDERER_SOURCES} ${PARSER_SOURCE})
endif()

target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} OpenGL::GL)


if (${CMAKE_SYSTEM_NAME} STREQUAL "Darwin")
    target_link_libraries(${PROJECT_NAME} "/opt/homebrew/var/vcpkg/packages/glew_${ARCH}-osx/lib/libGLEW.a" "/usr/local/lib/liblexbor.dylib")
    target_include_directories(${PROJECT_NAME} PRIVATE "/opt/homebrew/var/vcpkg/packages/glew_${ARCH}-osx/include" "/usr/local/include")
elseif(${CMAKE_SYSTEM_NAME} STREQUAL "Windows")
    target_link_libraries(${PROJECT_NAME} "${VCPKG_ROOT}/installed/${ARCH}-windows/lib/glew32.lib" "${CMAKE_CURRENT_SOURCE_DIR}/lexbor/build/Release/lexbor.lib")
    target_include_directories(${PROJECT_NAME} PRIVATE "${VCPKG_ROOT}/installed/${ARCH}-windows/include" "${VCPKG_ROOT}/packages/glew_${ARCH}-windows/include" ${CMAKE_CURRENT_SOURCE_DIR}/lexbor/source)

    # Add .dll files
    configure_file("${CMAKE_CURRENT_SOURCE_DIR}/lexbor/build/Release/lexbor.dll" "${CMAKE_BINARY_DIR}" COPYONLY)

    message("Copy DLL files to the executable directory before running!")
endif()