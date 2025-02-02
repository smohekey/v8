// Copyright 2021 the V8 project authors. All rights reserved.
// Use of this source code is governed by a BSD-style license that can be
// found in the LICENSE file.

#ifndef V8_BASELINE_PPC_BASELINE_COMPILER_PPC_INL_H_
#define V8_BASELINE_PPC_BASELINE_COMPILER_PPC_INL_H_

#include "src/base/logging.h"
#include "src/baseline/baseline-compiler.h"

namespace v8 {
namespace internal {
namespace baseline {

#define __ basm_.

void BaselineCompiler::Prologue() {
  ASM_CODE_COMMENT(&masm_);
  __ masm()->EnterFrame(StackFrame::BASELINE);
  DCHECK_EQ(kJSFunctionRegister, kJavaScriptCallTargetRegister);
  int max_frame_size =
      bytecode_->frame_size() + max_call_args_ * kSystemPointerSize;
  CallBuiltin<Builtin::kBaselineOutOfLinePrologue>(
      kContextRegister, kJSFunctionRegister, kJavaScriptCallArgCountRegister,
      max_frame_size, kJavaScriptCallNewTargetRegister, bytecode_);

  PrologueFillFrame();
}

void BaselineCompiler::PrologueFillFrame() { UNIMPLEMENTED(); }

void BaselineCompiler::VerifyFrameSize() { UNIMPLEMENTED(); }

}  // namespace baseline
}  // namespace internal
}  // namespace v8

#endif  // V8_BASELINE_PPC_BASELINE_COMPILER_PPC_INL_H_
