// Copyright 2024 Google LLC
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

//! [all]
#include "google/cloud/speech/v2/speech_client.h"
#include "google/cloud/location.h"
#include "google/cloud/universe_domain.h"
#include "google/cloud/universe_domain_options.h"
#include <iostream>

int main(int argc, char* argv[]) try {
  if (argc != 3 && argc != 4) {
    std::cerr << "Usage: " << argv[0]
              << " project-id location-id [intended-universe-domain]\n";
    return 1;
  }
  std::string const project_id = argv[1];
  std::string const location_id = argv[2];


  auto options =
      google::cloud::AddUniverseDomainOption(google::cloud::ExperimentalTag{});
  if (!options.ok()) throw std::move(options).status();

  namespace speech = ::google::cloud::speech_v2;
  auto client = speech::SpeechClient(speech::MakeSpeechConnection(*options));

  google::cloud::speech::v2::RecognitionConfig recognition_config;
  *recognition_config.add_language_codes() = "en-US";
  recognition_config.set_model("long");

  google::cloud::speech::v2::Recognizer recognizer;
  *recognizer.mutable_default_recognition_config() = recognition_config;

  google::cloud::speech::v2::CreateRecognizerRequest request;
  request.set_validate_only(true);
  request.set_recognizer_id("test-recognizer");
  request.set_parent(google::cloud::Location(project_id, location_id).FullName());
  *request.mutable_recognizer() = recognizer;

  auto result = client.CreateRecognizer(request).get();

  if (!result.ok()) throw std::move(result).status();

  std::cout << "CreateRecognizer=" << result->name() << "\n";


  return 0;
} catch (google::cloud::Status const& status) {
  std::cerr << "google::cloud::Status thrown: " << status << "\n";
  return 1;
}
//! [all]
