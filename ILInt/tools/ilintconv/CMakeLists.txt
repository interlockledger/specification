# Copyright (c) 2018, Open Communications Security
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
cmake_minimum_required(VERSION 3.9)
project(ilintconv
	VERSION 0.1)

# Including the global modules
set(MSVC_STATIC_CRT 1)
include("cmake/MSVCCRT.cmake")

# GoogleTest
include("cmake/GTest.cmake")

configure_file (
	${CMAKE_CURRENT_SOURCE_DIR}/src/version.h.in
	${CMAKE_CURRENT_SOURCE_DIR}/src/version.h
)

add_executable(ilintconv
	src/errors.h
	src/errors.c
	src/ilint.h
	src/ilint.c
	src/options.h
	src/options.c
	src/utils.h
	src/utils.c
	src/main.c)

if(GTEST_FOUND)

add_executable(ilintconv-test
	src/errors.h
	src/errors.c
	src/ilint.h
	src/ilint.c
	src/options.h
	src/options.c
	src/utils.h
	src/utils.c
	test/OptionsTest.h
	test/UtilsTest.h
	test/UtilsTest.cpp
	test/OptionsTest.cpp
	test/main.cpp)

target_include_directories(ilintconv-test
	PRIVATE src)

target_link_libraries(ilintconv-test
	GTest)

endif()

