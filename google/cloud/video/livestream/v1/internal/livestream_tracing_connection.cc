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
// source: google/cloud/video/livestream/v1/service.proto

#include "google/cloud/video/livestream/v1/internal/livestream_tracing_connection.h"
#include "google/cloud/internal/opentelemetry.h"
#include "google/cloud/internal/traced_stream_range.h"
#include <memory>
#include <utility>

namespace google {
namespace cloud {
namespace video_livestream_v1_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

#ifdef GOOGLE_CLOUD_CPP_HAVE_OPENTELEMETRY

LivestreamServiceTracingConnection::LivestreamServiceTracingConnection(
    std::shared_ptr<video_livestream_v1::LivestreamServiceConnection> child)
    : child_(std::move(child)) {}

future<StatusOr<google::cloud::video::livestream::v1::Channel>>
LivestreamServiceTracingConnection::CreateChannel(
    google::cloud::video::livestream::v1::CreateChannelRequest const& request) {
  auto span = internal::MakeSpan(
      "video_livestream_v1::LivestreamServiceConnection::CreateChannel");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span), child_->CreateChannel(request));
}

StatusOr<google::longrunning::Operation>
LivestreamServiceTracingConnection::CreateChannel(
    NoAwaitTag,
    google::cloud::video::livestream::v1::CreateChannelRequest const& request) {
  auto span = internal::MakeSpan(
      "video_livestream_v1::LivestreamServiceConnection::CreateChannel");
  opentelemetry::trace::Scope scope(span);
  return internal::EndSpan(*span, child_->CreateChannel(NoAwaitTag{}, request));
}

future<StatusOr<google::cloud::video::livestream::v1::Channel>>
LivestreamServiceTracingConnection::CreateChannel(
    google::longrunning::Operation const& operation) {
  auto span = internal::MakeSpan(
      "video_livestream_v1::LivestreamServiceConnection::CreateChannel");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span), child_->CreateChannel(operation));
}

StreamRange<google::cloud::video::livestream::v1::Channel>
LivestreamServiceTracingConnection::ListChannels(
    google::cloud::video::livestream::v1::ListChannelsRequest request) {
  auto span = internal::MakeSpan(
      "video_livestream_v1::LivestreamServiceConnection::ListChannels");
  internal::OTelScope scope(span);
  auto sr = child_->ListChannels(std::move(request));
  return internal::MakeTracedStreamRange<
      google::cloud::video::livestream::v1::Channel>(std::move(span),
                                                     std::move(sr));
}

StatusOr<google::cloud::video::livestream::v1::Channel>
LivestreamServiceTracingConnection::GetChannel(
    google::cloud::video::livestream::v1::GetChannelRequest const& request) {
  auto span = internal::MakeSpan(
      "video_livestream_v1::LivestreamServiceConnection::GetChannel");
  auto scope = opentelemetry::trace::Scope(span);
  return internal::EndSpan(*span, child_->GetChannel(request));
}

future<StatusOr<google::cloud::video::livestream::v1::OperationMetadata>>
LivestreamServiceTracingConnection::DeleteChannel(
    google::cloud::video::livestream::v1::DeleteChannelRequest const& request) {
  auto span = internal::MakeSpan(
      "video_livestream_v1::LivestreamServiceConnection::DeleteChannel");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span), child_->DeleteChannel(request));
}

StatusOr<google::longrunning::Operation>
LivestreamServiceTracingConnection::DeleteChannel(
    NoAwaitTag,
    google::cloud::video::livestream::v1::DeleteChannelRequest const& request) {
  auto span = internal::MakeSpan(
      "video_livestream_v1::LivestreamServiceConnection::DeleteChannel");
  opentelemetry::trace::Scope scope(span);
  return internal::EndSpan(*span, child_->DeleteChannel(NoAwaitTag{}, request));
}

future<StatusOr<google::cloud::video::livestream::v1::OperationMetadata>>
LivestreamServiceTracingConnection::DeleteChannel(
    google::longrunning::Operation const& operation) {
  auto span = internal::MakeSpan(
      "video_livestream_v1::LivestreamServiceConnection::DeleteChannel");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span), child_->DeleteChannel(operation));
}

future<StatusOr<google::cloud::video::livestream::v1::Channel>>
LivestreamServiceTracingConnection::UpdateChannel(
    google::cloud::video::livestream::v1::UpdateChannelRequest const& request) {
  auto span = internal::MakeSpan(
      "video_livestream_v1::LivestreamServiceConnection::UpdateChannel");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span), child_->UpdateChannel(request));
}

