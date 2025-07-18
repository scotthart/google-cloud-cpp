// Copyright 2025 Google LLC
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
// source: google/cloud/managedkafka/schemaregistry/v1/schema_registry.proto

#ifndef GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_MANAGEDKAFKA_SCHEMAREGISTRY_V1_INTERNAL_MANAGED_SCHEMA_REGISTRY_STUB_H
#define GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_MANAGEDKAFKA_SCHEMAREGISTRY_V1_INTERNAL_MANAGED_SCHEMA_REGISTRY_STUB_H

#include "google/cloud/options.h"
#include "google/cloud/status_or.h"
#include "google/cloud/version.h"
#include <google/cloud/location/locations.grpc.pb.h>
#include <google/cloud/managedkafka/schemaregistry/v1/schema_registry.grpc.pb.h>
#include <google/longrunning/operations.grpc.pb.h>
#include <memory>
#include <utility>

namespace google {
namespace cloud {
namespace managedkafka_schemaregistry_v1_internal {
GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_BEGIN

class ManagedSchemaRegistryStub {
 public:
  virtual ~ManagedSchemaRegistryStub() = 0;

  virtual StatusOr<
      google::cloud::managedkafka::schemaregistry::v1::SchemaRegistry>
  GetSchemaRegistry(grpc::ClientContext& context, Options const& options,
                    google::cloud::managedkafka::schemaregistry::v1::
                        GetSchemaRegistryRequest const& request) = 0;

  virtual StatusOr<google::cloud::managedkafka::schemaregistry::v1::
                       ListSchemaRegistriesResponse>
  ListSchemaRegistries(grpc::ClientContext& context, Options const& options,
                       google::cloud::managedkafka::schemaregistry::v1::
                           ListSchemaRegistriesRequest const& request) = 0;

  virtual StatusOr<
      google::cloud::managedkafka::schemaregistry::v1::SchemaRegistry>
  CreateSchemaRegistry(grpc::ClientContext& context, Options const& options,
                       google::cloud::managedkafka::schemaregistry::v1::
                           CreateSchemaRegistryRequest const& request) = 0;

  virtual Status DeleteSchemaRegistry(
      grpc::ClientContext& context, Options const& options,
      google::cloud::managedkafka::schemaregistry::v1::
          DeleteSchemaRegistryRequest const& request) = 0;

  virtual StatusOr<google::cloud::managedkafka::schemaregistry::v1::Context>
  GetContext(
      grpc::ClientContext& context, Options const& options,
      google::cloud::managedkafka::schemaregistry::v1::GetContextRequest const&
          request) = 0;

  virtual StatusOr<google::api::HttpBody> ListContexts(
      grpc::ClientContext& context, Options const& options,
      google::cloud::managedkafka::schemaregistry::v1::
          ListContextsRequest const& request) = 0;

  virtual StatusOr<google::cloud::managedkafka::schemaregistry::v1::Schema>
  GetSchema(
      grpc::ClientContext& context, Options const& options,
      google::cloud::managedkafka::schemaregistry::v1::GetSchemaRequest const&
          request) = 0;

  virtual StatusOr<google::api::HttpBody> GetRawSchema(
      grpc::ClientContext& context, Options const& options,
      google::cloud::managedkafka::schemaregistry::v1::GetSchemaRequest const&
          request) = 0;

  virtual StatusOr<google::api::HttpBody> ListSchemaVersions(
      grpc::ClientContext& context, Options const& options,
      google::cloud::managedkafka::schemaregistry::v1::
          ListSchemaVersionsRequest const& request) = 0;

  virtual StatusOr<google::api::HttpBody> ListSchemaTypes(
      grpc::ClientContext& context, Options const& options,
      google::cloud::managedkafka::schemaregistry::v1::
          ListSchemaTypesRequest const& request) = 0;

  virtual StatusOr<google::api::HttpBody> ListSubjects(
      grpc::ClientContext& context, Options const& options,
      google::cloud::managedkafka::schemaregistry::v1::
          ListSubjectsRequest const& request) = 0;

  virtual StatusOr<google::api::HttpBody> ListSubjectsBySchemaId(
      grpc::ClientContext& context, Options const& options,
      google::cloud::managedkafka::schemaregistry::v1::
          ListSubjectsBySchemaIdRequest const& request) = 0;

  virtual StatusOr<google::api::HttpBody> DeleteSubject(
      grpc::ClientContext& context, Options const& options,
      google::cloud::managedkafka::schemaregistry::v1::
          DeleteSubjectRequest const& request) = 0;

  virtual StatusOr<
      google::cloud::managedkafka::schemaregistry::v1::SchemaVersion>
  LookupVersion(grpc::ClientContext& context, Options const& options,
                google::cloud::managedkafka::schemaregistry::v1::
                    LookupVersionRequest const& request) = 0;

