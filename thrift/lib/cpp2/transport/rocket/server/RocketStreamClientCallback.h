/*
 * Copyright 2018-present Facebook, Inc.
 *
 * Licensed under the Apache License, Version 2.0 (the "License");
 * you may not use this file except in compliance with the License.
 * You may obtain a copy of the License at
 *
 *   http://www.apache.org/licenses/LICENSE-2.0
 *
 * Unless required by applicable law or agreed to in writing, software
 * distributed under the License is distributed on an "AS IS" BASIS,
 * WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
 * See the License for the specific language governing permissions and
 * limitations under the License.
 */

#pragma once

#include <memory>

#include <folly/ExceptionWrapper.h>
#include <folly/io/async/HHWheelTimer.h>

#include <thrift/lib/cpp2/async/StreamCallbacks.h>
#include <thrift/lib/cpp2/transport/rocket/Types.h>

namespace apache {
namespace thrift {

namespace rocket {
class RocketServerFrameContext;
} // namespace rocket

// TODO Optimize memory footprint of per-stream timeouts
class RocketStreamClientCallback final : public StreamClientCallback,
                                         public folly::HHWheelTimer::Callback {
 public:
  RocketStreamClientCallback(
      rocket::RocketServerFrameContext&& context,
      uint32_t initialRequestN);
  ~RocketStreamClientCallback() override = default;

  void onFirstResponse(
      FirstResponsePayload&& firstResponse,
      folly::EventBase* evb,
      StreamServerCallback* serverCallback) override;
  void onFirstResponseError(folly::exception_wrapper ew) override;

  void onStreamNext(StreamPayload&& payload) override;
  void onStreamError(folly::exception_wrapper ew) override;
  void onStreamComplete() override;

  void request(uint32_t n);

  void timeoutExpired() noexcept override;

  StreamServerCallback& getStreamServerCallback();

 private:
  // TODO RocketServerConnection* suffices instead of RocketServerFrameContext
  std::unique_ptr<rocket::RocketServerFrameContext> context_;
  StreamServerCallback* serverCallback_{nullptr};
  uint64_t tokens_{0};

  void scheduleTimeout();
};

} // namespace thrift
} // namespace apache
