/*
 * Copyright (c) 2017, The Bifrost Authors. All rights reserved.
 *
 * Redistribution and use in source and binary forms, with or without
 * modification, are permitted provided that the following conditions
 * are met:
 * * Redistributions of source code must retain the above copyright
 *   notice, this list of conditions and the following disclaimer.
 * * Redistributions in binary form must reproduce the above copyright
 *   notice, this list of conditions and the following disclaimer in the
 *   documentation and/or other materials provided with the distribution.
 * * Neither the name of The Bifrost Authors nor the names of its
 *   contributors may be used to endorse or promote products derived
 *   from this software without specific prior written permission.
 *
 * THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS'' AND ANY
 * EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
 * IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
 * PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
 * CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
 * EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
 * PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
 * PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
 * OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
 * (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
 * OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.
 */

#ifndef BF_TBN_READER_H_INCLUDE_GUARD_
#define BF_TBN_READER_H_INCLUDE_GUARD_

#ifdef __cplusplus
extern "C" {
	#endif
	
	#include <bifrost/ring.h>
	
	typedef struct BFtbnreader_impl* BFtbnreader;
	
	typedef int (*BFtbnreader_sequence_callback)(BFoffset, BFoffset, int, int,
	                                             void const**, size_t*);
	
	typedef enum BFtbnreader_status_ {
		BF_READ_STARTED,
		BF_READ_ENDED,
		BF_READ_CONTINUED,
		BF_READ_CHANGED,
		BF_READ_NO_DATA,
		BF_READ_INTERRUPTED,
		BF_READ_ERROR
	} BFtbnreader_status;
	
	BFstatus bfTbnReaderCreate(BFtbnreader* obj,
	                           int           fd,
	                           BFring        ring,
	                           BFsize        nsrc,
	                           BFsize        src0,
	                           BFsize        buffer_ntime,
	                           BFsize        slot_ntime,
	                           BFtbnreader_sequence_callback sequence_callback,
	                           int           core);
	BFstatus bfTbnReaderDestroy(BFtbnreader obj);
	BFstatus bfTbnReaderRead(BFtbnreader obj, BFtbnreader_status* result);
	BFstatus bfTbnReaderFlush(BFtbnreader obj);
	BFstatus bfTbnReaderEnd(BFtbnreader obj);
	
	#ifdef __cplusplus
} // extern "C"
#endif

#endif // BF_TBN_READER_H_INCLUDE_GUARD_