StatusOr<google::longrunning::Operation>
LivestreamServiceTracingConnection::UpdateChannel(
    NoAwaitTag,
    google::cloud::video::livestream::v1::UpdateChannelRequest const& request) {
  auto span = internal::MakeSpan(
      "video_livestream_v1::LivestreamServiceConnection::UpdateChannel");
  opentelemetry::trace::Scope scope(span);
  return internal::EndSpan(*span, child_->UpdateChannel(NoAwaitTag{}, request));
}

future<StatusOr<google::cloud::video::livestream::v1::Channel>>
LivestreamServiceTracingConnection::UpdateChannel(
    google::longrunning::Operation const& operation) {
  auto span = internal::MakeSpan(
      "video_livestream_v1::LivestreamServiceConnection::UpdateChannel");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span), child_->UpdateChannel(operation));
}

future<StatusOr<google::cloud::video::livestream::v1::ChannelOperationResponse>>
LivestreamServiceTracingConnection::StartChannel(
    google::cloud::video::livestream::v1::StartChannelRequest const& request) {
  auto span = internal::MakeSpan(
      "video_livestream_v1::LivestreamServiceConnection::StartChannel");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span), child_->StartChannel(request));
}

StatusOr<google::longrunning::Operation>
LivestreamServiceTracingConnection::StartChannel(
    NoAwaitTag,
    google::cloud::video::livestream::v1::StartChannelRequest const& request) {
  auto span = internal::MakeSpan(
      "video_livestream_v1::LivestreamServiceConnection::StartChannel");
  opentelemetry::trace::Scope scope(span);
  return internal::EndSpan(*span, child_->StartChannel(NoAwaitTag{}, request));
}

future<StatusOr<google::cloud::video::livestream::v1::ChannelOperationResponse>>
LivestreamServiceTracingConnection::StartChannel(
    google::longrunning::Operation const& operation) {
  auto span = internal::MakeSpan(
      "video_livestream_v1::LivestreamServiceConnection::StartChannel");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span), child_->StartChannel(operation));
}

future<StatusOr<google::cloud::video::livestream::v1::ChannelOperationResponse>>
LivestreamServiceTracingConnection::StopChannel(
    google::cloud::video::livestream::v1::StopChannelRequest const& request) {
  auto span = internal::MakeSpan(
      "video_livestream_v1::LivestreamServiceConnection::StopChannel");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span), child_->StopChannel(request));
}

StatusOr<google::longrunning::Operation>
LivestreamServiceTracingConnection::StopChannel(
    NoAwaitTag,
    google::cloud::video::livestream::v1::StopChannelRequest const& request) {
  auto span = internal::MakeSpan(
      "video_livestream_v1::LivestreamServiceConnection::StopChannel");
  opentelemetry::trace::Scope scope(span);
  return internal::EndSpan(*span, child_->StopChannel(NoAwaitTag{}, request));
}

future<StatusOr<google::cloud::video::livestream::v1::ChannelOperationResponse>>
LivestreamServiceTracingConnection::StopChannel(
    google::longrunning::Operation const& operation) {
  auto span = internal::MakeSpan(
      "video_livestream_v1::LivestreamServiceConnection::StopChannel");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span), child_->StopChannel(operation));
}

future<StatusOr<google::cloud::video::livestream::v1::Input>>
LivestreamServiceTracingConnection::CreateInput(
    google::cloud::video::livestream::v1::CreateInputRequest const& request) {
  auto span = internal::MakeSpan(
      "video_livestream_v1::LivestreamServiceConnection::CreateInput");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span), child_->CreateInput(request));
}

StatusOr<google::longrunning::Operation>
LivestreamServiceTracingConnection::CreateInput(
    NoAwaitTag,
    google::cloud::video::livestream::v1::CreateInputRequest const& request) {
  auto span = internal::MakeSpan(
      "video_livestream_v1::LivestreamServiceConnection::CreateInput");
  opentelemetry::trace::Scope scope(span);
  return internal::EndSpan(*span, child_->CreateInput(NoAwaitTag{}, request));
}

future<StatusOr<google::cloud::video::livestream::v1::Input>>
LivestreamServiceTracingConnection::CreateInput(
    google::longrunning::Operation const& operation) {
  auto span = internal::MakeSpan(
      "video_livestream_v1::LivestreamServiceConnection::CreateInput");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span), child_->CreateInput(operation));
}

