/*
 * Copyright (c) 2018, Open Communications Security
 * All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions are met:
 *     * Redistributions of source code must retain the above copyright
 *       notice, this list of conditions and the following disclaimer.
 *     * Redistributions in binary form must reproduce the above copyright
 *       notice, this list of conditions and the following disclaimer in the
 *       documentation and/or other materials provided with the distribution.
 *     * Neither the name of the <organization> nor the
 *       names of its contributors may be used to endorse or promote products
 *       derived from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS" AND
 * ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE IMPLIED
 * WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE ARE
 * DISCLAIMED. IN NO EVENT SHALL OPEN COMMUNICATIONS SECURITY BE LIABLE FOR ANY
 * DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
 * (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
 * LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND
 * ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE OF THIS
 * SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */
#ifndef _errors_H_
#define _errors_H_

#ifdef __cplusplus
extern "C" {
#endif // __cplusplus

/**
 * Error code for success.
 */
#define ERR_SUCCESS 0
/**
 * Error code for an unknown option.
 */
#define ERR_UNKNOWN_OPTION 1
/**
 * Error code for too many options.
 */
#define ERR_TOO_MANY_OPTIONS 2
/**
 * Error code for input too long.
 */
#define ERR_VALUE_TOO_LONG 3
/**
 * Error code used for missing input.
 */
#define ERR_VALUE_MISSING 4
/**
 * Error code used when the input is invalid.
 */
#define ERR_INVALID_VALUE 5
/**
 * Error code used when the conversion is not possible.
 */
#define ERR_UNABLE_TO_CONVERT 6

/**
 * This function returns the message associated for a
 * given error code.
 *
 * @param[in] code The error code.
 * @return The error message associated with it.
 */
const char * errors_getMessage(int code);

#ifdef __cplusplus
} // extern "C"
#endif // __cplusplus

#endif /* _errors_H_ */
