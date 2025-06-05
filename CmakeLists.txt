cmake_minimum_required(VERSION 3.15)

project(Raycasting_Engine)

# Set the C standard
set(CMAKE_C_STANDARD 11)

# Set the output directories for binaries and libraries
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/bin)
set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)
set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${CMAKE_BINARY_DIR}/lib)

# === SDL3 Submodule Directory ===
# SDL3 should be cloned in third-party/SDL as a Git submodule
set(SDL3_DIR ${CMAKE_SOURCE_DIR}/third-party/SDL)

# Include SDL3 headers
include_directories(${SDL3_DIR}/include)

# Include project headers
include_directories(${CMAKE_SOURCE_DIR}/includes)

# === SDL3 Submodule Configuration ===
if(EXISTS "${SDL3_DIR}/CMakeLists.txt")
    # Add SDL3 as a subdirectory to build it as part of the project
    add_subdirectory(${SDL3_DIR} EXCLUDE_FROM_ALL)

    # Use the static or shared SDL3 target defined by the submodule
    set(USE_SDL_TARGET SDL3::SDL3)
else()
    message(FATAL_ERROR "SDL3 submodule not initialized or missing: expected CMakeLists.txt in ${SDL3_DIR}")
endif()

# === Collect Source and Header Files ===
file(GLOB_RECURSE SOURCES ${CMAKE_SOURCE_DIR}/src/*.c)
file(GLOB_RECURSE HEADERS ${CMAKE_SOURCE_DIR}/includes/*.h)

# Create the executable
add_executable(${PROJECT_NAME} ${SOURCES} ${HEADERS})

# Group sources for IDEs
source_group("src" FILES ${SOURCES})
source_group("includes" FILES ${HEADERS})

# === Link SDL3 and Additional Libraries ===
target_link_libraries(${PROJECT_NAME} ${USE_SDL_TARGET})

# Link math library on Unix-like systems
if(UNIX AND NOT APPLE)
    target_link_libraries(${PROJECT_NAME} m)
endif()

# === Post-build: Copy SDL3 DLLs on Windows (MSVC only) ===
if(WIN32 AND MSVC)
    add_custom_command(TARGET ${PROJECT_NAME} POST_BUILD
        COMMAND ${CMAKE_COMMAND} -E copy_if_different
        $<TARGET_FILE:SDL3::SDL3>
        $<TARGET_FILE_DIR:${PROJECT_NAME}>
    )
endif()

# === Platform Compatibility Check ===
if(APPLE)
    message(FATAL_ERROR "macOS build is not currently supported. Please use Windows or Linux.")
elseif(NOT WIN32 AND NOT UNIX)
    message(FATAL_ERROR "Unsupported platform. Only Windows (MSVC/MinGW) and Linux are supported.")
endif()
