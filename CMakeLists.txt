cmake_minimum_required(VERSION 3.18.0)

project(elf_entrypoint_hook VERSION 0.1.0)

set(CMAKE_INSTALL_RPATH_USE_LINK_PATH TRUE)

add_library(hook
    SHARED
    src/lib.cpp
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