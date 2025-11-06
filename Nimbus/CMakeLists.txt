# CMakeList.txt : CMake project for Nimbus, include source and define
# project specific logic here.
#

# Add source to this project.
set(SOURCES 
	"Source/Nimbus.h"
	"Source/Nimbus.cpp")

add_library (Nimbus STATIC)

target_sources(Nimbus PRIVATE ${SOURCES})

# Match VS filters to directory structure on disk
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SOURCES})

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Nimbus PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