  virtual StatusOr<
      google::cloud::managedkafka::schemaregistry::v1::SchemaVersion>
  GetVersion(
      grpc::ClientContext& context, Options const& options,
      google::cloud::managedkafka::schemaregistry::v1::GetVersionRequest const&
          request) = 0;

  virtual StatusOr<google::api::HttpBody> GetRawSchemaVersion(
      grpc::ClientContext& context, Options const& options,
      google::cloud::managedkafka::schemaregistry::v1::GetVersionRequest const&
          request) = 0;

  virtual StatusOr<google::api::HttpBody> ListVersions(
      grpc::ClientContext& context, Options const& options,
      google::cloud::managedkafka::schemaregistry::v1::
          ListVersionsRequest const& request) = 0;

  virtual StatusOr<
      google::cloud::managedkafka::schemaregistry::v1::CreateVersionResponse>
  CreateVersion(grpc::ClientContext& context, Options const& options,
                google::cloud::managedkafka::schemaregistry::v1::
                    CreateVersionRequest const& request) = 0;

  virtual StatusOr<google::api::HttpBody> DeleteVersion(
      grpc::ClientContext& context, Options const& options,
      google::cloud::managedkafka::schemaregistry::v1::
          DeleteVersionRequest const& request) = 0;

  virtual StatusOr<google::api::HttpBody> ListReferencedSchemas(
      grpc::ClientContext& context, Options const& options,
      google::cloud::managedkafka::schemaregistry::v1::
          ListReferencedSchemasRequest const& request) = 0;

  virtual StatusOr<google::cloud::managedkafka::schemaregistry::v1::
                       CheckCompatibilityResponse>
  CheckCompatibility(grpc::ClientContext& context, Options const& options,
                     google::cloud::managedkafka::schemaregistry::v1::
                         CheckCompatibilityRequest const& request) = 0;

  virtual StatusOr<
      google::cloud::managedkafka::schemaregistry::v1::SchemaConfig>
  GetSchemaConfig(grpc::ClientContext& context, Options const& options,
                  google::cloud::managedkafka::schemaregistry::v1::
                      GetSchemaConfigRequest const& request) = 0;

  virtual StatusOr<
      google::cloud::managedkafka::schemaregistry::v1::SchemaConfig>
  UpdateSchemaConfig(grpc::ClientContext& context, Options const& options,
                     google::cloud::managedkafka::schemaregistry::v1::
                         UpdateSchemaConfigRequest const& request) = 0;

  virtual StatusOr<
      google::cloud::managedkafka::schemaregistry::v1::SchemaConfig>
  DeleteSchemaConfig(grpc::ClientContext& context, Options const& options,
                     google::cloud::managedkafka::schemaregistry::v1::
                         DeleteSchemaConfigRequest const& request) = 0;

  virtual StatusOr<google::cloud::managedkafka::schemaregistry::v1::SchemaMode>
  GetSchemaMode(grpc::ClientContext& context, Options const& options,
                google::cloud::managedkafka::schemaregistry::v1::
                    GetSchemaModeRequest const& request) = 0;

  virtual StatusOr<google::cloud::managedkafka::schemaregistry::v1::SchemaMode>
  UpdateSchemaMode(grpc::ClientContext& context, Options const& options,
                   google::cloud::managedkafka::schemaregistry::v1::
                       UpdateSchemaModeRequest const& request) = 0;

  virtual StatusOr<google::cloud::managedkafka::schemaregistry::v1::SchemaMode>
  DeleteSchemaMode(grpc::ClientContext& context, Options const& options,
                   google::cloud::managedkafka::schemaregistry::v1::
                       DeleteSchemaModeRequest const& request) = 0;

  virtual StatusOr<google::cloud::location::ListLocationsResponse>
  ListLocations(
      grpc::ClientContext& context, Options const& options,
      google::cloud::location::ListLocationsRequest const& request) = 0;

  virtual StatusOr<google::cloud::location::Location> GetLocation(
      grpc::ClientContext& context, Options const& options,
      google::cloud::location::GetLocationRequest const& request) = 0;

  virtual StatusOr<google::longrunning::ListOperationsResponse> ListOperations(
      grpc::ClientContext& context, Options const& options,
      google::longrunning::ListOperationsRequest const& request) = 0;

  virtual StatusOr<google::longrunning::Operation> GetOperation(
      grpc::ClientContext& context, Options const& options,
      google::longrunning::GetOperationRequest const& request) = 0;

  virtual Status DeleteOperation(
      grpc::ClientContext& context, Options const& options,
      google::longrunning::DeleteOperationRequest const& request) = 0;

