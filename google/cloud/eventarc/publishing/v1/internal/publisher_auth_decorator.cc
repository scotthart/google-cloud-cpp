// Copyright 2022 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//      https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

// Generated by the Codegen C++ plugin.
// If you make any local changes, they will be lost.
// source: google/cloud/eventarc/publishing/v1/publisher.proto

#include "google/cloud/eventarc/publishing/v1/internal/publisher_auth_decorator.h"
#include <google/cloud/eventarc/publishing/v1/publisher.grpc.pb.h>
#include <memory>
#include <utility>

namespace google {
namespace cloud {
namespace eventarc_publishing_v1_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

PublisherAuth::PublisherAuth(
    std::shared_ptr<google::cloud::internal::GrpcAuthenticationStrategy> auth,
    std::shared_ptr<PublisherStub> child)
    : auth_(std::move(auth)), child_(std::move(child)) {}

StatusOr<google::cloud::eventarc::publishing::v1::
             PublishChannelConnectionEventsResponse>
PublisherAuth::PublishChannelConnectionEvents(
    grpc::ClientContext& context, Options const& options,
    google::cloud::eventarc::publishing::v1::
        PublishChannelConnectionEventsRequest const& request) {
  auto status = auth_->ConfigureContext(context);
  if (!status.ok()) return status;
  return child_->PublishChannelConnectionEvents(context, options, request);
}

StatusOr<google::cloud::eventarc::publishing::v1::PublishEventsResponse>
PublisherAuth::PublishEvents(
    grpc::ClientContext& context, Options const& options,
    google::cloud::eventarc::publishing::v1::PublishEventsRequest const&
        request) {
  auto status = auth_->ConfigureContext(context);
  if (!status.ok()) return status;
  return child_->PublishEvents(context, options, request);
}

StatusOr<google::cloud::eventarc::publishing::v1::PublishResponse>
PublisherAuth::Publish(
    grpc::ClientContext& context, Options const& options,
    google::cloud::eventarc::publishing::v1::PublishRequest const& request) {
  auto status = auth_->ConfigureContext(context);
  if (!status.ok()) return status;
  return child_->Publish(context, options, request);
}

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace eventarc_publishing_v1_internal
}  // namespace cloud
}  // namespace google
