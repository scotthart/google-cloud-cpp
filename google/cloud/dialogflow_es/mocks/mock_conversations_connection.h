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
// source: google/cloud/dialogflow/v2/conversation.proto

#ifndef GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_DIALOGFLOW_ES_MOCKS_MOCK_CONVERSATIONS_CONNECTION_H
#define GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_DIALOGFLOW_ES_MOCKS_MOCK_CONVERSATIONS_CONNECTION_H

#include "google/cloud/dialogflow_es/conversations_connection.h"
#include <gmock/gmock.h>

namespace google {
namespace cloud {
namespace dialogflow_es_mocks {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

/**
 * A class to mock `ConversationsConnection`.
 *
 * Application developers may want to test their code with simulated responses,
 * including errors, from an object of type `ConversationsClient`. To do so,
 * construct an object of type `ConversationsClient` with an instance of this
 * class. Then use the Google Test framework functions to program the behavior
 * of this mock.
 *
 * @see [This example][bq-mock] for how to test your application with GoogleTest.
 * While the example showcases types from the BigQuery library, the underlying
 * principles apply for any pair of `*Client` and `*Connection`.
 *
 * [bq-mock]: @cloud_cpp_docs_link{bigquery,bigquery-read-mock}
 */
class MockConversationsConnection
    : public dialogflow_es::ConversationsConnection {
 public:
  MOCK_METHOD(Options, options, (), (override));

  MOCK_METHOD(
      StatusOr<google::cloud::dialogflow::v2::Conversation>, CreateConversation,
      (google::cloud::dialogflow::v2::CreateConversationRequest const& request),
      (override));

  MOCK_METHOD((StreamRange<google::cloud::dialogflow::v2::Conversation>),
              ListConversations,
              (google::cloud::dialogflow::v2::ListConversationsRequest request),
              (override));

  MOCK_METHOD(
      StatusOr<google::cloud::dialogflow::v2::Conversation>, GetConversation,
      (google::cloud::dialogflow::v2::GetConversationRequest const& request),
      (override));

  MOCK_METHOD(StatusOr<google::cloud::dialogflow::v2::Conversation>,
              CompleteConversation,
              (google::cloud::dialogflow::v2::CompleteConversationRequest const&
                   request),
              (override));

  MOCK_METHOD(
      StatusOr<google::cloud::dialogflow::v2::IngestContextReferencesResponse>,
      IngestContextReferences,
      (google::cloud::dialogflow::v2::IngestContextReferencesRequest const&
           request),
      (override));

  MOCK_METHOD((StreamRange<google::cloud::dialogflow::v2::Message>),
              ListMessages,
              (google::cloud::dialogflow::v2::ListMessagesRequest request),
              (override));

  MOCK_METHOD(
      StatusOr<
          google::cloud::dialogflow::v2::SuggestConversationSummaryResponse>,
      SuggestConversationSummary,
      (google::cloud::dialogflow::v2::SuggestConversationSummaryRequest const&
           request),
      (override));

  MOCK_METHOD(
      StatusOr<google::cloud::dialogflow::v2::GenerateStatelessSummaryResponse>,
      GenerateStatelessSummary,
      (google::cloud::dialogflow::v2::GenerateStatelessSummaryRequest const&
           request),
      (override));

  MOCK_METHOD(
      StatusOr<
          google::cloud::dialogflow::v2::GenerateStatelessSuggestionResponse>,
      GenerateStatelessSuggestion,
      (google::cloud::dialogflow::v2::GenerateStatelessSuggestionRequest const&
           request),
      (override));

  MOCK_METHOD(
      StatusOr<google::cloud::dialogflow::v2::SearchKnowledgeResponse>,
      SearchKnowledge,
      (google::cloud::dialogflow::v2::SearchKnowledgeRequest const& request),
      (override));

  MOCK_METHOD(
      StatusOr<google::cloud::dialogflow::v2::GenerateSuggestionsResponse>,
      GenerateSuggestions,
      (google::cloud::dialogflow::v2::GenerateSuggestionsRequest const&
           request),
      (override));

  MOCK_METHOD((StreamRange<google::cloud::location::Location>), ListLocations,
              (google::cloud::location::ListLocationsRequest request),
              (override));

  MOCK_METHOD(StatusOr<google::cloud::location::Location>, GetLocation,
              (google::cloud::location::GetLocationRequest const& request),
              (override));

  MOCK_METHOD((StreamRange<google::longrunning::Operation>), ListOperations,
              (google::longrunning::ListOperationsRequest request), (override));

  MOCK_METHOD(StatusOr<google::longrunning::Operation>, GetOperation,
              (google::longrunning::GetOperationRequest const& request),
              (override));

  MOCK_METHOD(Status, CancelOperation,
              (google::longrunning::CancelOperationRequest const& request),
              (override));
};

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace dialogflow_es_mocks
}  // namespace cloud
}  // namespace google

#endif  // GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_DIALOGFLOW_ES_MOCKS_MOCK_CONVERSATIONS_CONNECTION_H
