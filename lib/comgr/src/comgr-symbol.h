/*******************************************************************************
*
* University of Illinois/NCSA
* Open Source License
*
* Copyright (c) 2018 Advanced Micro Devices, Inc. All Rights Reserved.
*
* Permission is hereby granted, free of charge, to any person obtaining a copy
* of this software and associated documentation files (the "Software"), to deal
* with the Software without restriction, including without limitation the
* rights to use, copy, modify, merge, publish, distribute, sublicense, and/or
* sell copies of the Software, and to permit persons to whom the Software is
* furnished to do so, subject to the following conditions:
*
*     * Redistributions of source code must retain the above copyright notice,
*       this list of conditions and the following disclaimers.
*
*     * Redistributions in binary form must reproduce the above copyright
*       notice, this list of conditions and the following disclaimers in the
*       documentation and/or other materials provided with the distribution.
*
*     * Neither the names of Advanced Micro Devices, Inc. nor the names of its
*       contributors may be used to endorse or promote products derived from
*       this Software without specific prior written permission.
*
* THE SOFTWARE IS PROVIDED "AS IS", WITHOUT WARRANTY OF ANY KIND, EXPRESS OR
* IMPLIED, INCLUDING BUT NOT LIMITED TO THE WARRANTIES OF MERCHANTABILITY,
* FITNESS FOR A PARTICULAR PURPOSE AND NONINFRINGEMENT. IN NO EVENT SHALL THE
* CONTRIBUTORS OR COPYRIGHT HOLDERS BE LIABLE FOR ANY CLAIM, DAMAGES OR OTHER
* LIABILITY, WHETHER IN AN ACTION OF CONTRACT, TORT OR OTHERWISE, ARISING FROM,
* OUT OF OR IN CONNECTION WITH THE SOFTWARE OR THE USE OR OTHER DEALINGS WITH
* THE SOFTWARE.
*
*******************************************************************************/

#ifndef COMGR_SYMBOL_H_
#define COMGR_SYMBOL_H_

#include "comgr/amd_comgr.h"
#include "llvm/Object/ObjectFile.h"

using namespace llvm::object;

namespace COMGR {

struct SymbolContext {
  SymbolContext();
  ~SymbolContext();

  amd_comgr_status_t SetName(llvm::StringRef Name);

  char *name;
  amd_comgr_symbol_type_t type;
  uint64_t size;
  bool undefined;
  uint64_t value;
};

class SymbolHelper {

public:
  amd_comgr_symbol_type_t map_to_comgr_symbol_type(SymbolRef::Type, uint64_t);

  llvm::Expected<OwningBinary<Binary>> create_binary(llvm::StringRef in_text);

  SymbolContext *search_symbol(llvm::StringRef, const char *, amd_comgr_data_kind_t);

  amd_comgr_status_t iterate_table(
    llvm::StringRef, amd_comgr_data_kind_t,
    amd_comgr_status_t (*callback)(amd_comgr_symbol_t, void *),
    void *);

}; // SymbolHelper

} // namespace COMGR

#endif