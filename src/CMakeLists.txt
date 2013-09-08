set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Wall -Wextra")
if(ENABLE_WERROR)
    set(CMAKE_C_FLAGS "${CMAKE_C_FLAGS} -Werror")
endif()

set(CMAKE_SHARED_LINKER_FLAGS "-Wl,--no-undefined ${CMAKE_SHARED_LINKER_FLAGS}")

##############################################################################

find_package(PkgConfig REQUIRED)
pkg_check_modules(gtk2 REQUIRED gtk+-2.0>=2.24)
pkg_check_modules(gdk_pixbuf REQUIRED gdk-pixbuf-2.0>=2.28)

##############################################################################

add_library(sde-utils-gtk-1.0 SHARED
    gdkrgba.c
    gdk-pixbuf.c
    config.c
)

##############################################################################

add_definitions(
    ${gtk2_CFLAGS}
    ${gtk2_CFLAGS}
)

link_directories(
    ${gtk2_pixbuf_LIBRARY_DIRS}
    ${gdk_pixbuf_LIBRARY_DIRS}
)

target_link_libraries(sde-utils-gtk-1.0
    ${gtk2_LIBRARIES}
    ${gdk_pixbuf_LIBRARIES}
)

##############################################################################

file(GLOB headers "${CMAKE_CURRENT_SOURCE_DIR}/sde-utils-gtk.h" "${CMAKE_CURRENT_SOURCE_DIR}/gdkrgba.h" "${CMAKE_CURRENT_SOURCE_DIR}/gdk-pixbuf.h")
install(FILES ${headers} DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/sde-utils-gtk-1.0/sde-utils-gtk)
install(FILES sde-utils-gtk.h DESTINATION ${CMAKE_INSTALL_INCLUDEDIR}/sde-utils-gtk-1.0)
install(TARGETS sde-utils-gtk-1.0 LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}/)

