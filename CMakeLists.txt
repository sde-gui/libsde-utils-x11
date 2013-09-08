cmake_minimum_required(VERSION 2.8)

project(libsde-utils-gtk)

option(ENABLE_WERROR "Enable -Werror flag for development" OFF)

include(GNUInstallDirs)

add_subdirectory(src)

configure_file(sde-utils-gtk-1.0.pc.in "${CMAKE_CURRENT_SOURCE_DIR}/sde-utils-gtk-1.0.pc" @ONLY)

install(FILES sde-utils-gtk-1.0.pc DESTINATION ${CMAKE_INSTALL_LIBDIR}/pkgconfig)
install(FILES cfg/settings.ini DESTINATION /usr/share/sde-config/sde-utils-gtk/)
