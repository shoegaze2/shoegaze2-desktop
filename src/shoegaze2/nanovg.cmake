set(NANOVG_SRC_DIR ../../deps/nanovg/src)

list(APPEND NANOVG_SOURCES
        ${NANOVG_SRC_DIR}/nanovg.c
        ${NANOVG_SRC_DIR}/nanovg.h
        ${NANOVG_SRC_DIR}/nanovg_gl.h
        ${NANOVG_SRC_DIR}/nanovg_gl_utils.h)
add_library(nanovg ${NANOVG_SOURCES})

find_package(OpenGL REQUIRED)

include_directories(${OPENGL_INCLUDE_DIRS} ${NANOVG_SRC_DIR})

set(GLFW_BUILD_DOCS OFF CACHE BOOL  "GLFW lib only")
set(GLFW_INSTALL OFF CACHE BOOL  "GLFW lib only")
set(GLFW_BUILD_EXAMPLES OFF CACHE BOOL  "GLFW lib only")
set(GLFW_BUILD_TESTS OFF CACHE BOOL  "GLFW lib only")

add_subdirectory(${DEPS_DIR}/glfw glfw)
include(${DEPS_DIR}/glad/cmake/CMakeLists.txt)

glad_add_library(glad_gl_core_33 STATIC API gl:core=3.3 wgl:core=1.0)

target_link_libraries(nanovg PUBLIC glad_gl_core_33 glfw)