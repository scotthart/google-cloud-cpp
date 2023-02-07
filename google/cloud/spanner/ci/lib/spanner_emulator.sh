#!/usr/bin/env bash
#
# Copyright 2020 Google LLC
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

# Make our include guard clean against set -o nounset.
test -n "${GOOGLE_CLOUD_SPANNER_CI_LIB_SPANNER_EMULATOR_SH__:-}" || declare -i GOOGLE_CLOUD_SPANNER_CI_LIB_SPANNER_EMULATOR_SH__=0
if ((GOOGLE_CLOUD_SPANNER_CI_LIB_SPANNER_EMULATOR_SH__++ != 0)); then
  return 0
fi # include guard

source module /ci/lib/io.sh

# Global variable that holds the PIDs of the Spanner emulators. These will be set
# when the emulators are started, and will be used to kill the emulators.
SPANNER_EMULATOR_PID=0
SPANNER_HTTP_EMULATOR_PID=0

# Outputs the port number that the emulator chose to listen on.
function spanner_emulator::internal::read_emulator_port() {
  local -r logfile="$1"
  shift

  local emulator_port="0"
  local -r expected=" : Server address: "
  for _ in $(seq 1 8); do
    if grep -q -s "${expected}" "${logfile}"; then
      # The port number is whatever is after the last ':'.
      emulator_port=$(grep "${expected}" "${logfile}" | awk -F: '{print $NF}')
      break
    fi
    sleep 1
  done
  echo "${emulator_port}"
}

# Outputs the port number that the emulator chose to listen on.
function spanner_emulator::internal::read_http_emulator_port() {
  local -r logfile="$1"
  shift

  local http_emulator_port="0"
  local -r expected=": REST server listening at localhost:"
  for _ in $(seq 1 8); do
    if grep -q -s "${expected}" "${logfile}"; then
      # The port number is whatever is after the last ':'.
      http_emulator_port=$(grep "${expected}" "${logfile}" | awk -F: '{print $NF}')
      break
    fi
    sleep 1
  done
  echo "${http_emulator_port}"
}

# Starts the cloud spanner emulator. On success, exports the
# SPANNER_EMULATOR_HOST environment variable containing the host:port where the
# emulator is listening.
function spanner_emulator::start() {
  io::log "Launching Cloud Spanner emulator in the background"
  if [[ -z "${CLOUD_SDK_LOCATION:-}" ]]; then
    echo 1>&2 "You must set CLOUD_SDK_LOCATION to find the emulator"
    return 1
  fi

  local emulator_port=0
  if [[ $# -ge 1 ]]; then
    emulator_port=$1
  fi

  # We cannot use `gcloud beta emulators spanner start` because there is no way
  # to kill the emulator at the end using that command.
  readonly SPANNER_EMULATOR_CMD="${CLOUD_SDK_LOCATION}/bin/cloud_spanner_emulator/emulator_main"
  if [[ ! -x "${SPANNER_EMULATOR_CMD}" ]]; then
    echo 1>&2 "The Cloud Spanner emulator does not seem to be installed, aborting"
    return 1
  fi

  # The tests typically run in a Docker container, where the ports are largely
  # free; when using in manual tests, you can set EMULATOR_PORT.
  rm -f emulator.log
  "${SPANNER_EMULATOR_CMD}" --host_port "localhost:${emulator_port}" >emulator.log 2>&1 </dev/null &
  SPANNER_EMULATOR_PID=$!

  emulator_port="$(spanner_emulator::internal::read_emulator_port emulator.log)"
  if [[ "${emulator_port}" = "0" ]]; then
    io::log_red "Cannot determine Cloud Spanner emulator port." >&2
    cat emulator.log >&2
    spanner_emulator::kill
    return 1
  fi

  # 2023-01-25T22:24:25Z (+165s): Launching Cloud Spanner emulator in the background
  # 2023-01-25T22:24:26Z (+166s): Spanner emulator started at localhost:8787

  export SPANNER_EMULATOR_HOST="localhost:${emulator_port}"
  io::log "Spanner emulator started at ${SPANNER_EMULATOR_HOST}"

  # 2023-01-25T22:29:30Z (+470s): Launching Cloud Spanner emulator in the background
  # 2023-01-25T22:29:31Z (+471s): Spanner emulator started at localhost:8787
  # 2023-01-25T22:29:31Z (+471s): Spanner HTTP emulator started at localhost:8788

  # We cannot use `gcloud beta emulators spanner start` because there is no way
  # to kill the emulator at the end using that command.
  readonly SPANNER_HTTP_EMULATOR_CMD="${CLOUD_SDK_LOCATION}/bin/cloud_spanner_emulator/gateway_main"
  if [[ ! -x "${SPANNER_HTTP_EMULATOR_CMD}" ]]; then
    echo 1>&2 "The Cloud Spanner HTTP emulator does not seem to be installed, aborting"
    return 1
  fi

  # The tests typically run in a Docker container, where the ports are largely
  # free; when using in manual tests, you can set EMULATOR_PORT.
  rm -f http_emulator.log
  local http_port=$((emulator_port + 1))
  local grpc_port=$((http_port + 1))
  "${SPANNER_HTTP_EMULATOR_CMD}" --hostname "localhost" \
      --grpc_port "${grpc_port}" --http_port "${http_port}" \
      >http_emulator.log 2>&1 </dev/null &
  SPANNER_HTTP_EMULATOR_PID=$!

  http_emulator_port="$(spanner_emulator::internal::read_http_emulator_port http_emulator.log)"
  if [[ "${http_emulator_port}" = "0" ]]; then
    io::log_red "Cannot determine Cloud Spanner HTTP emulator port." >&2
    cat http_emulator.log >&2
    spanner_emulator::kill
    return 1
  fi

  export SPANNER_EMULATOR_REST_HOST="http://localhost:${http_emulator_port}"
  io::log "Spanner HTTP emulator started at ${SPANNER_EMULATOR_REST_HOST}"
}

# Kills the running emulator.
function spanner_emulator::kill() {
  if (("${SPANNER_EMULATOR_PID}" > 0)); then
    echo -n "Killing Spanner Emulator [${SPANNER_EMULATOR_PID}] "
    kill "${SPANNER_EMULATOR_PID}" || echo -n "-"
    wait "${SPANNER_EMULATOR_PID}" >/dev/null 2>&1 || echo -n "+"
    echo -n "."
    echo " done."
    SPANNER_EMULATOR_PID=0
  fi
  if (("${SPANNER_HTTP_EMULATOR_PID}" > 0)); then
    echo -n "Killing Spanner HTTP Emulator [${SPANNER_HTTP_EMULATOR_PID}] "
    kill "${SPANNER_HTTP_EMULATOR_PID}" || echo -n "-"
    wait "${SPANNER_HTTP_EMULATOR_PID}" >/dev/null 2>&1 || echo -n "+"
    echo -n "."
    echo " done."
    SPANNER_HTTP_EMULATOR_PID=0
  fi
}
