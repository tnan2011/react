cmake_minimum_required(VERSION 3.10)

project(reaction-gui LANGUAGES C CXX)
set(CMAKE_C_STANDARD 99)
set(CMAKE_CXX_STANDARD 17)

set(
    SOURCE_FILE
    src/main.cc
    src/mainWindow.hpp

    src/utils/utils.hpp
    src/utils/utils.cc

    src/gui/window.cc

    src/gui/init.cc
    src/gui/init.hpp

    src/gui/label.cc
    src/gui/include/label.hpp

    src/gui/buttons.cc
    src/gui/include/buttons.hpp

    src/gui/include/dropbox.hpp
    src/gui/dropbox.cc

    src/gui/include/progress.hpp
    src/gui/progress.cc

    src/common/include/signal.hpp
    src/common/include/props.hpp

    src/common/context.cc
    src/common/include/context.hpp
    src/common/process.cc

    src/common/include/message.hpp
    src/common/include/process.hpp
)

find_package(Qt6 COMPONENTS Widgets REQUIRED)
find_package(PkgConfig REQUIRED)
pkg_check_modules(UDEV REQUIRED libudev)
set(CMAKE_AUTOMOC ON)

add_executable(${PROJECT_NAME} ${SOURCE_FILE})

target_compile_options(${PROJECT_NAME} PRIVATE "$<$<CXX_COMPILER_ID:Clang>:-fno-direct-access-external-data>")

target_link_libraries(${PROJECT_NAME} Qt6::Widgets ${UDEV_LIBRARIES})
target_include_directories(${PROJECT_NAME} PRIVATE ${UDEV_INCLUDE_DIR})
