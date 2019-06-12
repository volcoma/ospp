file(GLOB libsrc *.h *.cpp *.hpp *.c *.cc)

set(target_name ospp)

message( STATUS "--------------------------------" )
if("${BACKEND_TYPE}" STREQUAL "SDL")
	message( STATUS "SDL backend selected." )
	file(GLOB impl_src ${CMAKE_CURRENT_SOURCE_DIR}/impl/sdl/*)

elseif("${BACKEND_TYPE}" STREQUAL "GLFW")
	message( STATUS "GLFW backend selected." )
	file(GLOB impl_src ${CMAKE_CURRENT_SOURCE_DIR}/impl/glfw/*)

elseif("${BACKEND_TYPE}" STREQUAL "MML")
	message( STATUS "MML backend selected." )
	file(GLOB impl_src ${CMAKE_CURRENT_SOURCE_DIR}/impl/mml/*)
else()
	message( FATAL_ERROR "No backend type was selected." )
endif()
message( STATUS "--------------------------------" )

list(APPEND libsrc ${impl_src})

add_library(${target_name} ${libsrc})

if("${BACKEND_TYPE}" STREQUAL "SDL")
	target_compile_definitions(${target_name} PRIVATE SDL_BACKEND)
	if(BUILD_SHARED_LIBS)
		target_link_libraries(${target_name} PRIVATE SDL2)
	else()
		target_link_libraries(${target_name} PRIVATE SDL2-static)
	endif()
	target_link_libraries(${target_name} PUBLIC ${CMAKE_DL_LIBS})

elseif("${BACKEND_TYPE}" STREQUAL "GLFW")
	target_compile_definitions(${target_name} PRIVATE GLFW_BACKEND)
	if(WIN32)
		target_compile_definitions(${target_name} PRIVATE GLFW_EXPOSE_NATIVE_WIN32)
	elseif(APPLE)
		target_compile_definitions(${target_name} PRIVATE GLFW_EXPOSE_NATIVE_COCOA)
	else()
		#target_compile_definitions(${target_name} PRIVATE GLFW_EXPOSE_NATIVE_WAYLAND)
		#target_compile_definitions(${target_name} PRIVATE GLFW_EXPOSE_NATIVE_MIR)
		target_compile_definitions(${target_name} PRIVATE GLFW_EXPOSE_NATIVE_X11)
	endif()
	target_link_libraries(${target_name} PRIVATE glfw)
    target_link_libraries(${target_name} PUBLIC ${CMAKE_DL_LIBS})


elseif("${BACKEND_TYPE}" STREQUAL "MML")
	target_compile_definitions(${target_name} PRIVATE MML_BACKEND)

	target_link_libraries(${target_name} PRIVATE mml-window)
endif()

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
