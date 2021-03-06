/*
   Copyright (c) 2015, Max Krasnyansky <max.krasnyansky@gmail.com> 
   All rights reserved.
   
   Redistribution and use in source and binary forms, with or without modification,
   are permitted provided that the following conditions are met:
   
   1. Redistributions of source code must retain the above copyright notice,
      this list of conditions and the following disclaimer.
   
   2. Redistributions in binary form must reproduce the above copyright notice,
      this list of conditions and the following disclaimer in the documentation
      and/or other materials provided with the distribution.
   
   THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
   AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO,
   THE IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
   ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDER OR CONTRIBUTORS BE LIABLE
   FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR CONSEQUENTIAL DAMAGES
   (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES;
   LOSS OF USE, DATA, OR PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED
   AND ON ANY THEORY OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
   (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
   OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
*/

/**
 * @file hogl/platform.hpp
 * Platform specific features and functions.
 */
#ifndef HOGL_PLATFORM_HPP
#define HOGL_PLATFORM_HPP

namespace hogl {
namespace platform {

void set_thread_title(const char *str);

/**
 * Typically coredump files do not contain file-backed mappings.
 * Which means that hogl-recover tool will have to have access 
 * to the original executable and shared libraries in order to
 * find global strings.
 * This function enables verbose coredump which includes file-backed
 * mappings, if supported by your platform.
 * Note that this makes coredump files much larger.
 * @return true if successful, false otherwise.
 */
bool enable_verbose_coredump();

} // namespace platform
} // namespace hogl

#endif // HOGL_PLATFORM_HPP
