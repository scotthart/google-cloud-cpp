// Copyright 2023 Google LLC
//
// Licensed under the Apache License, Version 2.0 (the "License");
// you may not use this file except in compliance with the License.
// You may obtain a copy of the License at
//
// https://www.apache.org/licenses/LICENSE-2.0
//
// Unless required by applicable law or agreed to in writing, software
// distributed under the License is distributed on an "AS IS" BASIS,
// WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
// See the License for the specific language governing permissions and
// limitations under the License.

//! [START pubsub_quickstart_subscriber] [all]
#include "google/cloud/pubsub/message.h"
#include "google/cloud/pubsub/subscriber.h"
#include "google/cloud/credentials.h"
#include <iostream>

int main(int argc, char* argv[]) {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " <project-id> <subscription-id>\n";
    return 1;
  }

  std::string const project_id = argv[1];
  std::string const subscription_id = argv[2];

  namespace pubsub = ::google::cloud::pubsub;

  std::string impersonate_service_account;

  google::cloud::Options options{};
  // Authenticate using Impersonated Service Account Credentials.
  std::shared_ptr<google::cloud::Credentials> credentials;
  if (impersonate_service_account.empty()) {
    credentials = google::cloud::MakeGoogleDefaultCredentials();
  } else {
    credentials = google::cloud::MakeImpersonateServiceAccountCredentials(
        google::cloud::MakeGoogleDefaultCredentials(),
        impersonate_service_account, google::cloud::Options{});
  }
  options.set<google::cloud::UnifiedCredentialsOption>(credentials);

  // Publish an empty message to the topic.
  // auto publisher = pubsub::Publisher(pubsub::MakePublisherConnection(
  //     pubsub::Topic(project_id, topic_id), options));
  // auto publish_future =
  //     publisher.Publish(pubsub::MessageBuilder{}.SetData("test").Build());
  // auto pub_result = publish_future.get();
  // if (!pub_result.ok()) {
  //   std::cerr << "Error publishing message: " << pub_result.status() << "\n";
  //   return 1;
  // }
  // std::cout << "Published message: " << "Published message" << std::endl;

  auto subscriber = pubsub::Subscriber(pubsub::MakeSubscriberConnection(
      pubsub::Subscription(project_id, subscription_id), options));

  auto pull_result = subscriber.Pull();
  if (!pull_result.ok()) {
    std::cerr << "Error pulling message: " << pull_result.status() << "\n";
    return 1;
  }
  pubsub::PullResponse& response = pull_result.value();
  auto ack_future = std::move(response.handler).ack();
  auto ack_result = ack_future.get();
  if (!ack_result.ok()) {
    std::cerr << "Error acking message: " << ack_result << "\n";
    return 1;
  }
  std::cout << "Received message: " << response.message << "\n";

  // absl::Notification done;
  // auto session =
  //     subscriber.Subscribe([&](pubsub::Message const& m, pubsub::AckHandler
  //     h) {
  //       std::cout << "Received message " << m << "\n";
  //       std::move(h).ack();
  //       if (!done.HasBeenNotified()) {
  //         done.Notify();
  //       }
  //     });

  // std::cout << "Waiting for messages on " + subscription_id + "...\n";

  // bool notified = done.WaitForNotificationWithTimeout(kWaitTimeout);
  // if (!notified) {
  //   std::cout << "timeout reached, ending session\n";
  // }
  // session.cancel();
  // auto final_status = session.get();
  // if (!final_status.ok()) {
  //   std::cerr << "Subscription session ended with error: " << final_status
  //             << "\n";
  //   return 1;
  // }

  return 0;
}

#if 0
int main(int argc, char* argv[]) try {
  if (argc != 3) {
    std::cerr << "Usage: " << argv[0] << " <project-id> <subscription-id>\n";
    return 1;
  }

  std::string const project_id = argv[1];
  std::string const subscription_id = argv[2];

  auto constexpr kWaitTimeout = std::chrono::seconds(30);

  // Create a namespace alias to make the code easier to read.
  namespace pubsub = ::google::cloud::pubsub;

  auto subscriber = pubsub::Subscriber(pubsub::MakeSubscriberConnection(
      pubsub::Subscription(project_id, subscription_id)));

  auto session =
      subscriber.Subscribe([&](pubsub::Message const& m, pubsub::AckHandler h) {
        std::cout << "Received message " << m << "\n";
        std::move(h).ack();
      });

  std::cout << "Waiting for messages on " + subscription_id + "...\n";

  // Blocks until the timeout is reached.
  auto result = session.wait_for(kWaitTimeout);
  if (result == std::future_status::timeout) {
    std::cout << "timeout reached, ending session\n";
    session.cancel();
  }

  return 0;
} catch (google::cloud::Status const& status) {
  std::cerr << "google::cloud::Status thrown: " << status << "\n";
  return 1;
}
//! [END pubsub_quickstart_subscriber] [all]
#endif
