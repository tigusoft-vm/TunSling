cmake_minimum_required (VERSION 3.0)
project (TunTest)

list(APPEND CMAKE_MODULE_PATH "${CMAKE_CURRENT_SOURCE_DIR}/cmake")

set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -g0 -O3 -march=native -Wall -Wextra -pedantic")
#set(CMAKE_CXX_FLAGS "${CMAKE_CXX_FLAGS} -std=c++14 -g3 -O0 -march=native -Wall -Wextra -pedantic")
add_definitions("-DNDEBUG")

find_package(Boost REQUIRED COMPONENTS system program_options)
if(NOT Boost_FOUND)
    message(FATAL_ERROR "Boost not found!!!")
endif()

find_package(Sodium REQUIRED)
if(NOT Sodium_FOUND)
    message(FATAL_ERROR "Sodium not found!!!")
endif()

file(GLOB src_group
    src/*.cpp
    src/*.h
    cjdns-code/*.c
    cjdns-code/*.h
)

add_executable(TunTest ${src_group})
target_link_libraries(TunTest ${Boost_LIBRARIES} ${SODIUM_LIBRARY})
target_include_directories(TunTest PUBLIC ${Boost_INCLUDE_DIRS} ${SODIUM_INCLUDE_DIR})

if(UNIX)
    target_link_libraries(TunTest pthread)
endif()


