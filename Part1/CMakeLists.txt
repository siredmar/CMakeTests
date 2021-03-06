cmake_minimum_required (VERSION 2.6)
project (Tutorial)
#########################
# Uninstall make target #
#########################
configure_file(
    "${CMAKE_CURRENT_SOURCE_DIR}/cmake_uninstall.cmake.in"
    "${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake"
    IMMEDIATE @ONLY)
add_custom_target(uninstall
    COMMAND ${CMAKE_COMMAND} -P ${CMAKE_CURRENT_BINARY_DIR}/cmake_uninstall.cmake)

###################
# Define creation #
###################
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

########################
# Setting output paths #
########################
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

################################################
# Including source and headers and building it #
################################################
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

##############################
# Installing the built stuff #
##############################
install (TARGETS Tutorial DESTINATION bin)
install (FILES "${PROJECT_BINARY_DIR}/inc/TutorialConfig.h" DESTINATION include)

#################################4
# Basic testing the application #
# Tests if the program does	    #
#  * run                        #
#  * not segfault               #
#  * returns 0                  #
#################################
include(CTest)

# Adding a single test manually
add_test (TutorialUsage ../bin/Tutorial)
set_tests_properties (TutorialUsage PROPERTIES PASS_REGULAR_EXPRESSION "Usage:.*number")

#define a macro to simplify adding tests, then use it
macro (do_test bin arg result)
	add_test (TutorialComp${arg} ${bin} ${arg})
	set_tests_properties (TutorialComp${arg}
	PROPERTIES PASS_REGULAR_EXPRESSION ${result})
endmacro (do_test)

# Adding tests via previously defined macro
do_test(../bin/Tutorial 25 "25 is 5")
do_test(../bin/Tutorial -25 "-25 is 0")
do_test(../bin/Tutorial 0.0001 "0.0001 is 0.01")
do_test(../bin/Tutorial a "Input must be an integer number!")

# ########################
# # Testing via CppUTest #
# ########################
# # Building test binary
# #add_subdirectory("${PROJECT_SOURCE_DIR}/UnitTest")
#
# # Perform tests with cpputest
# #set_target_properties(cpputest PROPERTIES EXCLUDE_FROM_DEFAULT_BUILD 1)
# # Function: Build test and add command to execute it via target 'test'
# function(add_test_without_ctest target)
#     add_subdirectory(${target})
#
#     if(NOT TARGET ${target})
#         return()
#     endif()
#
# 	message("II: 1")
#     #add_dependencies(test ${target})
#     add_custom_command(	TARGET UnitTest
# 						POST_BUILD
# 					COMMAND bash echo hello)#${CMAKE_RUNTIME_OUTPUT_DIRECTORY}/${target})
# 	message("II: 2")
# endfunction()
# add_custom_target(UnitTest)
# add_test_without_ctest(${PROJECT_SOURCE_DIR}/UnitTest)

add_subdirectory(UnitTest)
