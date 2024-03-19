cmake_minimum_required(VERSION 3.20)
project(lsap VERSION 1.0 DESCRIPTION "Tool to find Wifi access points written in C++")


set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(CMAKE_CXX_EXTENSIONS OFF)

if (MSVC)
    # warning level 4
    add_compile_options(/W4)
else()
    # additional warnings
    add_compile_options(-Wall -Wextra -Wpedantic)
endif()

set(SRCDIR ${CMAKE_CURRENT_SOURCE_DIR}/src)
set(INCLUDEDIR ${CMAKE_CURRENT_SOURCE_DIR}/include)
set(LIBDIR ${CMAKE_CURRENT_SOURCE_DIR}/lib)
set(BINDIR ${CMAKE_CURRENT_BINARY_DIR}/bin)
#set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${BINDIR})

# Gather all source files
file(GLOB SOURCES ${SRCDIR}/*.cpp)

# Add libraries you want to link with here
set(LIBRARIES "")

# Build executable
add_executable(lsap ${SOURCES})

# Link own libraries

add_library(netutils SHARED ${SRCDIR}/netutils/netutils.cpp)

target_link_libraries(lsap PRIVATE netutils)

# Link external libraries
target_include_directories(lsap PRIVATE ${INCLUDEDIR}) # header locations for libraries

target_link_directories(lsap PRIVATE ${LIBDIR}) # specify directory of the libraries

target_link_libraries(lsap PRIVATE ${LIBRARIES}) # link libraries

# Set capabilities for the executable
add_custom_command(TARGET lsap
    POST_BUILD
    COMMAND sudo setcap cap_net_raw+eip lsap
)


