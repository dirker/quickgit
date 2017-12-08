cmake_minimum_required(VERSION 3.10)

project(quickgit)
add_executable(quickgit main.cpp)

find_package(PkgConfig REQUIRED)
pkg_search_module(LIBGIT2 REQUIRED libgit2)

target_link_libraries(quickgit ${LIBGIT2_LIBRARIES})
target_include_directories(quickgit PUBLIC ${LIBGIT2_INCLUDE_DIRS})
target_compile_options(quickgit PUBLIC ${SDL2_CFLAGS_OTHER})
