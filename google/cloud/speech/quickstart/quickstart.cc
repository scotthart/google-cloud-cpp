// Copyright 2022 Google LLC
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
#include "google/cloud/speech/v1/speech_client.h"
#include "google/cloud/speech/v2/speech_client.h"
#include "google/cloud/common_options.h"
#include "google/cloud/project.h"
#include <iostream>


int main(int argc, char* argv[]) {
  auto constexpr kDefaultUri = "gs://cloud-samples-data/speech/hello.wav";
  namespace speech_v2 = ::google::cloud::speech::v2;
  google::cloud::Options options;
//  auto options = google::cloud::Options{}.set<google::cloud::EndpointOption>(
//      "us-central1-speech.googleapis.com");
//  auto options = google::cloud::Options{}.set<google::cloud::EndpointOption>(
//      "eu-speech.googleapis.com");
  auto connection = google::cloud::speech_v2::MakeSpeechConnection(options);
  auto client = google::cloud::speech_v2::SpeechClient(connection, options);

  google::cloud::speech::v2::Recognizer recognizer;
//  recognizer.mutable_config()->set_model("short");
//  *(recognizer.mutable_config()->add_language_codes()) = "en-US";
//  speech_v2::AutoDetectDecodingConfig config;
//  *recognizer.mutable_config()->mutable_auto_decoding_config() = config;

//  auto recognizer_result = client.CreateRecognizer(
//      "projects/cloud-cpp-testing-resources/locations/us-central1",
//      recognizer,
//      "my-recognizer").get();
//
//  if (!recognizer_result) {
//    std::cerr << "CreateRecognizer failed: " << recognizer_result.status() << "\n";
//    return 1;
//  }


  google::cloud::speech::v2::RecognizeRequest request;
  *(request.mutable_config()->add_language_codes()) = "en-US";
  request.mutable_config()->set_model("short");
  speech_v2::AutoDetectDecodingConfig config;
  *request.mutable_config()->mutable_auto_decoding_config() = config;
//  request.set_recognizer(
//      "projects/cloud-cpp-testing-resources/locations/us-central1/recognizers/my-recognizer");
  request.set_recognizer(
      "projects/cloud-cpp-testing-resources/locations/global/recognizers/_");
  request.set_uri(kDefaultUri);

  auto response = client.Recognize(request, options);

  if (response.status().code() != google::cloud::StatusCode::kOk) {
    // Output: expected resource location to be global, but found asia-southeast1 in resource name.
    std::cerr << "Recognize failed: " << response.status().message() << "\n";
    return 1;
  }
}

#if 0
int main(int argc, char* argv[]) try {
  auto constexpr kDefaultUri = "gs://cloud-samples-data/speech/hello.wav";
  if (argc > 2) {
    std::cerr << "Usage: " << argv[0] << " [gcs-uri]\n"
              << "  The gcs-uri must be in gs://... format. It defaults to "
              << kDefaultUri << "\n";
    return 1;
  }
  auto uri = std::string{argc == 2 ? argv[1] : kDefaultUri};

  namespace speech = ::google::cloud::speech_v1;
  auto client = speech::SpeechClient(speech::MakeSpeechConnection());

  google::cloud::speech::v1::RecognitionConfig config;
  config.set_language_code("en-US");
  google::cloud::speech::v1::RecognitionAudio audio;
  audio.set_uri(uri);
  auto response = client.Recognize(config, audio);
  if (!response) throw std::move(response).status();
  std::cout << response->DebugString() << "\n";

  return 0;
} catch (google::cloud::Status const& status) {
  std::cerr << "google::cloud::Status thrown: " << status << "\n";
  return 1;
}
#endif
//! [all]
