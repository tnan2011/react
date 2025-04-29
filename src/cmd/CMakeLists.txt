cmake_minimum_required(VERSION 3.10)
project(reaction-cli)

find_package(PkgConfig REQUIRED)
pkg_check_modules(PARTED REQUIRED libparted)
set(
    SOURCE

    sys/core.c
    sys/fat32.c

    cmd.c
    main.c 
)

add_executable(${PROJECT_NAME} ${SOURCE})
target_include_directories(${PROJECT_NAME} PRIVATE ../ ${PARTED_INCLUDE_DIRS})
target_link_libraries(${PROJECT_NAME} PRIVATE ${PARTED_LIBRARIES})
target_compile_options(${PROJECT_NAME} PRIVATE ${PARTED_CFLAG_OTHER})
