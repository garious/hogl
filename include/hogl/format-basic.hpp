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
 * @file hogl/format-basic.h
 * Basic format handler.
 */
#ifndef HOGL_FORMAT_BASIC_HPP
#define HOGL_FORMAT_BASIC_HPP

#include <hogl/detail/format.hpp>
#include <hogl/detail/ostrbuf.hpp>
#include <hogl/detail/timestamp.hpp>

namespace hogl {

/**
 * Basic format handler.
 * Simple and efficient handler for generating text output.
 */
class format_basic : public format {
public:
	enum Fields {
		TIMESPEC  = (1<<0),
		TIMESTAMP = (1<<1),
		TIMEDELTA = (1<<2),
		RING      = (1<<3),
		SEQNUM    = (1<<4),
		AREA      = (1<<5),
		SECTION   = (1<<6),
		RECDUMP   = (1<<7),
		DEFAULT = (TIMESTAMP | RING | SEQNUM | AREA | SECTION),
	        FAST0   = (TIMESPEC | RING | SEQNUM | AREA | SECTION),
	        FAST1   = (TIMESPEC | TIMEDELTA | RING | SEQNUM | AREA | SECTION)
	};

	explicit format_basic(uint32_t fields = DEFAULT);
	explicit format_basic(const char *fields);

	virtual void process(ostrbuf &s, const format::data &d);

	// Timespec cache
	struct tscache {
		enum {
			NSEC_SPLIT  = 10000,
			NSEC_HI_LEN = 5,
			NSEC_LEN    = 9,
			NSEC_LO_LEN = NSEC_LEN - NSEC_HI_LEN,
			SEC_LEN     = 11,
			TS_LEN      = SEC_LEN + 1 + NSEC_LEN,
			NSEC_HI_OFFSET = SEC_LEN + 1,
			NSEC_LO_OFFSET = NSEC_HI_OFFSET + NSEC_HI_LEN
		};

		time_t   _sec;
		uint32_t _nsec_hi;
		uint8_t  _str[TS_LEN];

		tscache(): _sec(0), _nsec_hi(0)
		{
			for (unsigned i=0; i<TS_LEN; i++) _str[i]='0';
			_str[SEC_LEN] = '.';
		}

		void update(hogl::timestamp t);
		const char *str() const  { return (const char *) _str; }
		unsigned int len() const { return TS_LEN; }
	};

protected:
	uint32_t  _fields;
	timestamp _last_timestamp;
	tscache   _tscache;

	void output_without_fmt(hogl::ostrbuf &sb, const record &r) const;
	void output_with_fmt(hogl::ostrbuf &sb, const record &r, unsigned int start_with = 0) const;
	virtual void output_raw(hogl::ostrbuf &sb, const record &r) const;

	void add_timespec(hogl::timestamp ts, uint8_t *str, unsigned int &i);

	void default_header(const format::data &d, ostrbuf &sb);
	void fast0_header(const format::data &d, ostrbuf &sb);
	void fast1_header(const format::data &d, ostrbuf &sb);
	void flexible_header(const format::data &d, ostrbuf &sb);
};

} // namespace hogl

#endif // HOGL_FORMAT_BASIC_HPP
