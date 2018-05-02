# Copyright (c) 2017-2018, Open Communications Security
# All rights reserved.
# 
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#     * Redistributions of source code must retain the above copyright
#       notice, this list of conditions and the following disclaimer.
#     * Redistributions in binary form must reproduce the above copyright
#       notice, this list of conditions and the following disclaimer in the
#       documentation and/or other materials provided with the distribution.
#     * Neither the name of the <organization> nor the
#       names of its contributors may be used to endorse or promote products
#       derived from this software without specific prior written permission.
# 
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
# ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
# WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
# DISCLAIMED. IN NO EVENT SHALL OPEN COMMUNICATIONS SECURITY BE LIABLE FOR ANY
# DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
# (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
# LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
# ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
# SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
#
# ==============================================================================
# This module locates the GTest and GMock libraries from Google. It replaces
# the FindGTest module included with CMake.
#
# The main advantage of this module is the ability to control the usage of
# all possible MSVC compilation flags (/MT, /MTd, /MD and /MDd) as well as
# 32 and 64 bits while running under Windows.
#
# Targets:
#    - GTest
#    - GTest::Main
#    - GMock
#    - GMock::Main
#
# Variables:
#
#    - GTEST_FOUND
#    - GMOCK_FOUND
#    - GTEST_INCLUDE_DIR
#    - GTEST_LIB
#    - GTEST_MAIN_LIB
#    - GTESTD_LIB
#    - GTESTD_MAIN_LIB
#    - GMOCK_INCLUDE_DIR
#    - GMOCK_LIB
#    - GMOCK_MAIN_LIB
#    - GMOCKD_LIB
#    - GMOCKD_MAIN_LIB
#
# This method depends on MSVCCRT from OpenCS in order to work properly.
#
# History:
#    - 2018.02.14: Support to "-dbg" libraries on Linux added;
#
# Known limitations:
# 	- Not tested on MacOS
if(__OPENCS_GTEST)
  return()
endif()
set(__OPENCS_GTEST 1)

function(gtest_log _msg)
	if (GTEST_VERBOSE)
		message(STATUS ${_msg})
	endif()
endfunction()

# Check the dependency on 
if (NOT __OPENCS_MSVCCRT)
	message(FATAL_ERROR "OpenCS GTest module requires OpenCS MSVCCRT module in order to work properly.")
endif()

# Find the GoogleTest directory
if (NOT DEFINED GTEST_HOME)
	if(NOT "$ENV{GTEST_HOME}" STREQUAL "")
		set(GTEST_HOME "$ENV{GTEST_HOME}")
	elseif(NOT "$ENV{GTEST_ROOT}" STREQUAL "")
		set(GTEST_HOME "$ENV{GTEST_ROOT}")
	endif()
endif()

# Find the header location
if (DEFINED GTEST_HOME)
	find_path(GTEST_INCLUDE_DIR
		gtest/gtest.h
		HINTS "${GTEST_HOME}"
		PATH_SUFFIXES include)
	find_path(GMOCK_INCLUDE_DIR
		gmock/gmock.h
		HINTS "${GTEST_HOME}"
		PATH_SUFFIXES include)
else()
	find_path(GTEST_INCLUDE_DIR
		gtest/gtest.h)
	find_path(GMOCK_INCLUDE_DIR
		gmock/gmock.h)
endif()

if (NOT GTEST_INCLUDE_DIR)
	message(WARNING "GTest include directory not found.")
endif()
if (NOT GMOCK_INCLUDE_DIR)
	message(WARNING "GMock include directory not found.")
endif()

find_package(Threads REQUIRED)

if (WIN32)
	set(_GTEST_LIB_DIR "lib/${WIN32_TARGET_PLATFORM}/${MSVC_CRT_FLAG}")	
	foreach(_gtest_lib_title IN ITEMS GTEST GTEST_MAIN GMOCK GMOCK_MAIN)
		string(TOLOWER "${_gtest_lib_title}.lib" _gtest_lib_file)
		find_library(${_gtest_lib_title}_LIB
			${_gtest_lib_file} 
			PATHS "${GTEST_HOME}"
			PATH_SUFFIXES "${_GTEST_LIB_DIR}")
		find_library(${_gtest_lib_title}D_LIB
			${_gtest_lib_file} 
			PATHS "${GTEST_HOME}"
			PATH_SUFFIXES "${_GTEST_LIB_DIR}D")
	endforeach(_gtest_lib_title)
else()
	foreach(_gtest_lib_title IN ITEMS GTEST GTEST_MAIN GMOCK GMOCK_MAIN)
		string(TOLOWER "lib${_gtest_lib_title}" _gtest_lib_file)
		find_library(${_gtest_lib_title}_LIB
			${_gtest_lib_file}.a)
		find_library(${_gtest_lib_title}D_LIB
			${_gtest_lib_file}-dbg.a)
		if (NOT ${_gtest_lib_title}D_LIB)
			set(${_gtest_lib_title}D_LIB ${${_gtest_lib_title}_LIB})
		endif()
	endforeach(_gtest_lib_title)
	# On Linux, it will require threads
