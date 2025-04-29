cmake_minimum_required(VERSION 3.10)
project(test_reaction)

find_package(PkgConfig REQUIRED)
pkg_check_modules(PARTED REQUIRED libparted)

set(SOURCE
    test.c
    ..sys/core.c
    ..sys/fat32.c
)
add_executable(test ${SOURCE})
target_include_directories(test PRIVATE ../ ${PARTED_INCLUDE_DIRS})
target_link_libraries(test PRIVATE ${PARTED_LIBRARIES})
target_compile_options(test PRIVATE ${PARTED_CFLAG_OTHER})
