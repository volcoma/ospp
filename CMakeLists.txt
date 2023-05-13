cmake_minimum_required(VERSION 3.4.3)

project(ospp)
include(CTest)

option(BUILD_OSPP_SHARED "Build as a shared library." ON)
option(BUILD_OSPP_TESTS "Build the tests" ON)

set(BACKEND_TYPE "MML" CACHE STRING "Backend type chosen by the user at CMake configure time")
set_property(CACHE BACKEND_TYPE PROPERTY STRINGS SDL GLFW MML)

if(BUILD_OSPP_TESTS)
	if(NOT CMAKE_RUNTIME_OUTPUT_DIRECTORY)
		set(CMAKE_RUNTIME_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
	endif()
	if(NOT CMAKE_LIBRARY_OUTPUT_DIRECTORY)
		set(CMAKE_LIBRARY_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/bin)
	endif()
	if(NOT CMAKE_ARCHIVE_OUTPUT_DIRECTORY)
		set(CMAKE_ARCHIVE_OUTPUT_DIRECTORY ${PROJECT_BINARY_DIR}/lib)
    endif()

    # Second, for multi-config builds (e.g. msvc)
    foreach( OUTPUTCONFIG ${CMAKE_CONFIGURATION_TYPES} )
        string( TOUPPER ${OUTPUTCONFIG} OUTPUTCONFIG )
        set( CMAKE_RUNTIME_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_RUNTIME_OUTPUT_DIRECTORY} )
        set( CMAKE_ARCHIVE_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_ARCHIVE_OUTPUT_DIRECTORY} )
        set( CMAKE_LIBRARY_OUTPUT_DIRECTORY_${OUTPUTCONFIG} ${CMAKE_LIBRARY_OUTPUT_DIRECTORY} )
    endforeach( OUTPUTCONFIG CMAKE_CONFIGURATION_TYPES )

    message(STATUS "Enabled ${PROJECT_NAME} tests.")

endif()

if(BUILD_OSPP_SHARED)
	set(BUILD_SHARED_LIBS ON)
else()
	set(BUILD_SHARED_LIBS OFF)
endif()


add_subdirectory(3rdparty)
add_subdirectory(ospp)


if(BUILD_OSPP_TESTS)
	add_subdirectory(tests)
endif()
