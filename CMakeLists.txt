cmake_minimum_required(VERSION 3.10)
project(quickgit)

add_executable(quickgit main.cpp imgui.cpp imgui_draw.cpp imgui_impl_glfw.cpp)

find_package(OpenGL REQUIRED)
target_include_directories(quickgit PUBLIC ${OPENGL_INCLUDE_DIR})
target_link_libraries(quickgit ${OPENGL_gl_LIBRARY})

find_package(PkgConfig REQUIRED)

pkg_search_module(LIBGIT2 REQUIRED libgit2)
target_link_libraries(quickgit ${LIBGIT2_LIBRARIES})
target_include_directories(quickgit PUBLIC ${LIBGIT2_INCLUDE_DIRS})
target_compile_options(quickgit PUBLIC ${LIBGIT2_COMPILE_FLAGS})

pkg_search_module(GLFW REQUIRED glfw3)
target_link_libraries(quickgit ${GLFW_LIBRARIES})
target_include_directories(quickgit PUBLIC ${GLFW_INCLUDE_DIRS})
target_compile_options(quickgit PUBLIC ${GLFW_COMPILE_FLAGS})
