# CMakeList.txt : CMake project for Nimbus, include source and define
# project specific logic here.
#

set(PROJECT Nimbus)

# Add source to this project.
set(SOURCES 
	"Source/Core/Application.h"
	"Source/Core/Application.cpp"
	"Source/Core/Core.h"
	"Source/Core/EntryPoint.h"
	"Source/Nimbus.h")

#set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}")

add_library (${PROJECT} STATIC)

set_target_properties(${PROJECT} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${PLATFORM}/${PROJECT}"
)

target_sources(${PROJECT} PRIVATE ${SOURCES})

target_include_directories(${PROJECT} PRIVATE "${CMAKE_CURRENT_SOURCE_DIR}/Source/Core")
#message(STATUS "HI ${CMAKE_CURRENT_SOURCE_DIR}/Source/Core")
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Source)

if(WIN32)
	add_compile_definitions(NB_PLATFORM_WINDOWS=1)
endif()

#target_compile_definitions(PROJECT PUBLIC NB_BUILD_DLL=0)

# Match VS filters to directory structure on disk
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SOURCES})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${PROJECT} PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