StreamRange<google::cloud::video::livestream::v1::Input>
LivestreamServiceTracingConnection::ListInputs(
    google::cloud::video::livestream::v1::ListInputsRequest request) {
  auto span = internal::MakeSpan(
      "video_livestream_v1::LivestreamServiceConnection::ListInputs");
  internal::OTelScope scope(span);
  auto sr = child_->ListInputs(std::move(request));
  return internal::MakeTracedStreamRange<
      google::cloud::video::livestream::v1::Input>(std::move(span),
                                                   std::move(sr));
}

StatusOr<google::cloud::video::livestream::v1::Input>
LivestreamServiceTracingConnection::GetInput(
    google::cloud::video::livestream::v1::GetInputRequest const& request) {
  auto span = internal::MakeSpan(
      "video_livestream_v1::LivestreamServiceConnection::GetInput");
  auto scope = opentelemetry::trace::Scope(span);
  return internal::EndSpan(*span, child_->GetInput(request));
}

future<StatusOr<google::cloud::video::livestream::v1::OperationMetadata>>
LivestreamServiceTracingConnection::DeleteInput(
    google::cloud::video::livestream::v1::DeleteInputRequest const& request) {
  auto span = internal::MakeSpan(
      "video_livestream_v1::LivestreamServiceConnection::DeleteInput");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span), child_->DeleteInput(request));
}

StatusOr<google::longrunning::Operation>
LivestreamServiceTracingConnection::DeleteInput(
    NoAwaitTag,
    google::cloud::video::livestream::v1::DeleteInputRequest const& request) {
  auto span = internal::MakeSpan(
      "video_livestream_v1::LivestreamServiceConnection::DeleteInput");
  opentelemetry::trace::Scope scope(span);
  return internal::EndSpan(*span, child_->DeleteInput(NoAwaitTag{}, request));
}

future<StatusOr<google::cloud::video::livestream::v1::OperationMetadata>>
LivestreamServiceTracingConnection::DeleteInput(
    google::longrunning::Operation const& operation) {
  auto span = internal::MakeSpan(
      "video_livestream_v1::LivestreamServiceConnection::DeleteInput");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span), child_->DeleteInput(operation));
}

future<StatusOr<google::cloud::video::livestream::v1::Input>>
LivestreamServiceTracingConnection::UpdateInput(
    google::cloud::video::livestream::v1::UpdateInputRequest const& request) {
  auto span = internal::MakeSpan(
      "video_livestream_v1::LivestreamServiceConnection::UpdateInput");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span), child_->UpdateInput(request));
}

StatusOr<google::longrunning::Operation>
LivestreamServiceTracingConnection::UpdateInput(
    NoAwaitTag,
    google::cloud::video::livestream::v1::UpdateInputRequest const& request) {
  auto span = internal::MakeSpan(
      "video_livestream_v1::LivestreamServiceConnection::UpdateInput");
  opentelemetry::trace::Scope scope(span);
  return internal::EndSpan(*span, child_->UpdateInput(NoAwaitTag{}, request));
}

future<StatusOr<google::cloud::video::livestream::v1::Input>>
LivestreamServiceTracingConnection::UpdateInput(
    google::longrunning::Operation const& operation) {
  auto span = internal::MakeSpan(
      "video_livestream_v1::LivestreamServiceConnection::UpdateInput");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span), child_->UpdateInput(operation));
}

StatusOr<google::cloud::video::livestream::v1::Event>
LivestreamServiceTracingConnection::CreateEvent(
    google::cloud::video::livestream::v1::CreateEventRequest const& request) {
  auto span = internal::MakeSpan(
      "video_livestream_v1::LivestreamServiceConnection::CreateEvent");
  auto scope = opentelemetry::trace::Scope(span);
  return internal::EndSpan(*span, child_->CreateEvent(request));
}

StreamRange<google::cloud::video::livestream::v1::Event>
LivestreamServiceTracingConnection::ListEvents(
    google::cloud::video::livestream::v1::ListEventsRequest request) {
  auto span = internal::MakeSpan(
      "video_livestream_v1::LivestreamServiceConnection::ListEvents");
  internal::OTelScope scope(span);
  auto sr = child_->ListEvents(std::move(request));
  return internal::MakeTracedStreamRange<
      google::cloud::video::livestream::v1::Event>(std::move(span),
                                                   std::move(sr));
}

