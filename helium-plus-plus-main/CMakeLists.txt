cmake_minimum_required(VERSION 3.12)

set(Boost_USE_STATIC_LIBS ON)
set(Boost_USE_STATIC_RUNTIME ON)
set(Boost_INCLUDE_DIR ${_VCPKG_INSTALLED_DIR}/x64-windows/include)
set_property(GLOBAL PROPERTY USE_FOLDERS ON)

if(MSVC)
    add_definitions(-D_WIN32_WINNT=0x0601)
endif(MSVC)

find_package(Boost COMPONENTS system REQUIRED)
if (Boost_FOUND)
    include_directories(${Boost_INCLUDE_DIRS})
    link_directories(${Boost_LIBRARY_DIRS})
endif ()

find_package(fmt REQUIRED)
find_package(Boost REQUIRED)
find_package(Microsoft.GSL REQUIRED)
find_package(ftxui REQUIRED)
find_package(mdspan CONFIG REQUIRED)

find_path(NEARGYE_SEMVER_INCLUDE_DIR NAMES semver.hpp PATH_SUFFIXES neargye)

add_executable (helium-plus-plus-main 
    "main/heliumpp.main.ixx" 
    "shared/heliumpp.shared.ixx")

set_property(TARGET helium-plus-plus-main PROPERTY CXX_STANDARD 23)

include_directories(${NEARGYE_SEMVER_INCLUDE_DIR})

target_link_libraries(helium-plus-plus-main
    PRIVATE
        fmt::fmt
        ftxui::component
        ftxui::dom
        ftxui::screen
        std::mdspan
        Microsoft.GSL::GSL
        ${Boost_LIBRARIES})