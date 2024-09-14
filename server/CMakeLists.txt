cmake_minimum_required(VERSION 3.16)

project(server LANGUAGES CXX)

set(CMAKE_AUTOUIC ON)
set(CMAKE_AUTOMOC ON)
set(CMAKE_AUTORCC ON)

set(CMAKE_CXX_STANDARD 17)
set(CMAKE_CXX_STANDARD_REQUIRED ON)

set(Boost_INCLUDE_DIR "../boost_1_82_0")

include_directories(${Boost_INCLUDE_DIR})
link_directories(${Boost_INCLUDE_DIR})

find_package(QT NAMES Qt6 Qt5 REQUIRED COMPONENTS Core)
find_package(Qt${QT_VERSION_MAJOR} REQUIRED COMPONENTS Core)

add_executable(server
  main.cpp
  server.h server.cpp
)

target_link_libraries(server Qt${QT_VERSION_MAJOR}::Core)

if(WIN32)
    target_link_libraries(server ws2_32)
endif()

include(GNUInstallDirs)
install(TARGETS server
    LIBRARY DESTINATION ${CMAKE_INSTALL_LIBDIR}
    RUNTIME DESTINATION ${CMAKE_INSTALL_BINDIR}
)
