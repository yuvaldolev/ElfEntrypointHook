cmake_minimum_required(VERSION 3.18.0)

project(elf_entrypoint_hook VERSION 0.1.0)

# set(DOBBY_GENERATE_SHARED OFF)
set(CMAKE_POSITION_INDEPENDENT_CODE ON)

add_subdirectory(third_party)

add_library(hook
    SHARED
    src/elf_util.cpp
    src/elf_util.hpp
    src/lib.cpp
)

target_include_directories(hook
    PRIVATE
    ${CMAKE_SOURCE_DIR}
)

target_link_libraries(hook
    PRIVATE
    inline-hook
)

set_target_properties(hook
    PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)

add_executable(main
    src/main.cpp
)

set_target_properties(main
    PROPERTIES
    CXX_STANDARD 20
    CXX_STANDARD_REQUIRED ON
)

target_link_libraries(main
    PRIVATE
    hook
)
