project(Zincon)
cmake_minimum_required(VERSION 3.18)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_APPLE_SILICON_PROCESSOR "arm64")
set(CMAKE_SYSTEM_PROCESSOR "arm64")
set(CMAKE_TOOLCHAIN_FILE "/opt/homebrew/Cellar/vcpkg/2020.11-1/libexec/scripts/buildsystems/vcpkg.cmake")

set(CMAKE_BINARY_DIR ${CMAKE_CURRENT_SOURCE_DIR}/build)

set(MAIN_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/main.cpp)
set(RENDERER_SOURCES ${CMAKE_CURRENT_SOURCE_DIR}/src/renderer/renderer.cpp)

find_package(glfw3 REQUIRED)
find_package(OpenGL REQUIRED)

include_directories("/opt/homebrew/var/vcpkg/packages/glew_arm64-osx/include")

add_executable(${PROJECT_NAME} ${MAIN_SOURCES} ${RENDERER_SOURCES})

SET_TARGET_PROPERTIES(${PROJECT_NAME} PROPERTIES MACOSX_BUNDLE TRUE)

target_link_libraries(${PROJECT_NAME} glfw)
target_link_libraries(${PROJECT_NAME} OpenGL::GL)
target_link_libraries(${PROJECT_NAME} "/opt/homebrew/var/vcpkg/packages/glew_arm64-osx/lib")