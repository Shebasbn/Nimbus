# CMakeList.txt : CMake project for Nimbus, include source and define
# project specific logic here.
#
set(PROJECT Sandbox)

# Add source to this project's executable.
set(SOURCES
	"Source/Sandbox.cpp")

add_executable (Sandbox)

set_target_properties(Sandbox PROPERTIES
    RUNTIME_OUTPUT_DIRECTORY "${CMAKE_SOURCE_DIR}/bin/${PLATFORM}/${PROJECT}"
)

target_sources(Sandbox PRIVATE ${SOURCES})

# Match VS filters to directory structure on disk
source_group(TREE "${CMAKE_CURRENT_SOURCE_DIR}" FILES ${SOURCES})

target_link_libraries(Sandbox Nimbus)

target_include_directories(Sandbox PUBLIC "${CMAKE_SOURCE_DIR}/Nimbus/Source")

# Set working directory for VS debugger
set_target_properties(Sandbox PROPERTIES
    VS_DEBUGGER_WORKING_DIRECTORY "${CMAKE_SOURCE_DIR}/Sandbox"
)

if (CMAKE_VERSION VERSION_GREATER 3.12)
  set_property(TARGET Nimbus PROPERTY CXX_STANDARD 20)
endif()

# TODO: Add tests and install targets if needed.