StatusOr<google::cloud::video::livestream::v1::Event>
LivestreamServiceTracingConnection::GetEvent(
    google::cloud::video::livestream::v1::GetEventRequest const& request) {
  auto span = internal::MakeSpan(
      "video_livestream_v1::LivestreamServiceConnection::GetEvent");
  auto scope = opentelemetry::trace::Scope(span);
  return internal::EndSpan(*span, child_->GetEvent(request));
}

Status LivestreamServiceTracingConnection::DeleteEvent(
    google::cloud::video::livestream::v1::DeleteEventRequest const& request) {
  auto span = internal::MakeSpan(
      "video_livestream_v1::LivestreamServiceConnection::DeleteEvent");
  auto scope = opentelemetry::trace::Scope(span);
  return internal::EndSpan(*span, child_->DeleteEvent(request));
}

StreamRange<google::cloud::video::livestream::v1::Clip>
LivestreamServiceTracingConnection::ListClips(
    google::cloud::video::livestream::v1::ListClipsRequest request) {
  auto span = internal::MakeSpan(
      "video_livestream_v1::LivestreamServiceConnection::ListClips");
  internal::OTelScope scope(span);
  auto sr = child_->ListClips(std::move(request));
  return internal::MakeTracedStreamRange<
      google::cloud::video::livestream::v1::Clip>(std::move(span),
                                                  std::move(sr));
}

StatusOr<google::cloud::video::livestream::v1::Clip>
LivestreamServiceTracingConnection::GetClip(
    google::cloud::video::livestream::v1::GetClipRequest const& request) {
  auto span = internal::MakeSpan(
      "video_livestream_v1::LivestreamServiceConnection::GetClip");
  auto scope = opentelemetry::trace::Scope(span);
  return internal::EndSpan(*span, child_->GetClip(request));
}

future<StatusOr<google::cloud::video::livestream::v1::Clip>>
LivestreamServiceTracingConnection::CreateClip(
    google::cloud::video::livestream::v1::CreateClipRequest const& request) {
  auto span = internal::MakeSpan(
      "video_livestream_v1::LivestreamServiceConnection::CreateClip");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span), child_->CreateClip(request));
}

StatusOr<google::longrunning::Operation>
LivestreamServiceTracingConnection::CreateClip(
    NoAwaitTag,
    google::cloud::video::livestream::v1::CreateClipRequest const& request) {
  auto span = internal::MakeSpan(
      "video_livestream_v1::LivestreamServiceConnection::CreateClip");
  opentelemetry::trace::Scope scope(span);
  return internal::EndSpan(*span, child_->CreateClip(NoAwaitTag{}, request));
}

future<StatusOr<google::cloud::video::livestream::v1::Clip>>
LivestreamServiceTracingConnection::CreateClip(
    google::longrunning::Operation const& operation) {
  auto span = internal::MakeSpan(
      "video_livestream_v1::LivestreamServiceConnection::CreateClip");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span), child_->CreateClip(operation));
}

future<StatusOr<google::cloud::video::livestream::v1::OperationMetadata>>
LivestreamServiceTracingConnection::DeleteClip(
    google::cloud::video::livestream::v1::DeleteClipRequest const& request) {
  auto span = internal::MakeSpan(
      "video_livestream_v1::LivestreamServiceConnection::DeleteClip");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span), child_->DeleteClip(request));
}

StatusOr<google::longrunning::Operation>
LivestreamServiceTracingConnection::DeleteClip(
    NoAwaitTag,
    google::cloud::video::livestream::v1::DeleteClipRequest const& request) {
  auto span = internal::MakeSpan(
      "video_livestream_v1::LivestreamServiceConnection::DeleteClip");
  opentelemetry::trace::Scope scope(span);
  return internal::EndSpan(*span, child_->DeleteClip(NoAwaitTag{}, request));
}

future<StatusOr<google::cloud::video::livestream::v1::OperationMetadata>>
LivestreamServiceTracingConnection::DeleteClip(
    google::longrunning::Operation const& operation) {
  auto span = internal::MakeSpan(
      "video_livestream_v1::LivestreamServiceConnection::DeleteClip");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span), child_->DeleteClip(operation));
}

