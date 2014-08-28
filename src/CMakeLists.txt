set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")
if(ENABLE_WERROR)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror")
endif()

set(CMAKE_SHARED_LINKER_FLAGS "-Wl,--no-undefined ${CMAKE_SHARED_LINKER_FLAGS}")

##############################################################################

find_package(PkgConfig REQUIRED)
pkg_check_modules(x11 REQUIRED x11)
pkg_check_modules(sde_utils REQUIRED sde-utils-1.0>=0.1)

##############################################################################

include_directories(
    ${x11_INCLUDE_DIRS}
    ${sde_utils_INCLUDE_DIRS}
)

add_definitions(
    -DPACKAGE_INSTALLATION_PREFIX=\"${CMAKE_INSTALL_PREFIX}\"
    ${x11_CFLAGS}
    ${sde_utils_CFLAGS}
)

link_directories(
    ${x11_pixbuf_LIBRARY_DIRS}
    ${sde_utils_LIBRARY_DIRS}
)

add_library(sde-utils-x11-1.0 SHARED
    atoms.c
    utils.c
)

target_link_libraries(sde-utils-x11-1.0
    ${x11_LIBRARIES}
    ${sde_utils_LIBRARIES}
)

##############################################################################

file(GLOB headers ${CMAKE_CURRENT_SOURCE_DIR}/*.h)
install(FILES ${headers} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/sde-utils-x11-1.0/sde-utils-x11)
install(FILES sde-utils-x11.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/sde-utils-x11-1.0)
install(TARGETS sde-utils-x11-1.0 LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/)

