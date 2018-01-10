#   == CMAKE ==
#   -- Version --
cmake_minimum_required(VERSION 3.9.6)



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
if (NOT DEFINED COLOUR)
    set(COLOUR true)
endif ()
message("Coloured messages: ${COLOUR}")

#   -- Verbose --
if (NOT DEFINED VERBOSE)
    set(VERBOSE true)
endif ()
message("Verbose messages: ${VERBOSE}")



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
    set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} \
        -DDEBUG                             \
        -g                                  \
        -O0                                 \
        -fsanitize=integer                  \
        -fsanitize=undefined                \
    ")
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
        -Wno-unknown-pragmas                \
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
