cmake_minimum_required (VERSION 2.6)
project (Tutorial)

# uninstall target
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)
add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)

# Some version information that gets put into defines
set (Tutorial_VERSION_MAJOR 1)
set (Tutorial_VERSION_MINOR 1)
# Set option that controls a define - see inc/TutorialConfig.h
option (USE_MYMATH "Use tutorial provided math implementation" ON)

# Write header file with variables and defines previously defined
configure_file (
	"${PROJECT_SOURCE_DIR}/inc/TutorialConfig.h.in"
	"${PROJECT_BINARY_DIR}/inc/TutorialConfig.h"
  )

# Set the path the binary will be located in
set(
 CMAKE_RUNTIME_OUTPUT_DIRECTORY
 ${CMAKE_HOME_DIRECTORY}/bin
 )
# Set the path libraries will be located in
set(
 CMAKE_LIBRARY_OUTPUT_DIRECTORY
 ${CMAKE_HOME_DIRECTORY}/lib
 )

# Add include directory
include_directories("${PROJECT_BINARY_DIR}/inc")

# Include this as library only if USE_MYMATH is being used
if (USE_MYMATH)
	# Add incldue directory
	include_directories("${PROJECT_SOURCE_DIR}/src/MathFunctions")
	# Added subdirectories get executed by cmake (see related CMakeLists.txt)
	add_subdirectory("${PROJECT_SOURCE_DIR}/src/MathFunctions")
	# Write EXTRA_LIBS variable with content
	set (EXTRA_LIBS ${EXTRA_LIBS} MathFunctions)
endif (USE_MYMATH)

# Initially define SOURCE variable with main program
set(SOURCE
    ${CMAKE_CURRENT_SOURCE_DIR}/src/tutorial.cxx
  )

# Added subdirectories get executed by cmake (see related CMakeLists.txt)
# and add the resulting executable
add_subdirectory("${PROJECT_SOURCE_DIR}/src/Test")
add_executable(Tutorial ${SOURCE})
target_link_libraries (Tutorial  ${EXTRA_LIBS})

# Installing the built stuff
install (TARGETS Tutorial DESTINATION bin)
install (FILES "${PROJECT_BINARY_DIR}/inc/TutorialConfig.h" DESTINATION include)
