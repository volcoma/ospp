file(GLOB_RECURSE libsrc *.h *.cpp *.hpp *.c *.cc)

set(target_name ospp)

add_library(${target_name} ${libsrc})

message( STATUS "--------------------------------" )

if("${BACKEND_TYPE}" STREQUAL "SDL")
	message( STATUS "SDL backend selected." )
	target_compile_definitions(${target_name} PRIVATE SDL_BACKEND)
elseif("${BACKEND_TYPE}" STREQUAL "GLFW")
	message( STATUS "GLFW backend selected." )
	target_compile_definitions(${target_name} PRIVATE GLFW_BACKEND)
elseif("${BACKEND_TYPE}" STREQUAL "MML")
	message( STATUS "MML backend selected." )
	target_compile_definitions(${target_name} PRIVATE MML_BACKEND)
else()
	message( FATAL_ERROR "No backend type was selected." )
endif()
message( STATUS "--------------------------------" )


if(BUILD_SHARED_LIBS)
	target_link_libraries(${target_name} PRIVATE SDL2)
else()
	target_link_libraries(${target_name} PRIVATE SDL2-static)
endif()
target_link_libraries(${target_name} PRIVATE glfw)
if(WIN32)
	target_compile_definitions(${target_name} PRIVATE GLFW_EXPOSE_NATIVE_WIN32)
elseif(APPLE)
	target_compile_definitions(${target_name} PRIVATE GLFW_EXPOSE_NATIVE_COCOA)
else()
	#target_compile_definitions(${target_name} PRIVATE GLFW_EXPOSE_NATIVE_WAYLAND)
	#target_compile_definitions(${target_name} PRIVATE GLFW_EXPOSE_NATIVE_MIR)
	target_compile_definitions(${target_name} PRIVATE GLFW_EXPOSE_NATIVE_X11)
    target_link_libraries(${target_name} PUBLIC ${CMAKE_DL_LIBS})
endif()
target_link_libraries(${target_name} PRIVATE mml-window)


target_compile_definitions(${target_name} PRIVATE OS_NO_EXCEPTIONS)

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
