cmake_minimum_required(VERSION 3.0)
project(Battleship CXX)
set(CMAKE_CXX_STANDARD 11)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

# Export compile commands for tooling
set(CMAKE_EXPORT_COMPILE_COMMANDS ON)

# Platform-specific configurations
if(WIN32)
    # Windows-specific settings
    set(USE_WINMM ON CACHE BOOL "" FORCE)
    set(USE_EXTERNAL_GLFW OFF CACHE BOOL "" FORCE)
    add_definitions(-D_WIN32)
    add_definitions(-DPLATFORM_DESKTOP)
elseif(APPLE)
    # macOS-specific settings
    set(CMAKE_OSX_DEPLOYMENT_TARGET "10.15" CACHE STRING "Minimum OS X deployment version")
    add_definitions(-DPLATFORM_DESKTOP)
    # Ensure macOS finds the correct OpenGL
    find_package(OpenGL REQUIRED)
elseif(UNIX AND NOT APPLE)
    # Linux-specific settings
    add_definitions(-DPLATFORM_DESKTOP)
    # Linux dependencies
    find_package(X11 REQUIRED)
    if(NOT X11_FOUND)
        message(FATAL_ERROR "X11 development packages not found")
    endif()
endif()

# Raylib configuration options
set(BUILD_EXAMPLES OFF CACHE BOOL "" FORCE)
set(BUILD_GAMES OFF CACHE BOOL "" FORCE)
set(OPENGL_VERSION "3.3" CACHE STRING "" FORCE)
set(BUILD_SHARED_LIBS OFF CACHE BOOL "" FORCE)

# Fetch and configure Raylib
include(FetchContent)
set(FETCHCONTENT_QUIET FALSE)
FetchContent_Declare(
    raylib
    GIT_REPOSITORY https://github.com/raysan5/raylib.git
    GIT_TAG 4.5.0
)
FetchContent_MakeAvailable(raylib)

# Project source files
file(GLOB_RECURSE PROJECT_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_LIST_DIR}/sources/*.cpp")
set(PROJECT_INCLUDE "${CMAKE_CURRENT_LIST_DIR}/sources/")
set(HEADERS_INCLUDE "${CMAKE_CURRENT_LIST_DIR}/headers/")

# Create executable with platform-specific settings
if(WIN32)
    add_executable(${PROJECT_NAME} WIN32 ${PROJECT_SOURCES})
else()
    add_executable(${PROJECT_NAME} ${PROJECT_SOURCES})
endif()

# Include directories
target_include_directories(${PROJECT_NAME} PRIVATE
    ${PROJECT_INCLUDE}
    ${HEADERS_INCLUDE}
    ${raylib_SOURCE_DIR}/src
)

# Platform-specific linking
if(WIN32)
    target_link_libraries(${PROJECT_NAME} PRIVATE raylib winmm)
    if(MSVC)
        set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "/SUBSYSTEM:CONSOLE")
    else()
        set_target_properties(${PROJECT_NAME} PROPERTIES LINK_FLAGS "-mconsole")
    endif()
elseif(APPLE)
    target_link_libraries(${PROJECT_NAME} PRIVATE
        raylib
        ${OPENGL_LIBRARIES}
        "-framework IOKit"
        "-framework Cocoa"
        "-framework OpenGL"
    )
else() # Linux
    target_link_libraries(${PROJECT_NAME} PRIVATE
        raylib
        m
        pthread
        dl
        rt
        X11
    )
endif()

# Asset path definition
if(WIN32)
    target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/")
else()
    target_compile_definitions(${PROJECT_NAME} PUBLIC ASSETS_PATH="${CMAKE_CURRENT_SOURCE_DIR}/assets/")
endif()

# Debug output
message(STATUS "System: ${CMAKE_SYSTEM_NAME}")
message(STATUS "Build type: ${CMAKE_BUILD_TYPE}")
message(STATUS "Source files: ${PROJECT_SOURCES}")
