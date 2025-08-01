#!/usr/bin/env bash
# Copyright 2021 Google LLC
#
# Licensed under the Apache License, Version 2.0 (the "License");
# you may not use this file except in compliance with the License.
# You may obtain a copy of the License at
#
#     https://www.apache.org/licenses/LICENSE-2.0
#
# Unless required by applicable law or agreed to in writing, software
# distributed under the License is distributed on an "AS IS" BASIS,
# WITHOUT WARRANTIES OR CONDITIONS OF ANY KIND, either express or implied.
# See the License for the specific language governing permissions and
# limitations under the License.

set -euo pipefail

declare -A -r LIBRARIES=(
  ["accessapproval"]="@com_google_googleapis//google/cloud/accessapproval/v1:accessapproval_cc_grpc"
  ["accesscontextmanager"]="$(
    printf ",%s" \
      "@com_google_googleapis//google/identity/accesscontextmanager/type:type_cc_grpc" \
      "@com_google_googleapis//google/identity/accesscontextmanager/v1:accesscontextmanager_cc_grpc"
  )"
  ["advisorynotifications"]="@com_google_googleapis//google/cloud/advisorynotifications/v1:advisorynotifications_cc_grpc"
  ["aiplatform"]="$(
    printf ",%s" \
      "@com_google_googleapis//google/cloud/aiplatform/logging:logging_cc_grpc" \
      "@com_google_googleapis//google/cloud/aiplatform/v1:aiplatform_cc_grpc" \
      "@com_google_googleapis//google/cloud/aiplatform/v1/schema/predict/instance:instance_cc_grpc" \
      "@com_google_googleapis//google/cloud/aiplatform/v1/schema/predict/params:params_cc_grpc" \
      "@com_google_googleapis//google/cloud/aiplatform/v1/schema/predict/prediction:prediction_cc_grpc" \
      "@com_google_googleapis//google/cloud/aiplatform/v1/schema/trainingjob/definition:definition_cc_grpc"
  )"
  ["alloydb"]="@com_google_googleapis//google/cloud/alloydb/v1:alloydb_cc_grpc"
  ["apigateway"]="@com_google_googleapis//google/cloud/apigateway/v1:apigateway_cc_grpc"
  ["apigeeconnect"]="@com_google_googleapis//google/cloud/apigeeconnect/v1:apigeeconnect_cc_grpc"
  ["apikeys"]="@com_google_googleapis//google/api/apikeys/v2:apikeys_cc_grpc"
  ["appengine"]="$(
    printf ",%s" \
      "@com_google_googleapis//google/appengine/v1:appengine_cc_grpc" \
      "@com_google_googleapis//google/appengine/logging/v1:logging_cc_grpc" \
      "@com_google_googleapis//google/appengine/legacy:legacy_cc_grpc"
  )"
  ["apphub"]="@com_google_googleapis//google/cloud/apphub/v1:apphub_cc_grpc"
  ["artifactregistry"]="@com_google_googleapis//google/devtools/artifactregistry/v1:artifactregistry_cc_grpc"
  ["asset"]="@com_google_googleapis//google/cloud/asset/v1:asset_cc_grpc"
  ["assuredworkloads"]="@com_google_googleapis//google/cloud/assuredworkloads/v1:assuredworkloads_cc_grpc"
  ["automl"]="@com_google_googleapis//google/cloud/automl/v1:automl_cc_grpc"
  ["backupdr"]="$(
    printf ",%s" \
      "@com_google_googleapis//google/cloud/backupdr/v1:backupdr_cc_grpc" \
      "@com_google_googleapis//google/cloud/backupdr/logging/v1:logging_cc_grpc"
  )"
  ["baremetalsolution"]="@com_google_googleapis//google/cloud/baremetalsolution/v2:baremetalsolution_cc_grpc"
  ["batch"]="@com_google_googleapis//google/cloud/batch/v1:batch_cc_grpc"
  ["beyondcorp"]="$(
    printf ",%s" \
      "@com_google_googleapis//google/cloud/beyondcorp/appconnections/v1:appconnections_cc_grpc" \
      "@com_google_googleapis//google/cloud/beyondcorp/appconnectors/v1:appconnectors_cc_grpc" \
      "@com_google_googleapis//google/cloud/beyondcorp/appgateways/v1:appgateways_cc_grpc"
  )"
  ["bigquery"]="$(
    # This is long enough that it needs to be kept in alphabetical order
    printf ",%s" \
      "@com_google_googleapis//google/cloud/bigquery/analyticshub/v1:analyticshub_cc_grpc" \
      "@com_google_googleapis//google/cloud/bigquery/biglake/v1:biglake_cc_grpc" \
      "@com_google_googleapis//google/cloud/bigquery/connection/v1:connection_cc_grpc" \
      "@com_google_googleapis//google/cloud/bigquery/datapolicies/v1:datapolicies_cc_grpc" \
      "@com_google_googleapis//google/cloud/bigquery/datapolicies/v2:datapolicies_cc_grpc" \
      "@com_google_googleapis//google/cloud/bigquery/datatransfer/v1:datatransfer_cc_grpc" \
      "@com_google_googleapis//google/cloud/bigquery/logging/v1:logging_cc_grpc" \
      "@com_google_googleapis//google/cloud/bigquery/migration/v2:migration_cc_grpc" \
      "@com_google_googleapis//google/cloud/bigquery/reservation/v1:reservation_cc_grpc" \
      "@com_google_googleapis//google/cloud/bigquery/storage/v1:storage_cc_grpc"
  )"
  ["bigquerycontrol"]="@com_google_googleapis//google/cloud/bigquery/v2:bigquery_cc_proto"
  ["bigtable"]="$(
    printf ",%s" \
      "@com_google_googleapis//google/bigtable/v2:bigtable_cc_grpc" \
      "@com_google_googleapis//google/bigtable/admin/v2:admin_cc_grpc"
  )"
  ["billing"]="$(
    printf ",%s" \
      "@com_google_googleapis//google/cloud/billing/v1:billing_cc_grpc" \
      "@com_google_googleapis//google/cloud/billing/budgets/v1:budgets_cc_grpc"
  )"
  ["binaryauthorization"]="@com_google_googleapis//google/cloud/binaryauthorization/v1:binaryauthorization_cc_grpc"
  ["certificatemanager"]="$(
    printf ",%s" \
      "@com_google_googleapis//google/cloud/certificatemanager/logging/v1:logging_cc_grpc" \
      "@com_google_googleapis//google/cloud/certificatemanager/v1:certificatemanager_cc_grpc"
  )"
  ["channel"]="@com_google_googleapis//google/cloud/channel/v1:channel_cc_grpc"
  ["chronicle"]="@com_google_googleapis//google/cloud/chronicle/v1:chronicle_cc_grpc"
  ["cloudbuild"]="$(
    printf ",%s" \
      "@com_google_googleapis//google/devtools/cloudbuild/v1:cloudbuild_cc_grpc" \
      "@com_google_googleapis//google/devtools/cloudbuild/v2:cloudbuild_cc_grpc"
  )"
  ["cloudcontrolspartner"]="@com_google_googleapis//google/cloud/cloudcontrolspartner/v1:cloudcontrolspartner_cc_grpc"
  ["cloudquotas"]="@com_google_googleapis//google/api/cloudquotas/v1:cloudquotas_cc_grpc"
  ["commerce"]="@com_google_googleapis//google/cloud/commerce/consumer/procurement/v1:procurement_cc_grpc"
  ["common"]="@com_google_googleapis//google/cloud/common:common_cc_grpc"
  ["composer"]="@com_google_googleapis//google/cloud/orchestration/airflow/service/v1:service_cc_grpc"
  ["confidentialcomputing"]="@com_google_googleapis//google/cloud/confidentialcomputing/v1:confidentialcomputing_cc_grpc"
  ["config"]="@com_google_googleapis//google/cloud/config/v1:config_cc_grpc"
  ["connectors"]="@com_google_googleapis//google/cloud/connectors/v1:connectors_cc_grpc"
  ["contactcenterinsights"]="@com_google_googleapis//google/cloud/contactcenterinsights/v1:contactcenterinsights_cc_grpc"
  ["container"]="@com_google_googleapis//google/container/v1:container_cc_grpc"
  ["containeranalysis"]="@com_google_googleapis//google/devtools/containeranalysis/v1:containeranalysis_cc_grpc"
  ["contentwarehouse"]="@com_google_googleapis//google/cloud/contentwarehouse/v1:contentwarehouse_cc_grpc"
  ["datacatalog"]="$(
    printf ",%s" \
      "@com_google_googleapis//google/cloud/datacatalog/v1:datacatalog_cc_grpc" \
      "@com_google_googleapis//google/cloud/datacatalog/lineage/v1:lineage_cc_grpc"
  )"
  ["dataform"]="$(
    printf ",%s" \
      "@com_google_googleapis//google/cloud/dataform/v1:dataform_cc_grpc" \
      "@com_google_googleapis//google/cloud/dataform/logging/v1:logging_cc_grpc"
  )"
  ["datafusion"]="@com_google_googleapis//google/cloud/datafusion/v1:datafusion_cc_grpc"
  ["datamigration"]="$(
    printf ",%s" \
      "@com_google_googleapis//google/cloud/clouddms/v1:clouddms_cc_grpc" \
      "@com_google_googleapis//google/cloud/clouddms/logging/v1:logging_cc_grpc"
  )"
  ["dataplex"]="@com_google_googleapis//google/cloud/dataplex/v1:dataplex_cc_grpc"
  ["dataproc"]="@com_google_googleapis//google/cloud/dataproc/v1:dataproc_cc_grpc"
  ["datastore"]="$(
    printf ",%s" \
      "@com_google_googleapis//google/datastore/admin/v1:admin_cc_grpc" \
      "@com_google_googleapis//google/datastore/v1:datastore_cc_grpc"
  )"
  ["datastream"]="@com_google_googleapis//google/cloud/datastream/v1:datastream_cc_grpc"
  ["deploy"]="@com_google_googleapis//google/cloud/deploy/v1:deploy_cc_grpc"
  ["developerconnect"]="@com_google_googleapis//google/cloud/developerconnect/v1:developerconnect_cc_grpc"
  ["devicestreaming"]="@com_google_googleapis//google/cloud/devicestreaming/v1:devicestreaming_cc_grpc"
  ["dialogflow_es"]="@com_google_googleapis//google/cloud/dialogflow/v2:dialogflow_cc_grpc"
  ["dialogflow_cx"]="@com_google_googleapis//google/cloud/dialogflow/cx/v3:cx_cc_grpc"
  ["discoveryengine"]="@com_google_googleapis//google/cloud/discoveryengine/v1:discoveryengine_cc_grpc"
  ["dlp"]="@com_google_googleapis//google/privacy/dlp/v2:dlp_cc_grpc"
  ["documentai"]="@com_google_googleapis//google/cloud/documentai/v1:documentai_cc_grpc"
  ["domains"]="@com_google_googleapis//google/cloud/domains/v1:domains_cc_grpc"
  ["edgecontainer"]="@com_google_googleapis//google/cloud/edgecontainer/v1:edgecontainer_cc_grpc"
  ["edgenetwork"]="@com_google_googleapis//google/cloud/edgenetwork/v1:edgenetwork_cc_grpc"
  ["essentialcontacts"]="@com_google_googleapis//google/cloud/essentialcontacts/v1:essentialcontacts_cc_grpc"
  ["eventarc"]="$(
    printf ",%s" \
      "@com_google_googleapis//google/cloud/eventarc/v1:eventarc_cc_grpc" \
      "@com_google_googleapis//google/cloud/eventarc/publishing/v1:publishing_cc_grpc"
  )"
  ["filestore"]="@com_google_googleapis//google/cloud/filestore/v1:filestore_cc_grpc"
  ["financialservices"]="@com_google_googleapis//google/cloud/financialservices/v1:financialservices_cc_grpc"
  ["functions"]="$(
    printf ",%s" \
      "@com_google_googleapis//google/cloud/functions/v1:functions_cc_grpc" \
      "@com_google_googleapis//google/cloud/functions/v2:functions_cc_grpc"
  )"
  ["gkebackup"]="$(
    printf ",%s" \
      "@com_google_googleapis//google/cloud/gkebackup/logging/v1:logging_cc_grpc" \
      "@com_google_googleapis//google/cloud/gkebackup/v1:gkebackup_cc_grpc"
  )"
  ["gkeconnect"]="@com_google_googleapis//google/cloud/gkeconnect/gateway/v1:gateway_cc_grpc"
  ["gkehub"]="$(
    printf ",%s" \
      "@com_google_googleapis//google/cloud/gkehub/v1:gkehub_cc_grpc" \
      "@com_google_googleapis//google/cloud/gkehub/v1/multiclusteringress:multiclusteringress_cc_grpc" \
      "@com_google_googleapis//google/cloud/gkehub/v1/configmanagement:configmanagement_cc_grpc"
  )"
  ["gkemulticloud"]="@com_google_googleapis//google/cloud/gkemulticloud/v1:gkemulticloud_cc_grpc"
  ["grafeas"]="@com_google_googleapis//grafeas/v1:grafeas_cc_grpc"
  ["iam"]="@com_google_googleapis//google/iam/admin/v1:admin_cc_grpc"
  ["iam_v2"]="@com_google_googleapis//google/iam/v2:iam_cc_grpc"
  ["iam_v3"]="@com_google_googleapis//google/iam/v3:iam_cc_grpc"
  ["iap"]="@com_google_googleapis//google/cloud/iap/v1:iap_cc_grpc"
  ["ids"]="@com_google_googleapis//google/cloud/ids/v1:ids_cc_grpc"
  ["kms"]="$(
    printf ",%s" \
      "@com_google_googleapis//google/cloud/kms/v1:kms_cc_grpc" \
      "@com_google_googleapis//google/cloud/kms/inventory/v1:inventory_cc_grpc"
  )"
  ["language"]="$(
    printf ",%s" \
      "@com_google_googleapis//google/cloud/language/v1:language_cc_grpc" \
      "@com_google_googleapis//google/cloud/language/v2:language_cc_grpc"
  )"
  ["licensemanager"]="@com_google_googleapis//google/cloud/licensemanager/v1:licensemanager_cc_grpc"
  ["logging_type"]="@com_google_googleapis//google/logging/type:type_cc_grpc"
  ["logging"]="@com_google_googleapis//google/logging/v2:logging_cc_grpc"
  ["lustre"]="@com_google_googleapis//google/cloud/lustre/v1:lustre_cc_grpc"
  ["managedidentities"]="@com_google_googleapis//google/cloud/managedidentities/v1:managedidentities_cc_grpc"
  ["managedkafka"]="$(
    printf ",%s" \
      "@com_google_googleapis//google/cloud/managedkafka/schemaregistry/v1:schemaregistry_cc_grpc" \
      "@com_google_googleapis//google/cloud/managedkafka/v1:managedkafka_cc_grpc"
  )"
  ["memcache"]="@com_google_googleapis//google/cloud/memcache/v1:memcache_cc_grpc"
  ["memorystore"]="@com_google_googleapis//google/cloud/memorystore/v1:memorystore_cc_grpc"
  ["metastore"]="$(
    printf ",%s" \
      "@com_google_googleapis//google/cloud/metastore/logging/v1:logging_cc_grpc" \
      "@com_google_googleapis//google/cloud/metastore/v1:metastore_cc_grpc"
  )"
  ["migrationcenter"]="@com_google_googleapis//google/cloud/migrationcenter/v1:migrationcenter_cc_grpc"
  ["monitoring"]="$(
    printf ",%s" \
      "@com_google_googleapis//google/monitoring/v3:monitoring_cc_grpc" \
      "@com_google_googleapis//google/monitoring/dashboard/v1:dashboard_cc_grpc" \
      "@com_google_googleapis//google/monitoring/metricsscope/v1:metricsscope_cc_grpc"
  )"
  ["netapp"]="@com_google_googleapis//google/cloud/netapp/v1:netapp_cc_grpc"
  ["networkconnectivity"]="@com_google_googleapis//google/cloud/networkconnectivity/v1:networkconnectivity_cc_grpc"
  ["networkmanagement"]="@com_google_googleapis//google/cloud/networkmanagement/v1:networkmanagement_cc_grpc"
  ["networksecurity"]="@com_google_googleapis//google/cloud/networksecurity/v1:networksecurity_cc_grpc"
  ["networkservices"]="@com_google_googleapis//google/cloud/networkservices/v1:networkservices_cc_grpc"
  ["notebooks"]="$(
    printf ",%s" \
      "@com_google_googleapis//google/cloud/notebooks/v1:notebooks_cc_grpc" \
      "@com_google_googleapis//google/cloud/notebooks/v2:notebooks_cc_grpc"
  )"
  ["optimization"]="@com_google_googleapis//google/cloud/optimization/v1:optimization_cc_grpc"
  ["oracledatabase"]="@com_google_googleapis//google/cloud/oracledatabase/v1:oracledatabase_cc_grpc"
  ["orgpolicy"]="@com_google_googleapis//google/cloud/orgpolicy/v2:orgpolicy_cc_grpc"
  ["osconfig"]="$(
    printf ",%s" \
      "@com_google_googleapis//google/cloud/osconfig/agentendpoint/v1:agentendpoint_cc_grpc" \
      "@com_google_googleapis//google/cloud/osconfig/v1:osconfig_cc_grpc"
  )"
  ["oslogin"]="$(
    printf ",%s" \
      "@com_google_googleapis//google/cloud/oslogin/v1:oslogin_cc_grpc" \
      "@com_google_googleapis//google/cloud/oslogin/common:common_cc_grpc"
  )"
  ["parametermanager"]="@com_google_googleapis//google/cloud/parametermanager/v1:parametermanager_cc_grpc"
  ["parallelstore"]="@com_google_googleapis//google/cloud/parallelstore/v1:parallelstore_cc_grpc"
  ["policysimulator"]="@com_google_googleapis//google/cloud/policysimulator/v1:policysimulator_cc_grpc"
  ["policytroubleshooter"]="$(
    printf ",%s" \
      "@com_google_googleapis//google/cloud/policytroubleshooter/v1:policytroubleshooter_cc_grpc" \
      "@com_google_googleapis//google/cloud/policytroubleshooter/iam/v3:iam_cc_grpc"
  )"
  ["privateca"]="@com_google_googleapis//google/cloud/security/privateca/v1:privateca_cc_grpc"
  ["privilegedaccessmanager"]="@com_google_googleapis//google/cloud/privilegedaccessmanager/v1:privilegedaccessmanager_cc_grpc"
  ["profiler"]="@com_google_googleapis//google/devtools/cloudprofiler/v2:cloudprofiler_cc_grpc"
  ["publicca"]="@com_google_googleapis//google/cloud/security/publicca/v1:publicca_cc_grpc"
  ["pubsub"]="@com_google_googleapis//google/pubsub/v1:pubsub_cc_grpc"
  ["pubsublite"]="@com_google_googleapis//google/cloud/pubsublite/v1:pubsublite_cc_grpc"
  ["rapidmigrationassessment"]="@com_google_googleapis//google/cloud/rapidmigrationassessment/v1:rapidmigrationassessment_cc_grpc"
  ["recaptchaenterprise"]="@com_google_googleapis//google/cloud/recaptchaenterprise/v1:recaptchaenterprise_cc_grpc"
  ["recommender"]="$(
    printf ",%s" \
      "@com_google_googleapis//google/cloud/recommender/v1:recommender_cc_grpc" \
      "@com_google_googleapis//google/cloud/recommender/logging/v1:logging_cc_grpc"
  )"
  ["redis"]="$(
    printf ",%s" \
      "@com_google_googleapis//google/cloud/redis/cluster/v1:cluster_cc_grpc" \
      "@com_google_googleapis//google/cloud/redis/v1:redis_cc_grpc"
  )"
  ["resourcemanager"]="@com_google_googleapis//google/cloud/resourcemanager/v3:resourcemanager_cc_grpc"
  ["retail"]="@com_google_googleapis//google/cloud/retail/v2:retail_cc_grpc"
  ["run"]="@com_google_googleapis//google/cloud/run/v2:run_cc_grpc"
  ["scheduler"]="@com_google_googleapis//google/cloud/scheduler/v1:scheduler_cc_grpc"
  ["secretmanager"]="$(
    printf ",%s" \
      "@com_google_googleapis//google/cloud/secretmanager/v1:secretmanager_cc_grpc" \
      "@com_google_googleapis//google/cloud/secretmanager/logging/v1:logging_cc_grpc"
  )"
  ["securesourcemanager"]="@com_google_googleapis//google/cloud/securesourcemanager/v1:securesourcemanager_cc_grpc"
  ["securitycenter"]="$(
    printf ",%s" \
      "@com_google_googleapis//google/cloud/securitycenter/v1:securitycenter_cc_grpc" \
      "@com_google_googleapis//google/cloud/securitycenter/v2:securitycenter_cc_grpc"
  )"
  ["securitycentermanagement"]="@com_google_googleapis//google/cloud/securitycentermanagement/v1:securitycentermanagement_cc_grpc"
  ["servicecontrol"]="$(
    printf ",%s" \
      "@com_google_googleapis//google/api/servicecontrol/v1:servicecontrol_cc_grpc" \
      "@com_google_googleapis//google/api/servicecontrol/v2:servicecontrol_cc_grpc"
  )"
  ["servicedirectory"]="@com_google_googleapis//google/cloud/servicedirectory/v1:servicedirectory_cc_grpc"
  ["servicehealth"]="$(
    printf ",%s" \
      "@com_google_googleapis//google/cloud/servicehealth/v1:servicehealth_cc_grpc" \
      "@com_google_googleapis//google/cloud/servicehealth/logging/v1:logging_cc_grpc"
  )"
  ["servicemanagement"]="@com_google_googleapis//google/api/servicemanagement/v1:servicemanagement_cc_grpc"
  ["serviceusage"]="@com_google_googleapis//google/api/serviceusage/v1:serviceusage_cc_grpc"
  ["shell"]="@com_google_googleapis//google/cloud/shell/v1:shell_cc_grpc"
  ["spanner"]="$(
    printf ",%s" \
      "@com_google_googleapis//google/spanner/v1:spanner_cc_grpc" \
      "@com_google_googleapis//google/spanner/admin/instance/v1:instance_cc_grpc" \
      "@com_google_googleapis//google/spanner/admin/database/v1:database_cc_grpc"
  )"
  ["speech"]="$(
    printf ",%s" \
      "@com_google_googleapis//google/cloud/speech/v1:speech_cc_grpc" \
      "@com_google_googleapis//google/cloud/speech/v2:speech_cc_grpc"
  )"
  ["sql"]="@com_google_googleapis//google/cloud/sql/v1:sql_cc_proto"
  ["storage"]="@com_google_googleapis//google/storage/v2:storage_cc_grpc"
  ["storagebatchoperations"]="@com_google_googleapis//google/cloud/storagebatchoperations/v1:storagebatchoperations_cc_grpc"
  ["storagecontrol"]="@com_google_googleapis//google/storage/control/v2:control_cc_grpc"
  ["storageinsights"]="@com_google_googleapis//google/cloud/storageinsights/v1:storageinsights_cc_grpc"
  ["storagetransfer"]="@com_google_googleapis//google/storagetransfer/v1:storagetransfer_cc_grpc"
  ["support"]="@com_google_googleapis//google/cloud/support/v2:support_cc_grpc"
  ["talent"]="@com_google_googleapis//google/cloud/talent/v4:talent_cc_grpc"
  ["tasks"]="@com_google_googleapis//google/cloud/tasks/v2:tasks_cc_grpc"
  ["telcoautomation"]="@com_google_googleapis//google/cloud/telcoautomation/v1:telcoautomation_cc_grpc"
  ["texttospeech"]="@com_google_googleapis//google/cloud/texttospeech/v1:texttospeech_cc_grpc"
  ["timeseriesinsights"]="@com_google_googleapis//google/cloud/timeseriesinsights/v1:timeseriesinsights_cc_grpc"
  ["tpu"]="$(
    printf ",%s" \
      "@com_google_googleapis//google/cloud/tpu/v1:tpu_cc_grpc" \
      "@com_google_googleapis//google/cloud/tpu/v2:tpu_cc_grpc"
  )"
  ["trace"]="$(
    printf ",%s" \
      "@com_google_googleapis//google/devtools/cloudtrace/v1:cloudtrace_cc_grpc" \
      "@com_google_googleapis//google/devtools/cloudtrace/v2:cloudtrace_cc_grpc"
  )"
  ["translate"]="@com_google_googleapis//google/cloud/translate/v3:translation_cc_grpc"
  ["video"]="$(
    printf ",%s" \
      "@com_google_googleapis//google/cloud/video/livestream/v1:livestream_cc_grpc" \
      "@com_google_googleapis//google/cloud/video/stitcher/v1:stitcher_cc_grpc" \
      "@com_google_googleapis//google/cloud/video/transcoder/v1:transcoder_cc_grpc"
  )"
  ["videointelligence"]="@com_google_googleapis//google/cloud/videointelligence/v1:videointelligence_cc_grpc"
  ["vision"]="@com_google_googleapis//google/cloud/vision/v1:vision_cc_grpc"
  ["vmmigration"]="@com_google_googleapis//google/cloud/vmmigration/v1:vmmigration_cc_grpc"
  ["vmwareengine"]="@com_google_googleapis//google/cloud/vmwareengine/v1:vmwareengine_cc_grpc"
  ["vpcaccess"]="@com_google_googleapis//google/cloud/vpcaccess/v1:vpcaccess_cc_grpc"
  ["webrisk"]="@com_google_googleapis//google/cloud/webrisk/v1:webrisk_cc_grpc"
  ["websecurityscanner"]="@com_google_googleapis//google/cloud/websecurityscanner/v1:websecurityscanner_cc_grpc"
  ["workflows"]="$(
    printf ",%s" \
      "@com_google_googleapis//google/cloud/workflows/v1:workflows_cc_grpc" \
      "@com_google_googleapis//google/cloud/workflows/type:type_cc_grpc" \
      "@com_google_googleapis//google/cloud/workflows/executions/v1:executions_cc_grpc"
  )"
  ["workstations"]="$(
    printf ",%s" \
      "@com_google_googleapis//google/cloud/workstations/logging/v1:logging_cc_grpc" \
      "@com_google_googleapis//google/cloud/workstations/v1:workstations_cc_grpc"
  )"
)

