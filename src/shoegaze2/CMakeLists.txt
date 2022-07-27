add_library(shoegaze2-desktop-lib STATIC)

set(SHOEGAZE2DESKTOP_DIR ${CMAKE_CURRENT_LIST_DIR}/Shoegaze2Desktop)

set(AUDIO_API_DIR ${SHOEGAZE2DESKTOP_DIR}/Audio/PortAudio)
set(AUDIO_API_SOURCES
        ${AUDIO_API_DIR}/AudioDevice.h
        ${AUDIO_API_DIR}/AudioDevice.cpp
        ${AUDIO_API_DIR}/AudioSystem.h
        ${AUDIO_API_DIR}/AudioSystem.cpp
        )

target_sources(shoegaze2-desktop-lib
        PUBLIC
        ${SHOEGAZE2DESKTOP_DIR}/GUI/Brush.h
        ${SHOEGAZE2DESKTOP_DIR}/GUI/Canvas.h
        ${SHOEGAZE2DESKTOP_DIR}/GUI/DisplayDevice.h
        ${SHOEGAZE2DESKTOP_DIR}/GUI/Image.h
        ${SHOEGAZE2DESKTOP_DIR}/GUI/Paint.h
        ${SHOEGAZE2DESKTOP_DIR}/GUI/Path.h
        ${SHOEGAZE2DESKTOP_DIR}/GUI/RenderingContext.h
        ${SHOEGAZE2DESKTOP_DIR}/GUI/UISystem.h
        ${SHOEGAZE2DESKTOP_DIR}/Input/Mouse.h
        ${AUDIO_API_SOURCES}
        PRIVATE
        ${SHOEGAZE2DESKTOP_DIR}/GUI/Canvas.cpp
        ${SHOEGAZE2DESKTOP_DIR}/GUI/DisplayDevice.cpp
        ${SHOEGAZE2DESKTOP_DIR}/GUI/Image.cpp
        ${SHOEGAZE2DESKTOP_DIR}/GUI/RenderingContext.cpp
        ${SHOEGAZE2DESKTOP_DIR}/GUI/UISystem.cpp
        ${SHOEGAZE2DESKTOP_DIR}/Input/Mouse.cpp
        )

include(nanovg.cmake)

set(PA_DISABLE_INSTALL ON CACHE BOOL "Disable PortAudio install")
set(PA_BUILD_SHARED OFF CACHE BOOL "Disable PortAudio shared library")
add_subdirectory(${DEPS_DIR}/portaudio ${CMAKE_CURRENT_BINARY_DIR}/portaudio)

get_target_property(PORTAUDIO_INCLUDES portaudio_static INCLUDE_DIRECTORIES)

add_subdirectory(../../../shoegaze2 ${CMAKE_CURRENT_BINARY_DIR}/shoegaze2)
shoegaze2_add_library(shoegaze2-lib)

target_include_directories(shoegaze2-desktop-lib PUBLIC ${CMAKE_CURRENT_LIST_DIR} ${PORTAUDIO_INCLUDES})
target_link_libraries(shoegaze2-desktop-lib PUBLIC shoegaze2-lib nanovg portaudio_static)