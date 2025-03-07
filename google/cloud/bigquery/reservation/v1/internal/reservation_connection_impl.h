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
// source: google/cloud/bigquery/reservation/v1/reservation.proto

#ifndef GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_BIGQUERY_RESERVATION_V1_INTERNAL_RESERVATION_CONNECTION_IMPL_H
#define GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_BIGQUERY_RESERVATION_V1_INTERNAL_RESERVATION_CONNECTION_IMPL_H

#include "google/cloud/bigquery/reservation/v1/internal/reservation_retry_traits.h"
#include "google/cloud/bigquery/reservation/v1/internal/reservation_stub.h"
#include "google/cloud/bigquery/reservation/v1/reservation_connection.h"
#include "google/cloud/bigquery/reservation/v1/reservation_connection_idempotency_policy.h"
#include "google/cloud/bigquery/reservation/v1/reservation_options.h"
#include "google/cloud/background_threads.h"
#include "google/cloud/backoff_policy.h"
#include "google/cloud/options.h"
#include "google/cloud/status_or.h"
#include "google/cloud/stream_range.h"
#include "google/cloud/version.h"
#include <memory>

namespace google {
namespace cloud {
namespace bigquery_reservation_v1_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

class ReservationServiceConnectionImpl
    : public bigquery_reservation_v1::ReservationServiceConnection {
 public:
  ~ReservationServiceConnectionImpl() override = default;

  ReservationServiceConnectionImpl(
      std::unique_ptr<google::cloud::BackgroundThreads> background,
      std::shared_ptr<bigquery_reservation_v1_internal::ReservationServiceStub>
          stub,
      Options options);

  Options options() override { return options_; }

  StatusOr<google::cloud::bigquery::reservation::v1::Reservation>
  CreateReservation(
      google::cloud::bigquery::reservation::v1::CreateReservationRequest const&
          request) override;

  StreamRange<google::cloud::bigquery::reservation::v1::Reservation>
  ListReservations(
      google::cloud::bigquery::reservation::v1::ListReservationsRequest request)
      override;

  StatusOr<google::cloud::bigquery::reservation::v1::Reservation>
  GetReservation(
      google::cloud::bigquery::reservation::v1::GetReservationRequest const&
          request) override;

  Status DeleteReservation(
      google::cloud::bigquery::reservation::v1::DeleteReservationRequest const&
          request) override;

  StatusOr<google::cloud::bigquery::reservation::v1::Reservation>
  UpdateReservation(
      google::cloud::bigquery::reservation::v1::UpdateReservationRequest const&
          request) override;

  StatusOr<google::cloud::bigquery::reservation::v1::Reservation>
  FailoverReservation(google::cloud::bigquery::reservation::v1::
                          FailoverReservationRequest const& request) override;

  StatusOr<google::cloud::bigquery::reservation::v1::CapacityCommitment>
  CreateCapacityCommitment(
      google::cloud::bigquery::reservation::v1::
          CreateCapacityCommitmentRequest const& request) override;

  StreamRange<google::cloud::bigquery::reservation::v1::CapacityCommitment>
  ListCapacityCommitments(
      google::cloud::bigquery::reservation::v1::ListCapacityCommitmentsRequest
          request) override;

  StatusOr<google::cloud::bigquery::reservation::v1::CapacityCommitment>
  GetCapacityCommitment(
      google::cloud::bigquery::reservation::v1::
          GetCapacityCommitmentRequest const& request) override;

  Status DeleteCapacityCommitment(
      google::cloud::bigquery::reservation::v1::
          DeleteCapacityCommitmentRequest const& request) override;

  StatusOr<google::cloud::bigquery::reservation::v1::CapacityCommitment>
  UpdateCapacityCommitment(
      google::cloud::bigquery::reservation::v1::
          UpdateCapacityCommitmentRequest const& request) override;

  StatusOr<
      google::cloud::bigquery::reservation::v1::SplitCapacityCommitmentResponse>
  SplitCapacityCommitment(
      google::cloud::bigquery::reservation::v1::
          SplitCapacityCommitmentRequest const& request) override;

  StatusOr<google::cloud::bigquery::reservation::v1::CapacityCommitment>
  MergeCapacityCommitments(
      google::cloud::bigquery::reservation::v1::
          MergeCapacityCommitmentsRequest const& request) override;

  StatusOr<google::cloud::bigquery::reservation::v1::Assignment>
  CreateAssignment(
      google::cloud::bigquery::reservation::v1::CreateAssignmentRequest const&
          request) override;

  StreamRange<google::cloud::bigquery::reservation::v1::Assignment>
  ListAssignments(
      google::cloud::bigquery::reservation::v1::ListAssignmentsRequest request)
      override;

  Status DeleteAssignment(
      google::cloud::bigquery::reservation::v1::DeleteAssignmentRequest const&
          request) override;

  StreamRange<google::cloud::bigquery::reservation::v1::Assignment>
  SearchAssignments(
      google::cloud::bigquery::reservation::v1::SearchAssignmentsRequest
          request) override;

  StreamRange<google::cloud::bigquery::reservation::v1::Assignment>
  SearchAllAssignments(
      google::cloud::bigquery::reservation::v1::SearchAllAssignmentsRequest
          request) override;

  StatusOr<google::cloud::bigquery::reservation::v1::Assignment> MoveAssignment(
      google::cloud::bigquery::reservation::v1::MoveAssignmentRequest const&
          request) override;

  StatusOr<google::cloud::bigquery::reservation::v1::Assignment>
  UpdateAssignment(
      google::cloud::bigquery::reservation::v1::UpdateAssignmentRequest const&
          request) override;

  StatusOr<google::cloud::bigquery::reservation::v1::BiReservation>
  GetBiReservation(
      google::cloud::bigquery::reservation::v1::GetBiReservationRequest const&
          request) override;

  StatusOr<google::cloud::bigquery::reservation::v1::BiReservation>
  UpdateBiReservation(google::cloud::bigquery::reservation::v1::
                          UpdateBiReservationRequest const& request) override;

 private:
  std::unique_ptr<google::cloud::BackgroundThreads> background_;
  std::shared_ptr<bigquery_reservation_v1_internal::ReservationServiceStub>
      stub_;
  Options options_;
};

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace bigquery_reservation_v1_internal
}  // namespace cloud
}  // namespace google

#endif  // GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_BIGQUERY_RESERVATION_V1_INTERNAL_RESERVATION_CONNECTION_IMPL_H