  virtual Status CancelOperation(
      grpc::ClientContext& context, Options const& options,
      google::longrunning::CancelOperationRequest const& request) = 0;
};

class DefaultManagedSchemaRegistryStub : public ManagedSchemaRegistryStub {
 public:
  explicit DefaultManagedSchemaRegistryStub(
      std::unique_ptr<google::cloud::managedkafka::schemaregistry::v1::
                          ManagedSchemaRegistry::StubInterface>
          grpc_stub,
      std::unique_ptr<google::longrunning::Operations::StubInterface>
          operations_stub,
      std::unique_ptr<google::cloud::location::Locations::StubInterface>
          locations_stub)
      : grpc_stub_(std::move(grpc_stub)),
        operations_stub_(std::move(operations_stub)),
        locations_stub_(std::move(locations_stub)) {}

  StatusOr<google::cloud::managedkafka::schemaregistry::v1::SchemaRegistry>
  GetSchemaRegistry(grpc::ClientContext& context, Options const& options,
                    google::cloud::managedkafka::schemaregistry::v1::
                        GetSchemaRegistryRequest const& request) override;

  StatusOr<google::cloud::managedkafka::schemaregistry::v1::
               ListSchemaRegistriesResponse>
  ListSchemaRegistries(grpc::ClientContext& context, Options const& options,
                       google::cloud::managedkafka::schemaregistry::v1::
                           ListSchemaRegistriesRequest const& request) override;

  StatusOr<google::cloud::managedkafka::schemaregistry::v1::SchemaRegistry>
  CreateSchemaRegistry(grpc::ClientContext& context, Options const& options,
                       google::cloud::managedkafka::schemaregistry::v1::
                           CreateSchemaRegistryRequest const& request) override;

  Status DeleteSchemaRegistry(
      grpc::ClientContext& context, Options const& options,
      google::cloud::managedkafka::schemaregistry::v1::
          DeleteSchemaRegistryRequest const& request) override;

  StatusOr<google::cloud::managedkafka::schemaregistry::v1::Context> GetContext(
      grpc::ClientContext& context, Options const& options,
      google::cloud::managedkafka::schemaregistry::v1::GetContextRequest const&
          request) override;

  StatusOr<google::api::HttpBody> ListContexts(
      grpc::ClientContext& context, Options const& options,
      google::cloud::managedkafka::schemaregistry::v1::
          ListContextsRequest const& request) override;

  StatusOr<google::cloud::managedkafka::schemaregistry::v1::Schema> GetSchema(
      grpc::ClientContext& context, Options const& options,
      google::cloud::managedkafka::schemaregistry::v1::GetSchemaRequest const&
          request) override;

  StatusOr<google::api::HttpBody> GetRawSchema(
      grpc::ClientContext& context, Options const& options,
      google::cloud::managedkafka::schemaregistry::v1::GetSchemaRequest const&
          request) override;

  StatusOr<google::api::HttpBody> ListSchemaVersions(
      grpc::ClientContext& context, Options const& options,
      google::cloud::managedkafka::schemaregistry::v1::
          ListSchemaVersionsRequest const& request) override;

  StatusOr<google::api::HttpBody> ListSchemaTypes(
      grpc::ClientContext& context, Options const& options,
      google::cloud::managedkafka::schemaregistry::v1::
          ListSchemaTypesRequest const& request) override;

  StatusOr<google::api::HttpBody> ListSubjects(
      grpc::ClientContext& context, Options const& options,
      google::cloud::managedkafka::schemaregistry::v1::
          ListSubjectsRequest const& request) override;

  StatusOr<google::api::HttpBody> ListSubjectsBySchemaId(
      grpc::ClientContext& context, Options const& options,
      google::cloud::managedkafka::schemaregistry::v1::
          ListSubjectsBySchemaIdRequest const& request) override;

  StatusOr<google::api::HttpBody> DeleteSubject(
      grpc::ClientContext& context, Options const& options,
      google::cloud::managedkafka::schemaregistry::v1::
          DeleteSubjectRequest const& request) override;

  StatusOr<google::cloud::managedkafka::schemaregistry::v1::SchemaVersion>
  LookupVersion(grpc::ClientContext& context, Options const& options,
                google::cloud::managedkafka::schemaregistry::v1::
                    LookupVersionRequest const& request) override;

  StatusOr<google::cloud::managedkafka::schemaregistry::v1::SchemaVersion>
  GetVersion(
      grpc::ClientContext& context, Options const& options,
      google::cloud::managedkafka::schemaregistry::v1::GetVersionRequest const&
          request) override;

  StatusOr<google::api::HttpBody> GetRawSchemaVersion(
      grpc::ClientContext& context, Options const& options,
      google::cloud::managedkafka::schemaregistry::v1::GetVersionRequest const&
          request) override;

