#   == CMAKE ==
#   -- Version --
cmake_minimum_required(VERSION 3.7.2)



#   == PROJECTS ==
#   -- Arctorus --
project(arctorus)



#   == BUILD INFOMATION ==
#   -- Date --
execute_process(COMMAND git log -1 --format=%cd --date=short OUTPUT_VARIABLE BUILD_DATE)
string(REGEX REPLACE "\n$" "" BUILD_DATE "${BUILD_DATE}")
set(BUILD_DATE ${BUILD_DATE})
message("Build date:'${BUILD_DATE}'.")

#   -- Branch --
execute_process(COMMAND git rev-parse --abbrev-ref HEAD OUTPUT_VARIABLE BUILD_BRANCH)
string(REGEX REPLACE "\n$" "" BUILD_BRANCH "${BUILD_BRANCH}")
set(BUILD_BRANCH ${BUILD_BRANCH})
message("Build branch:'${BUILD_BRANCH}'.")

#   -- Patch --
execute_process(COMMAND git rev-list --count HEAD OUTPUT_VARIABLE BUILD_PATCH)
string(REGEX REPLACE "\n$" "" BUILD_PATCH "${BUILD_PATCH}")
set(BUILD_PATCH ${BUILD_PATCH})
message("Build patch:'${BUILD_PATCH}'.")

#   -- Hash --
execute_process(COMMAND git rev-parse --short HEAD OUTPUT_VARIABLE BUILD_HASH)
string(REGEX REPLACE "\n$" "" BUILD_HASH "${BUILD_HASH}")
set(BUILD_HASH ${BUILD_HASH})
message("Build hash:'${BUILD_HASH}'.")

#   -- Type --
set(BUILD_TYPE ${CMAKE_BUILD_TYPE})
message("Build type:'${BUILD_TYPE}'.")

#   -- Compiler --
set(BUILD_COMPILER ${CMAKE_CXX_COMPILER_ID})
message("Build compiler:'${BUILD_COMPILER}'.")

#   -- Directory --
set(ARCTORUS_DIR ${CMAKE_SOURCE_DIR})
message("Build directory:'${ARCTORUS_DIR}'.")



#   == LOGGING OPTIONS ==
#   -- Colour --
if (NOT DEFINED LOG_COLOUR)
    set(LOG_COLOUR OFF)
endif ()
if (LOG_COLOUR)
    set(DEFINE_LOG_COLOUR "#define ENABLE_LOG_COLOUR")
    message("Coloured log enabled.")
else ()
    set(DEFINE_LOG_COLOUR "// Coloured log is disabled.")
    message("Coloured log disabled.")
endif ()

#   -- Verbose --
if (NOT DEFINED LOG_VERBOSE)
    set(LOG_VERBOSE OFF)
endif ()
if (LOG_VERBOSE)
    set(DEFINE_LOG_VERBOSE "#define ENABLE_LOG_VERBOSE")
    message("Verbose log enabled.")
else ()
    set(DEFINE_LOG_VERBOSE "// Verbose log is disabled.")
    message("Verbose log disabled.")
endif ()



#   == MODULE OPTIONS ==
#   -- Graphics --
if (NOT DEFINED GRAPHICS)
    set(GRAPHICS OFF)
endif ()
if (GRAPHICS)
    set(DEFINE_GRAPHICS "#define ENABLE_GRAPHICS")
    message("Graphics enabled.")
else ()
    set(DEFINE_GRAPHICS "// Graphics are disabled.")
    message("Graphics disabled.")
endif ()

#   -- Photon Paths --
if (NOT DEFINED PHOTON_PATHS)
    set(PHOTON_PATHS OFF)
endif ()
if (PHOTON_PATHS)
    if (NOT GRAPHICS)
        message(FATAL_ERROR "Photon paths are not allowed when graphics are disabled.")
    endif ()

    set(DEFINE_PHOTON_PATHS "#define ENABLE_PHOTON_PATHS")
    message("Photon paths enabled.")
else ()
    set(DEFINE_PHOTON_PATHS "// Photon paths are disabled.")
    message("Photon paths disabled.")
endif ()


#   == DIRECTORIES ==
#   -- Binary Output --
set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${CMAKE_SOURCE_DIR}/bin)

#   -- Source Code --
set(ARCTORUS_SRC_DIR ${CMAKE_SOURCE_DIR}/src)



#   == CONFIGURATION ==
#   -- Source --
configure_file(${CMAKE_SOURCE_DIR}/res/src/gen/config.hpp.in ${CMAKE_SOURCE_DIR}/src/gen/config.hpp)



#   == SOURCE CODE ==
#   -- Glob Files --
file(GLOB_RECURSE SOURCE_FILES ${ARCTORUS_SRC_DIR}/*.cpp)
file(GLOB_RECURSE HEADER_FILES ${ARCTORUS_SRC_DIR}/*.hpp)



#   == FLAGS ==
#   -- Standard --
set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

#   -- Optimisation --
if (CMAKE_BUILD_TYPE MATCHES "debug")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}                         \
        -DDEBUG                                                     \
        -g                                                          \
        -O0                                                         \
    ")
    if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
        set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS}                     \
        -fsanitize=integer                                          \
        -fsanitize=undefined                                        \
        -fsanitize-blacklist=${CMAKE_SOURCE_DIR}/.clang-sanitizer   \
    ")
    endif ()
elseif (CMAKE_BUILD_TYPE MATCHES "release")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
        -DNDEBUG                            \
        -O3                                 \
    ")
else ()
    message(FATAL_ERROR "Optimisation flags are not defined for build type: '${CMAKE_BUILD_TYPE}'.")
endif ()

#   -- Warning --
if (CMAKE_CXX_COMPILER_ID MATCHES "Clang")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
        -Weverything                        \
        -Wno-c++98-compat                   \
        -Wno-padded                         \
        -Wno-unknown-pragmas                \
        -Wno-weak-vtables                   \
    ")
elseif (CMAKE_CXX_COMPILER_ID MATCHES "GNU")
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
        -Wall                               \
        -Wextra                             \
        -Wpedantic                          \
        -Wno-unknown-pragmas                \
        -Wno-unknown-warning-option         \
    ")
else ()
    message(FATAL_ERROR "Warning flags are not defined for compiler type: '${CMAKE_CXX_COMPILER_ID}'.")
endif ()



#   == BUILDING ==
#   -- Exec Creation --
add_executable(arctorus ${SOURCE_FILES} ${HEADER_FILES})

#   -- Include Local Directories --
target_include_directories(arctorus PUBLIC ${ARCTORUS_SRC_DIR})

#   -- Locate Packages --
if (GRAPHICS)
    find_package(OpenGL REQUIRED)
    find_package(SDL2 REQUIRED)
    find_package(GLEW REQUIRED)
    find_package(glfw3 3.2.1 REQUIRED)

    #   -- Include System Directories --
    target_include_directories(arctorus SYSTEM PUBLIC ${OpenGL_INCLUDE_DIR})
    target_include_directories(arctorus SYSTEM PUBLIC ${SDL2_INCLUDE_DIR})

    #   -- Link Libraries --
    target_link_libraries(arctorus ${OPENGL_LIBRARIES})
    target_link_libraries(arctorus ${SDL2_LIBRARIES})
    target_link_libraries(arctorus GLEW)
    target_link_libraries(arctorus glfw)
endif ()
