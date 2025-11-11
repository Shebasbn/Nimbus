# CMakeList.txt : CMake project for Nimbus, include source and define
# project specific logic here.
#
cmake_minimum_required(VERSION 3.11)
set(PROJECT Nimbus)

# Add source to this project.
set(SOURCES 
	"Source/Core/Application.h"
	"Source/Core/Application.cpp"
	"Source/Core/Core.h"
	"Source/Core/EntryPoint.h"
	"Source/Nimbus.h" 
	"Source/Core/Log.h"
	"Source/Core/Log.cpp"
	"Source/Core/Event/Event.h"
	"Source/Core/Event/ApplicationEvent.h"
	"Source/Core/Event/KeyEvent.h"
	"Source/Core/Event/MouseEvent.h" 
	"Source/Core/Layer.h" 
	"Source/Core/Layer.cpp" 
	"Source/Core/LayerStack.cpp" 
	"Source/Core/LayerStack.h" 
	"Source/Core/Window.h" 
	"Source/Platform/Windows/WindowsWindow.h" "Source/Platform/Windows/WIndowsWindow.cpp")

#set (CMAKE_ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}")

#if(NOT TARGET spdlog)
   # Stand-alone build
 #   find_package(spdlog REQUIRED)
#endif()
add_subdirectory(${CMAKE_CURRENT_SOURCE_DIR}/vendor/spdlog)
add_library (${PROJECT} STATIC)

set_target_properties(${PROJECT} PROPERTIES
    ARCHIVE_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${CMAKE_BUILD_TYPE}/${PROJECT}"
)

target_sources(${PROJECT} PRIVATE ${SOURCES})

target_precompile_headers(${PROJECT} PRIVATE "Source/nbpch.h")

target_include_directories(${PROJECT} PRIVATE 
						   "${CMAKE_CURRENT_SOURCE_DIR}/Source/Core"
						   "${CMAKE_CURRENT_SOURCE_DIR}/Source")

target_link_libraries(${PROJECT} PUBLIC spdlog)
#message(STATUS "HI ${CMAKE_CURRENT_SOURCE_DIR}/Source/Core")
#include_directories(${CMAKE_CURRENT_SOURCE_DIR}/Source)

if(WIN32)
	add_compile_definitions(NB_PLATFORM_WINDOWS=1 _UNICODE UNICODE)
	target_compile_definitions(${PROJECT} PRIVATE
		$<IF:$<CONFIG:Debug>, NB_ENABLE_ASSERTS=1, ""> )
endif()

#target_compile_definitions(PROJECT PUBLIC NB_BUILD_DLL=0)

# Match VS filters to directory structure on disk
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SOURCES})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET ${PROJECT} PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