future<StatusOr<google::cloud::video::livestream::v1::DvrSession>>
LivestreamServiceTracingConnection::CreateDvrSession(
    google::cloud::video::livestream::v1::CreateDvrSessionRequest const&
        request) {
  auto span = internal::MakeSpan(
      "video_livestream_v1::LivestreamServiceConnection::CreateDvrSession");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span), child_->CreateDvrSession(request));
}

StatusOr<google::longrunning::Operation>
LivestreamServiceTracingConnection::CreateDvrSession(
    NoAwaitTag,
    google::cloud::video::livestream::v1::CreateDvrSessionRequest const&
        request) {
  auto span = internal::MakeSpan(
      "video_livestream_v1::LivestreamServiceConnection::CreateDvrSession");
  opentelemetry::trace::Scope scope(span);
  return internal::EndSpan(*span,
                           child_->CreateDvrSession(NoAwaitTag{}, request));
}

future<StatusOr<google::cloud::video::livestream::v1::DvrSession>>
LivestreamServiceTracingConnection::CreateDvrSession(
    google::longrunning::Operation const& operation) {
  auto span = internal::MakeSpan(
      "video_livestream_v1::LivestreamServiceConnection::CreateDvrSession");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span),
                           child_->CreateDvrSession(operation));
}

StreamRange<google::cloud::video::livestream::v1::DvrSession>
LivestreamServiceTracingConnection::ListDvrSessions(
    google::cloud::video::livestream::v1::ListDvrSessionsRequest request) {
  auto span = internal::MakeSpan(
      "video_livestream_v1::LivestreamServiceConnection::ListDvrSessions");
  internal::OTelScope scope(span);
  auto sr = child_->ListDvrSessions(std::move(request));
  return internal::MakeTracedStreamRange<
      google::cloud::video::livestream::v1::DvrSession>(std::move(span),
                                                        std::move(sr));
}

StatusOr<google::cloud::video::livestream::v1::DvrSession>
LivestreamServiceTracingConnection::GetDvrSession(
    google::cloud::video::livestream::v1::GetDvrSessionRequest const& request) {
  auto span = internal::MakeSpan(
      "video_livestream_v1::LivestreamServiceConnection::GetDvrSession");
  auto scope = opentelemetry::trace::Scope(span);
  return internal::EndSpan(*span, child_->GetDvrSession(request));
}

future<StatusOr<google::cloud::video::livestream::v1::OperationMetadata>>
LivestreamServiceTracingConnection::DeleteDvrSession(
    google::cloud::video::livestream::v1::DeleteDvrSessionRequest const&
        request) {
  auto span = internal::MakeSpan(
      "video_livestream_v1::LivestreamServiceConnection::DeleteDvrSession");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span), child_->DeleteDvrSession(request));
}

StatusOr<google::longrunning::Operation>
LivestreamServiceTracingConnection::DeleteDvrSession(
    NoAwaitTag,
    google::cloud::video::livestream::v1::DeleteDvrSessionRequest const&
        request) {
  auto span = internal::MakeSpan(
      "video_livestream_v1::LivestreamServiceConnection::DeleteDvrSession");
  opentelemetry::trace::Scope scope(span);
  return internal::EndSpan(*span,
                           child_->DeleteDvrSession(NoAwaitTag{}, request));
}

future<StatusOr<google::cloud::video::livestream::v1::OperationMetadata>>
LivestreamServiceTracingConnection::DeleteDvrSession(
    google::longrunning::Operation const& operation) {
  auto span = internal::MakeSpan(
      "video_livestream_v1::LivestreamServiceConnection::DeleteDvrSession");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span),
                           child_->DeleteDvrSession(operation));
}

future<StatusOr<google::cloud::video::livestream::v1::DvrSession>>
LivestreamServiceTracingConnection::UpdateDvrSession(
    google::cloud::video::livestream::v1::UpdateDvrSessionRequest const&
        request) {
  auto span = internal::MakeSpan(
      "video_livestream_v1::LivestreamServiceConnection::UpdateDvrSession");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span), child_->UpdateDvrSession(request));
}

StatusOr<google::longrunning::Operation>
LivestreamServiceTracingConnection::UpdateDvrSession(
    NoAwaitTag,
    google::cloud::video::livestream::v1::UpdateDvrSessionRequest const&
        request) {
  auto span = internal::MakeSpan(
      "video_livestream_v1::LivestreamServiceConnection::UpdateDvrSession");
  opentelemetry::trace::Scope scope(span);
  return internal::EndSpan(*span,
                           child_->UpdateDvrSession(NoAwaitTag{}, request));
}

