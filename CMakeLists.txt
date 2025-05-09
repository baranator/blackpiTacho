cmake_minimum_required(VERSION 3.14)
include(FetchContent)
project(lvgl)

foreach(BACKEND_NAME "SDL" "LINUX_DRM" "LINUX_FBDEV" "X11" "WAYLAND")
    execute_process(COMMAND "scripts/backend_conf.sh" ${BACKEND_NAME} OUTPUT_VARIABLE IS_BACKEND_ENABLED)
    set("LV_USE_${BACKEND_NAME}" ${IS_BACKEND_ENABLED})
endforeach()

# Uncomment if the program needs debugging
#set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -O0 -ggdb")

set(CMAKE_C_STANDARD 99) # LVGL officially supports C99 and above
set(CMAKE_CXX_STANDARD 17) #C17
set(CMAKE_CXX_STANDARD_REQUIRED ON)
set(EXECUTABLE_OUTPUT_PATH ${PROJECT_SOURCE_DIR}/bin)

file(GLOB_RECURSE MY_SOURCES CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/*.c")
file(GLOB_RECURSE MY_ASSETS CONFIGURE_DEPENDS "${CMAKE_CURRENT_SOURCE_DIR}/src/assets/*.c")
find_package(PkgConfig REQUIRED)

#gattlib stuff ...still missing include-error in gattlib seems to be fixed after 0.7.2
pkg_search_module(PCRE REQUIRED libpcre)
pkg_search_module(GLIB REQUIRED glib-2.0)
FetchContent_Populate(gattlib GIT_REPOSITORY https://github.com/labapart/gattlib.git GIT_TAG f99558d9b8e3dbba2a952a0b292d3497aec8ee69 SOURCE_DIR gattlib)
#option(GATTLIB_BUILD_EXAMPLES "" NO)
SET(GATTLIB_BUILD_EXAMPLES NO CACHE BOOL "Build libfoo shared library" FORCE)

add_subdirectory(gattlib)
include_directories(${GATTLIB_INCLUDE_DIRS})
    


#lvgl stuff
set(LV_CONF_BUILD_DISABLE_EXAMPLES 1)
set(LV_CONF_BUILD_DISABLE_DEMOS 1)
FetchContent_Populate(lvgl GIT_REPOSITORY https://github.com/lvgl/lvgl.git GIT_TAG e016e45bd40ba8ffcedca590197b2fccdaff3bed SOURCE_DIR lvgl)
add_subdirectory(lvgl)


target_include_directories(lvgl PUBLIC ${PROJECT_SOURCE_DIR}/include )

#add_subdirectory(${lvgl_SOURCE_DIR})

message(STATUS "${MY_ASSETS}")

if (LV_USE_LINUX_DRM)

    find_package(PkgConfig REQUIRED)
    pkg_check_modules(LIBDRM REQUIRED libdrm)

    target_include_directories(lvgl PUBLIC ${LIBDRM_INCLUDE_DIRS})
    #add_executable(blackpiTacho "${MY_SOURCES}")
    add_executable(blackpiTacho "${MY_SOURCES}" "${MY_ASSETS}")
    target_include_directories(blackpiTacho PUBLIC ${lvgl_SOURCE_DIR} ${PROJECT_SOURCE_DIR}/include)
    #target_include_directories(blackpiTacho PUBLIC  )
    #target_compile_definitions(blackpiTacho PRIVATE LV_CONF_INCLUDE_SIMPLE)
    target_link_libraries(blackpiTacho lvgl::lvgl lvgl::thorvg ${LIBDRM_LIBRARIES} m pthread jansson)

elseif (LV_USE_SDL)

    find_package(PkgConfig REQUIRED)
    pkg_check_modules(SDL2 REQUIRED sdl2)
    pkg_check_modules(SDL2_image REQUIRED SDL2_image)

    target_include_directories(lvgl PRIVATE ${SDL2_INCLUDE_DIRS})
    target_include_directories(lvgl PRIVATE ${SDL2_IMAGE_INCLUDE_DIRS})
    add_executable(blackpiTacho "${MY_SOURCES}" "${MY_ASSETS}")
    
    target_link_libraries(blackpiTacho lvgl::lvgl lvgl::thorvg ${SDL2_LIBRARIES} ${SDL2_IMAGE_LIBRARIES} m pthread jansson)

elseif (LV_USE_WAYLAND)

    find_package(PkgConfig REQUIRED)
    pkg_check_modules(wayland-client REQUIRED wayland-client)
    pkg_check_modules(wayland-cursor REQUIRED wayland-cursor)
    pkg_check_modules(xkbcommon REQUIRED xkbcommon)

    # Wayland protocols
    pkg_check_modules(WAYLAND_PROTOCOLS REQUIRED wayland-protocols>=1.25)
    pkg_get_variable(WAYLAND_PROTOCOLS_BASE wayland-protocols pkgdatadir)

    execute_process(COMMAND "scripts/gen_wl_protocols.sh" OUTPUT_VARIABLE WAYLAND_PROTOCOLS_SRC)

    target_include_directories(lvgl PRIVATE ${PROJECT_SOURCE_DIR} "${PROJECT_SOURCE_DIR}/wl_protocols")
    add_executable(blackpiTacho "${MY_SOURCES}" "${MY_ASSETS}" ${WAYLAND_PROTOCOLS_SRC} backends/wayland.c)
    target_compile_definitions(blackpiTacho PRIVATE LV_CONF_INCLUDE_SIMPLE)
    target_compile_options(blackpiTacho PRIVATE ${GLIB_LDFLAGS} ${GATTLIB_LDFLAGS} )

    target_link_libraries(blackpiTacho lvgl lvgl::thorvg m jansson wayland-client wayland-cursor xkbcommon ${PCRE_LIBRARIES} gattlib )

else()

    # No specific build steps required for FBDEV
    add_executable(blackpiTacho "${MY_SOURCES}" "${MY_ASSETS}")
    target_link_libraries(blackpiTacho lvgl lvgl::examples lvgl::demos lvgl::thorvg m pthread jansson)
endif()

add_custom_target (run COMMAND ${EXECUTABLE_OUTPUT_PATH}/blackpiTacho DEPENDS blackpiTacho)
