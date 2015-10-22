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

#include <stdio.h>
#include <stdint.h>
#include <stdlib.h>
#include <stdarg.h>
#include <string.h>
#include <unistd.h>
#include <errno.h>
#include <sys/uio.h>

#include <string>

#include "hogl/detail/ostrbuf-stdio.hpp"

namespace hogl {

void ostrbuf_stdio::do_flush(const uint8_t *data, size_t len)
{
	if (failed())
		return;

	// Flush buffered data
	if (_size)
		fwrite(_data, 1, _size, _file);

	// Flush un-buffered data
	if (len)
		fwrite(data, 1, len, _file);

	if (ferror(_file))
		ostrbuf::failure(strerror(errno));

	this->reset();
}

ostrbuf_stdio::ostrbuf_stdio(FILE *file, unsigned int flags, unsigned int buffer_capacity) :
	ostrbuf(buffer_capacity), _flags(flags), _file(file)
{ }

ostrbuf_stdio::~ostrbuf_stdio()
{
	if (_flags & CLOSE_ON_DELETE) {
		::fclose(_file);
		_file = 0;
	}
}

} // namespace hogl