endif()

if (GTEST_INCLUDE_DIR)
	gtest_log("GTest headers found at ${GTEST_INCLUDE_DIR}.")
	if(NOT TARGET GTest)
		add_library(GTest UNKNOWN IMPORTED)
		set_target_properties(GTest PROPERTIES
			INTERFACE_INCLUDE_DIRECTORIES "${GTEST_INCLUDE_DIR}")
        	set_target_properties(GTest PROPERTIES
		            INTERFACE_LINK_LIBRARIES "Threads::Threads")
		if (GTEST_LIB)
			set_property(TARGET GTest APPEND PROPERTY
				IMPORTED_CONFIGURATIONS RELEASE)
			set_target_properties(GTest PROPERTIES
				IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
				IMPORTED_LOCATION_RELEASE "${GTEST_LIB}")
			gtest_log("GTest release lib found at ${GTEST_LIB}.")
		endif()
		if (GTESTD_LIB)
			set_property(TARGET GTest APPEND PROPERTY
				IMPORTED_CONFIGURATIONS DEBUG)
			set_target_properties(GTest PROPERTIES
				IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
				IMPORTED_LOCATION_DEBUG "${GTESTD_LIB}")		
			gtest_log("GTest debug lib found at ${GTESTD_LIB}.")
		endif()
	endif()
	if(NOT TARGET GTest::Main)
		add_library(GTest::Main UNKNOWN IMPORTED)
		set_target_properties(GTest::Main PROPERTIES
			INTERFACE_INCLUDE_DIRECTORIES "${GTEST_INCLUDE_DIR}")
		if (GTEST_MAIN_LIB)
			set_property(TARGET GTest::Main APPEND PROPERTY
				IMPORTED_CONFIGURATIONS RELEASE)
			set_target_properties(GTest::Main PROPERTIES
				IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
				IMPORTED_LOCATION_RELEASE "${GTEST_MAIN_LIB}")
			gtest_log("GTest Main release lib found at ${GTEST_MAIN_LIB}.")
		endif()
		if(GTEST_MAIND_LIB)
			set_property(TARGET GTest::Main APPEND PROPERTY
				IMPORTED_CONFIGURATIONS DEBUG)
			set_target_properties(GTest::Main PROPERTIES
				IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
				IMPORTED_LOCATION_DEBUG "${GTEST_MAIND_LIB}")		
			gtest_log("GTest Main debug lib found at ${GTEST_MAIND_LIB}.")
		endif()
	endif()
	set(GTEST_FOUND 1)
endif()

if (GMOCK_INCLUDE_DIR)
	gtest_log("GMock headers found at ${GMOCK_INCLUDE_DIR}.")
	if(NOT TARGET GMock)
		add_library(GMock UNKNOWN IMPORTED)
		set_target_properties(GMock PROPERTIES
			INTERFACE_INCLUDE_DIRECTORIES "${GMOCK_INCLUDE_DIR}")
        	set_target_properties(GTest PROPERTIES
		            INTERFACE_LINK_LIBRARIES "Threads::Threads")
		if (GMOCK_LIB)
			set_property(TARGET GMock APPEND PROPERTY
				IMPORTED_CONFIGURATIONS RELEASE)
			set_target_properties(GMock PROPERTIES
				IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
				IMPORTED_LOCATION_RELEASE "${GMOCK_LIB}")
			gtest_log("GMock lib release found at ${GMOCK_LIB}.")
		endif()
		if (GMOCKD_LIB)
			set_property(TARGET GMock APPEND PROPERTY
				IMPORTED_CONFIGURATIONS DEBUG)
			set_target_properties(GMock PROPERTIES
				IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
				IMPORTED_LOCATION_DEBUG "${GMOCKD_LIB}")		
			gtest_log("GMock lib debug found at ${GMOCKD_LIB}.")
		endif()
	endif()
	if(NOT TARGET GMock::Main)
		add_library(GMock::Main UNKNOWN IMPORTED)
		set_target_properties(GMock::Main PROPERTIES
			INTERFACE_INCLUDE_DIRECTORIES "${GMOCK_INCLUDE_DIR}")
		set_property(TARGET GTest::Main APPEND PROPERTY
			IMPORTED_CONFIGURATIONS RELEASE)
		set_target_properties(GMock::Main PROPERTIES
			IMPORTED_LINK_INTERFACE_LANGUAGES_RELEASE "CXX"
			IMPORTED_LOCATION_RELEASE "${GMOCK_MAIN_LIB}")
		set_property(TARGET GMock::Main APPEND PROPERTY
			IMPORTED_CONFIGURATIONS DEBUG)
		set_target_properties(GMock::Main PROPERTIES
			IMPORTED_LINK_INTERFACE_LANGUAGES_DEBUG "CXX"
			IMPORTED_LOCATION_DEBUG "${GMOCKD_MAIN_LIB}")		
	endif()
	set(GMOCK_FOUND 1)
endif()
