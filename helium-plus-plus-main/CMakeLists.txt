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

find_package(Boost REQUIRED)
find_package(Microsoft.GSL REQUIRED)
find_package(ftxui REQUIRED)
find_package(spdlog CONFIG REQUIRED)
find_package(nameof CONFIG REQUIRED)
find_package(eventpp CONFIG REQUIRED)
find_package(mdspan CONFIG REQUIRED)
find_package(stduuid CONFIG REQUIRED)
find_package(unifex CONFIG REQUIRED)
find_package(tomlplusplus CONFIG REQUIRED)

find_path(NEARGYE_SEMVER_INCLUDE_DIR NAMES semver.hpp PATH_SUFFIXES neargye)

add_executable (helium-plus-plus-main 
    "main/heliumpp.main.ixx" 
    "shared/heliumpp.shared.ixx" 
    "events/heliumpp.events.ixx"
    "config/heliumpp.config.ixx" 
    "terminalui/heliumpp.terminalui.ixx" 
    "server/heliumpp.server.ixx" 
    "server/server/heliumpp.server.server.ixx" 
    "server/process_starter/heliumpp.server.process_starter.ixx" 
    "server/manager/heliumpp.server.manager.ixx" 
    "server/shared/heliumpp.server.shared.ixx" 
    "heliumpp.ixx" 
    "logger/heliumpp.logger.ixx" 
    "exception/heliumpp.exception.ixx" 
    "terminalui/component/command_input/heliumpp.terminalui.component.command_input.ixx" 
    "terminalui/component/logger_panel/heliumpp.terminalui.component.logger_panel.ixx"
    "terminalui/main/heliumpp.terminalui.main.ixx"
    "terminalui/component/settings_panel/heliumpp.terminalui.component.settings_panel.ixx" 
    "terminalui/shared/heliumpp.terminalui.shared.ixx"
    "terminalui/component/top_menu/heliumpp.terminalui.component.top_menu.ixx" "terminalui/animation/startup/heliumpp.terminalui.animation.startup.ixx")

set_property(TARGET helium-plus-plus-main PROPERTY CXX_STANDARD 23)

include_directories(${NEARGYE_SEMVER_INCLUDE_DIR})

target_link_libraries(helium-plus-plus-main
    PRIVATE
        ftxui::component
        ftxui::dom
        ftxui::screen
        std::mdspan
        Microsoft.GSL::GSL
        spdlog::spdlog_header_only
        unifex::unifex
        stduuid
        nameof::nameof
        eventpp::eventpp
        tomlplusplus::tomlplusplus
        ${Boost_LIBRARIES})