// Copyright 2017 Google Inc.
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
//     http://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

#include "third_party/cloud_cpp/google/cloud/bigtable/testing/table_test_fixture.h"
#include "third_party/cloud_cpp/google/cloud/internal/throw_delegate.h"
#include "net/proto2/public/text_format.h"

namespace google {
namespace cloud {
namespace bigtable {
namespace testing {

google::bigtable::v2::ReadRowsResponse ReadRowsResponseFromString(
    std::string const& repr) {
  google::bigtable::v2::ReadRowsResponse response;
  if (!proto2::TextFormat::ParseFromString(repr, &response)) {
    google::cloud::internal::ThrowRuntimeError("Failed to parse " + repr);
  }
  return response;
}

std::shared_ptr<MockDataClient> TableTestFixture::SetupMockClient() {
  auto client = std::make_shared<MockDataClient>();
  EXPECT_CALL(*client, project_id())
      .WillRepeatedly(::testing::ReturnRef(project_id_));
  EXPECT_CALL(*client, instance_id())
      .WillRepeatedly(::testing::ReturnRef(instance_id_));
  return client;
}

}  // namespace testing
}  // namespace bigtable
}  // namespace cloud
}  // namespace google
