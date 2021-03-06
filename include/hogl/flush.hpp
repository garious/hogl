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
 * @file hogl/flush.hpp
 * Top-level API for flushing log records.
 */
#ifndef HOGL_FLUSH_HPP
#define HOGL_FLUSH_HPP

#include <stdint.h>

#include <hogl/detail/compiler.hpp>
#include <hogl/detail/preproc.hpp>
#include <hogl/detail/timestamp.hpp>
#include <hogl/detail/ringbuf.hpp>

namespace hogl {

/*
 * Flush log records in a specific ring.
 * @param r ringbuf to flush
 * @param to_usec timeout in microseconds (default 10 seconds)
 * @return true on success, false on timeout
 */
bool flush(ringbuf *r, unsigned int to_usec = 10000000);

/*
 * Flush log records.
 * @param to_usec timeout in microseconds (default 10 seconds)
 * @return true on success, false on timeout
 */
bool flush(unsigned int to_usec = 10000000);

} // namespace hogl

#endif // HOGL_FLUSH_HPP