  StatusOr<google::api::HttpBody> ListVersions(
      grpc::ClientContext& context, Options const& options,
      google::cloud::managedkafka::schemaregistry::v1::
          ListVersionsRequest const& request) override;

  StatusOr<
      google::cloud::managedkafka::schemaregistry::v1::CreateVersionResponse>
  CreateVersion(grpc::ClientContext& context, Options const& options,
                google::cloud::managedkafka::schemaregistry::v1::
                    CreateVersionRequest const& request) override;

  StatusOr<google::api::HttpBody> DeleteVersion(
      grpc::ClientContext& context, Options const& options,
      google::cloud::managedkafka::schemaregistry::v1::
          DeleteVersionRequest const& request) override;

  StatusOr<google::api::HttpBody> ListReferencedSchemas(
      grpc::ClientContext& context, Options const& options,
      google::cloud::managedkafka::schemaregistry::v1::
          ListReferencedSchemasRequest const& request) override;

  StatusOr<google::cloud::managedkafka::schemaregistry::v1::
               CheckCompatibilityResponse>
  CheckCompatibility(grpc::ClientContext& context, Options const& options,
                     google::cloud::managedkafka::schemaregistry::v1::
                         CheckCompatibilityRequest const& request) override;

  StatusOr<google::cloud::managedkafka::schemaregistry::v1::SchemaConfig>
  GetSchemaConfig(grpc::ClientContext& context, Options const& options,
                  google::cloud::managedkafka::schemaregistry::v1::
                      GetSchemaConfigRequest const& request) override;

  StatusOr<google::cloud::managedkafka::schemaregistry::v1::SchemaConfig>
  UpdateSchemaConfig(grpc::ClientContext& context, Options const& options,
                     google::cloud::managedkafka::schemaregistry::v1::
                         UpdateSchemaConfigRequest const& request) override;

  StatusOr<google::cloud::managedkafka::schemaregistry::v1::SchemaConfig>
  DeleteSchemaConfig(grpc::ClientContext& context, Options const& options,
                     google::cloud::managedkafka::schemaregistry::v1::
                         DeleteSchemaConfigRequest const& request) override;

  StatusOr<google::cloud::managedkafka::schemaregistry::v1::SchemaMode>
  GetSchemaMode(grpc::ClientContext& context, Options const& options,
                google::cloud::managedkafka::schemaregistry::v1::
                    GetSchemaModeRequest const& request) override;

  StatusOr<google::cloud::managedkafka::schemaregistry::v1::SchemaMode>
  UpdateSchemaMode(grpc::ClientContext& context, Options const& options,
                   google::cloud::managedkafka::schemaregistry::v1::
                       UpdateSchemaModeRequest const& request) override;

  StatusOr<google::cloud::managedkafka::schemaregistry::v1::SchemaMode>
  DeleteSchemaMode(grpc::ClientContext& context, Options const& options,
                   google::cloud::managedkafka::schemaregistry::v1::
                       DeleteSchemaModeRequest const& request) override;

  StatusOr<google::cloud::location::ListLocationsResponse> ListLocations(
      grpc::ClientContext& context, Options const& options,
      google::cloud::location::ListLocationsRequest const& request) override;

  StatusOr<google::cloud::location::Location> GetLocation(
      grpc::ClientContext& context, Options const& options,
      google::cloud::location::GetLocationRequest const& request) override;

  StatusOr<google::longrunning::ListOperationsResponse> ListOperations(
      grpc::ClientContext& context, Options const& options,
      google::longrunning::ListOperationsRequest const& request) override;

  StatusOr<google::longrunning::Operation> GetOperation(
      grpc::ClientContext& context, Options const& options,
      google::longrunning::GetOperationRequest const& request) override;

  Status DeleteOperation(
      grpc::ClientContext& context, Options const& options,
      google::longrunning::DeleteOperationRequest const& request) override;

  Status CancelOperation(
      grpc::ClientContext& context, Options const& options,
      google::longrunning::CancelOperationRequest const& request) override;

 private:
  std::unique_ptr<google::cloud::managedkafka::schemaregistry::v1::
                      ManagedSchemaRegistry::StubInterface>
      grpc_stub_;
  std::unique_ptr<google::longrunning::Operations::StubInterface>
      operations_stub_;
  std::unique_ptr<google::cloud::location::Locations::StubInterface>
      locations_stub_;
};

GOOGLE_CLOUD_CPP_INLINE_NAMESPACE_END
}  // namespace managedkafka_schemaregistry_v1_internal
}  // namespace cloud
}  // namespace google

#endif  // GOOGLE_CLOUD_CPP_GOOGLE_CLOUD_MANAGEDKAFKA_SCHEMAREGISTRY_V1_INTERNAL_MANAGED_SCHEMA_REGISTRY_STUB_H
