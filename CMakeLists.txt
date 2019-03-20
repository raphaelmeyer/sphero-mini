cmake_minimum_required(VERSION 3.10)

project(SpheroMini VERSION 0.0.1)

find_package(PkgConfig)
pkg_check_modules(DBUS dbus-glib-1)

add_executable(sm
  main.cc
)

target_compile_features(sm PRIVATE cxx_std_17)
target_compile_options(sm
  PRIVATE
    "-Wall"
    "-Werror"
)

target_link_libraries(sm
  PRIVATE
    ${DBUS_LIBRARIES}
)
target_include_directories(sm
  PRIVATE
    ${DBUS_INCLUDE_DIRS}
)

