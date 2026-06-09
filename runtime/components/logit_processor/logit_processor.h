// Copyright 2026 The ODML Authors.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#ifndef THIRD_PARTY_ODML_LITERT_LM_RUNTIME_COMPONENTS_CONSTRAINED_DECODING_LOGIT_PROCESSOR_H_
#define THIRD_PARTY_ODML_LITERT_LM_RUNTIME_COMPONENTS_CONSTRAINED_DECODING_LOGIT_PROCESSOR_H_

#include "absl/status/status.h"  // from @com_google_absl
#include "absl/types/span.h"  // from @com_google_absl
#include "litert/cc/litert_layout.h"  // from @litert
#include "litert/cc/litert_tensor_buffer.h"  // from @litert
#include "tflite/types/half.h"  // from @litert

namespace litert::lm {

class LogitProcessor {
 public:
  virtual ~LogitProcessor() = default;

  // Updates the processor's internal sequence history.
  //
  // To enforce Prompt Exclusion, the engine only calls this method during the
  // decode phase (ignoring prefill tokens).
  virtual absl::Status UpdateState(absl::Span<int> next_token_ids) = 0;

  // Modifies the logits tensor in-place based on the processor's current state.
  virtual absl::Status ProcessLogits(::litert::TensorBuffer& logits) = 0;
  virtual absl::Status ProcessLogits(
      absl::Span<float> logits,
      absl::Span<const ::litert::Layout::Dim> logits_dims) = 0;
  virtual absl::Status ProcessLogits(
      absl::Span<tflite::half> logits,
      absl::Span<const ::litert::Layout::Dim> logits_dims) = 0;
};

}  // namespace litert::lm

#endif  // THIRD_PARTY_ODML_LITERT_LM_RUNTIME_COMPONENTS_CONSTRAINED_DECODING_LOGIT_PROCESSOR_H_