future<StatusOr<google::cloud::video::livestream::v1::DvrSession>>
LivestreamServiceTracingConnection::UpdateDvrSession(
    google::longrunning::Operation const& operation) {
  auto span = internal::MakeSpan(
      "video_livestream_v1::LivestreamServiceConnection::UpdateDvrSession");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span),
                           child_->UpdateDvrSession(operation));
}

future<StatusOr<google::cloud::video::livestream::v1::Asset>>
LivestreamServiceTracingConnection::CreateAsset(
    google::cloud::video::livestream::v1::CreateAssetRequest const& request) {
  auto span = internal::MakeSpan(
      "video_livestream_v1::LivestreamServiceConnection::CreateAsset");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span), child_->CreateAsset(request));
}

StatusOr<google::longrunning::Operation>
LivestreamServiceTracingConnection::CreateAsset(
    NoAwaitTag,
    google::cloud::video::livestream::v1::CreateAssetRequest const& request) {
  auto span = internal::MakeSpan(
      "video_livestream_v1::LivestreamServiceConnection::CreateAsset");
  opentelemetry::trace::Scope scope(span);
  return internal::EndSpan(*span, child_->CreateAsset(NoAwaitTag{}, request));
}

future<StatusOr<google::cloud::video::livestream::v1::Asset>>
LivestreamServiceTracingConnection::CreateAsset(
    google::longrunning::Operation const& operation) {
  auto span = internal::MakeSpan(
      "video_livestream_v1::LivestreamServiceConnection::CreateAsset");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span), child_->CreateAsset(operation));
}

future<StatusOr<google::cloud::video::livestream::v1::OperationMetadata>>
LivestreamServiceTracingConnection::DeleteAsset(
    google::cloud::video::livestream::v1::DeleteAssetRequest const& request) {
  auto span = internal::MakeSpan(
      "video_livestream_v1::LivestreamServiceConnection::DeleteAsset");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span), child_->DeleteAsset(request));
}

StatusOr<google::longrunning::Operation>
LivestreamServiceTracingConnection::DeleteAsset(
    NoAwaitTag,
    google::cloud::video::livestream::v1::DeleteAssetRequest const& request) {
  auto span = internal::MakeSpan(
      "video_livestream_v1::LivestreamServiceConnection::DeleteAsset");
  opentelemetry::trace::Scope scope(span);
  return internal::EndSpan(*span, child_->DeleteAsset(NoAwaitTag{}, request));
}

future<StatusOr<google::cloud::video::livestream::v1::OperationMetadata>>
LivestreamServiceTracingConnection::DeleteAsset(
    google::longrunning::Operation const& operation) {
  auto span = internal::MakeSpan(
      "video_livestream_v1::LivestreamServiceConnection::DeleteAsset");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span), child_->DeleteAsset(operation));
}

StatusOr<google::cloud::video::livestream::v1::Asset>
LivestreamServiceTracingConnection::GetAsset(
    google::cloud::video::livestream::v1::GetAssetRequest const& request) {
  auto span = internal::MakeSpan(
      "video_livestream_v1::LivestreamServiceConnection::GetAsset");
  auto scope = opentelemetry::trace::Scope(span);
  return internal::EndSpan(*span, child_->GetAsset(request));
}

StreamRange<google::cloud::video::livestream::v1::Asset>
LivestreamServiceTracingConnection::ListAssets(
    google::cloud::video::livestream::v1::ListAssetsRequest request) {
  auto span = internal::MakeSpan(
      "video_livestream_v1::LivestreamServiceConnection::ListAssets");
  internal::OTelScope scope(span);
  auto sr = child_->ListAssets(std::move(request));
  return internal::MakeTracedStreamRange<
      google::cloud::video::livestream::v1::Asset>(std::move(span),
                                                   std::move(sr));
}

StatusOr<google::cloud::video::livestream::v1::Pool>
LivestreamServiceTracingConnection::GetPool(
    google::cloud::video::livestream::v1::GetPoolRequest const& request) {
  auto span = internal::MakeSpan(
      "video_livestream_v1::LivestreamServiceConnection::GetPool");
  auto scope = opentelemetry::trace::Scope(span);
  return internal::EndSpan(*span, child_->GetPool(request));
}

