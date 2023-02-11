cmake_minimum_required(VERSION 3.12)

add_executable (helium-plus-plus-main "main/heliumpp.main.ixx")

set_property(TARGET helium-plus-plus-main PROPERTY CXX_STANDARD 23)

find_path(NEARGYE_SEMVER_INCLUDE_DIRS "neargye/semver.hpp")
target_include_directories(helium-plus-plus-main PRIVATE ${NEARGYE_SEMVER_INCLUDE_DIRS})