if [[ $# -eq 0 ]]; then
  keys=("${!LIBRARIES[@]}")
else
  keys=("$@")
fi

for library in "${keys[@]}"; do
  IFS=',' read -r -a rules <<<"${LIBRARIES[$library]}"
  files=(
    "external/googleapis/protolists/${library}.list"
    "external/googleapis/protodeps/${library}.deps"
  )
  for file in "${files[@]}"; do
    : >"${file}"
  done
  for rule in "${rules[@]}"; do
    if [[ -z "${rule}" ]]; then continue; fi
    path="${rule%:*}"
    echo "=== $library $rule $path"
    bazelisk query --noshow_progress --noshow_loading_progress \
      "deps(${rule})" |
      grep "${path}" |
      grep -E '\.proto$' \
        >>"external/googleapis/protolists/${library}.list" || true
    bazelisk query --noshow_progress --noshow_loading_progress \
      "deps(${rule})" |
      grep "@com_google_googleapis//" | grep _proto |
      grep -v "${path}" \
        >>"external/googleapis/protodeps/${library}.deps" || true
  done
  for file in "${files[@]}"; do
    LC_ALL=C sort -u "${file}" >"${file}.sorted"
    mv "${file}.sorted" "${file}"
  done
done

# TODO(#11694) - the Bazel file introduces a dependency that we do not build.
#    Fortunately (maybe?) we do not use or need the dep until the issue is
#    resolved.
sed -i '/@com_google_googleapis\/\/google\/cloud\/location:location_proto/d' \
  "external/googleapis/protodeps/datamigration.deps"