future<StatusOr<google::cloud::video::livestream::v1::Pool>>
LivestreamServiceTracingConnection::UpdatePool(
    google::cloud::video::livestream::v1::UpdatePoolRequest const& request) {
  auto span = internal::MakeSpan(
      "video_livestream_v1::LivestreamServiceConnection::UpdatePool");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span), child_->UpdatePool(request));
}

StatusOr<google::longrunning::Operation>
LivestreamServiceTracingConnection::UpdatePool(
    NoAwaitTag,
    google::cloud::video::livestream::v1::UpdatePoolRequest const& request) {
  auto span = internal::MakeSpan(
      "video_livestream_v1::LivestreamServiceConnection::UpdatePool");
  opentelemetry::trace::Scope scope(span);
  return internal::EndSpan(*span, child_->UpdatePool(NoAwaitTag{}, request));
}

future<StatusOr<google::cloud::video::livestream::v1::Pool>>
LivestreamServiceTracingConnection::UpdatePool(
    google::longrunning::Operation const& operation) {
  auto span = internal::MakeSpan(
      "video_livestream_v1::LivestreamServiceConnection::UpdatePool");
  internal::OTelScope scope(span);
  return internal::EndSpan(std::move(span), child_->UpdatePool(operation));
}

StreamRange<google::cloud::location::Location>
LivestreamServiceTracingConnection::ListLocations(
    google::cloud::location::ListLocationsRequest request) {
  auto span = internal::MakeSpan(
      "video_livestream_v1::LivestreamServiceConnection::ListLocations");
  internal::OTelScope scope(span);
  auto sr = child_->ListLocations(std::move(request));
  return internal::MakeTracedStreamRange<google::cloud::location::Location>(
      std::move(span), std::move(sr));
}

StatusOr<google::cloud::location::Location>
LivestreamServiceTracingConnection::GetLocation(
    google::cloud::location::GetLocationRequest const& request) {
  auto span = internal::MakeSpan(
      "video_livestream_v1::LivestreamServiceConnection::GetLocation");
  auto scope = opentelemetry::trace::Scope(span);
  return internal::EndSpan(*span, child_->GetLocation(request));
}

StreamRange<google::longrunning::Operation>
LivestreamServiceTracingConnection::ListOperations(
    google::longrunning::ListOperationsRequest request) {
  auto span = internal::MakeSpan(
      "video_livestream_v1::LivestreamServiceConnection::ListOperations");
  internal::OTelScope scope(span);
  auto sr = child_->ListOperations(std::move(request));
  return internal::MakeTracedStreamRange<google::longrunning::Operation>(
      std::move(span), std::move(sr));
}

StatusOr<google::longrunning::Operation>
LivestreamServiceTracingConnection::GetOperation(
    google::longrunning::GetOperationRequest const& request) {
  auto span = internal::MakeSpan(
      "video_livestream_v1::LivestreamServiceConnection::GetOperation");
  auto scope = opentelemetry::trace::Scope(span);
  return internal::EndSpan(*span, child_->GetOperation(request));
}

Status LivestreamServiceTracingConnection::DeleteOperation(
    google::longrunning::DeleteOperationRequest const& request) {
  auto span = internal::MakeSpan(
      "video_livestream_v1::LivestreamServiceConnection::DeleteOperation");
  auto scope = opentelemetry::trace::Scope(span);
  return internal::EndSpan(*span, child_->DeleteOperation(request));
}

Status LivestreamServiceTracingConnection::CancelOperation(
    google::longrunning::CancelOperationRequest const& request) {
  auto span = internal::MakeSpan(
      "video_livestream_v1::LivestreamServiceConnection::CancelOperation");
  auto scope = opentelemetry::trace::Scope(span);
  return internal::EndSpan(*span, child_->CancelOperation(request));
}

#endif  // GOOGLE_CLOUD_CPP_HAVE_OPENTELEMETRY

std::shared_ptr<video_livestream_v1::LivestreamServiceConnection>
MakeLivestreamServiceTracingConnection(
    std::shared_ptr<video_livestream_v1::LivestreamServiceConnection> conn) {
#ifdef GOOGLE_CLOUD_CPP_HAVE_OPENTELEMETRY
  if (internal::TracingEnabled(conn->options())) {
    conn =
        std::make_shared<LivestreamServiceTracingConnection>(std::move(conn));
  }
#endif  // GOOGLE_CLOUD_CPP_HAVE_OPENTELEMETRY
  return conn;
}

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace video_livestream_v1_internal
}  // namespace cloud
}  // namespace google
