
# Copyright (c) 2017, The Bifrost Authors. All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions
# are met:
# * Redistributions of source code must retain the above copyright
#   notice, this list of conditions and the following disclaimer.
# * Redistributions in binary form must reproduce the above copyright
#   notice, this list of conditions and the following disclaimer in the
#   documentation and/or other materials provided with the distribution.
# * Neither the name of The Bifrost Authors nor the names of its
#   contributors may be used to endorse or promote products derived
#   from this software without specific prior written permission.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS ``AS IS'' AND ANY
# EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR
# PURPOSE ARE DISCLAIMED.  IN NO EVENT SHALL THE COPYRIGHT OWNER OR
# CONTRIBUTORS BE LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL,
# EXEMPLARY, OR CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO,
# PROCUREMENT OF SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR
# PROFITS; OR BUSINESS INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY
# OF LIABILITY, WHETHER IN CONTRACT, STRICT LIABILITY, OR TORT
# (INCLUDING NEGLIGENCE OR OTHERWISE) ARISING IN ANY WAY OUT OF THE USE
# OF THIS SOFTWARE, EVEN IF ADVISED OF THE POSSIBILITY OF SUCH DAMAGE.

# **TODO: Write tests for this class

from libbifrost import _bf, _check, _get, BifrostObject

class DrxReader(BifrostObject):
    def __init__(self, fh, ring, nsrc, src0,
                 buffer_nframe, slot_nframe, sequence_callback, core=None):
        if core is None:
            core = -1
        BifrostObject.__init__(
            self, _bf.bfDrxReaderCreate, _bf.bfDrxReaderDestroy,
            fh.fileno(), ring.obj, nsrc, src0,
            buffer_nframe, slot_nframe,
            sequence_callback, core)
    def __enter__(self):
        return self
    def __exit__(self, type, value, tb):
        self.end()
    def read(self):
        status = _bf.BFdrxreader_status()
        _check(_bf.bfDrxReaderRead(self.obj, status))
        return status
    def flush(self):
        _check(_bf.bfDrxReaderFlush(self.obj))
    def end(self):
        _check(_bf.bfDrxReaderEnd(self.obj))