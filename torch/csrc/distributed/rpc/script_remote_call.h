#pragma once

#include <torch/csrc/distributed/rpc/script_call.h>
#include <torch/csrc/distributed/rpc/types.h>
#include <torch/csrc/jit/operator.h>
#include <torch/csrc/jit/pickler.h>
#include <vector>

namespace torch {
namespace distributed {
namespace rpc {

using torch::jit::Operator;

// A ScriptRemoteCall instance represents an invocation of `dist.remote` on a
// builtin operator. Currently, it does not support using RRef as arguments yet.
// Besides the operator and a vector of arguments, ScriptRemoteCall also
// caontains the RRefId and the ForkId of the return value RRef.
class TORCH_API ScriptRemoteCall final : public ScriptCall {
 public:
  ScriptRemoteCall(
      std::shared_ptr<Operator> op,
      std::vector<at::IValue>&& args,
      const RRefId& retRRefId,
      const RRefId& retForkId);

  const RRefId& retRRefId();
  const RRefId& retForkId();

  Message toMessage() const;
  static ScriptRemoteCall fromMessage(const Message& message);

 private:
  const RRefId retRRefId_;
  const RRefId retForkId_;
};

} // namespace rpc
} // namespace distributed
} // namespace torch
