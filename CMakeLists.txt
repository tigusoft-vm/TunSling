cmake_minimum_required (VERSION 3.0)
project (TunTest)

set(CMAKE_CXX_FLAGS ${CMAKE_CXX_FLAGS} -std=c++14)

find_package(Boost REQUIRED COMPONENTS system)
if(NOT Boost_FOUND)
    message(FATAL_ERROR "Boost not found!!!")
endif()

file(GLOB src_group
    src/*.cpp
    src/*.h
)

add_executable(TunTest ${src_group})
target_link_libraries(TunTest ${Boost_LIBRARIES})
target_include_directories(TunTest PUBLIC ${Boost_INCLUDE_DIRS})

if(UNIX)
    target_link_libraries(TunTest pthread)
endif()


