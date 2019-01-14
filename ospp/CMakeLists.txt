file(GLOB_RECURSE libsrc *.h *.cpp *.hpp *.c *.cc)

set(target_name ospp)

add_library(${target_name} ${libsrc})

target_compile_definitions(${target_name} PRIVATE GLFW_BACKEND)

target_link_libraries(${target_name} PRIVATE SDL2)
target_link_libraries(${target_name} PRIVATE glfw)
target_link_libraries(${target_name} PRIVATE mml-window)


target_include_directories(${target_name}
    PUBLIC
		${CMAKE_CURRENT_SOURCE_DIR}/..
)
set_target_properties(${target_name} PROPERTIES
    CXX_STANDARD 14
    CXX_STANDARD_REQUIRED YES
    CXX_EXTENSIONS NO
    POSITION_INDEPENDENT_CODE ON
    WINDOWS_EXPORT_ALL_SYMBOLS ON
)
