# Copyright (c) 2017, Open Communications Security
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
# This module let's the change of the CRT used by the compiler when using MSVC.
# When the option MSVC_STATIC_CRT is set to ON, the default /MD flag will be
# replaced by the /MT flag. Furthermore, the variable MSVC_CRT_FLAG will hold
# the name of the flag used "MD" or "MT".
#
# On Windows, it also defined the variable WIN32_TARGET_PLATFORM that contains
# "x86" for 32 bits or "x64" for 64-bits.
#
if(__OPENCS_MSVCCRT)
  return()
endif()
set(__OPENCS_MSVCCRT 1)

if (WIN32)
	# Platform
	if (MSVC)
		if(CMAKE_FORCE_WIN64)
			set(WIN32_TARGET_PLATFORM "x64")
		else()
			set(WIN32_TARGET_PLATFORM "x86")
		endif()
	else()
		if(CMAKE_CL_64)
			set(WIN32_TARGET_PLATFORM "x64")
		else()
			set(WIN32_TARGET_PLATFORM "x86")
		endif()
	endif()
	message(STATUS "WIN32 Target Platform: ${WIN32_TARGET_PLATFORM}")
	
	# MSVC CRT
	if (MSVC)
		if( NOT DEFINED MSVC_STATIC_CRT)
			option(MSVC_STATIC_CRT "Instructs the compiler to use the static CRT instead of the dynamic one." 0)
		endif()
		if (MSVC_STATIC_CRT)
			set(MSVC_CRT_FLAG "MT")
			foreach(lang C CXX)
				foreach (flag_var
						CMAKE_${lang}_FLAGS
						CMAKE_${lang}_FLAGS_DEBUG
						CMAKE_${lang}_FLAGS_DEBUG_INIT
						CMAKE_${lang}_FLAGS_INIT
						CMAKE_${lang}_FLAGS_MINSIZEREL
						CMAKE_${lang}_FLAGS_MINSIZEREL_INIT
						CMAKE_${lang}_FLAGS_RELEASE
						CMAKE_${lang}_FLAGS_RELEASE_INIT
						CMAKE_${lang}_FLAGS_RELWITHDEBINFO
						CMAKE_${lang}_FLAGS_RELWITHDEBINFO_INIT
						)
					string(REPLACE "/MDd " "/MTd " ${flag_var} "${${flag_var}}")
					string(REPLACE "/MD " "/MT " ${flag_var} "${${flag_var}}")
				endforeach()
			endforeach()
		else()
			set(MSVC_CRT_FLAG "MD")
		endif()
		message(STATUS "MSVC CRT flag: ${MSVC_CRT_FLAG}.")
	endif()	
endif()
