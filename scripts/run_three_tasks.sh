#!/usr/bin/env bash
set -eo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
WORKSPACE="$(cd "${SCRIPT_DIR}/.." && pwd)"
INSTALL_SETUP="${WORKSPACE}/install/setup.bash"
INSTALL_PREFIX="${WORKSPACE}/install"

MODE="${1:-udp}"
if [[ "${MODE}" == "udp" || "${MODE}" == "mqtt" ]]; then
  shift || true
else
  echo "Usage: $0 [udp|mqtt] [-- <extra ros args for udp ingest or mqtt bridge>]" >&2
  exit 1
fi

INGEST_ARGS=()
if [[ "${1:-}" == "--" ]]; then
  shift
  INGEST_ARGS=("$@")
elif [[ $# -gt 0 ]]; then
  echo "Usage: $0 [udp|mqtt] [-- <extra ros args for udp ingest or mqtt bridge>]" >&2
  exit 1
fi

if [[ -n "${ROS_DISTRO:-}" && -f "/opt/ros/${ROS_DISTRO}/setup.bash" ]]; then
  # shellcheck disable=SC1090
  source "/opt/ros/${ROS_DISTRO}/setup.bash"
elif [[ -f "/opt/ros/humble/setup.bash" ]]; then
  # shellcheck disable=SC1091
  source "/opt/ros/humble/setup.bash"
elif [[ -f "/opt/ros/jazzy/setup.bash" ]]; then
  # shellcheck disable=SC1091
  source "/opt/ros/jazzy/setup.bash"
else
  echo "Unable to find a ROS 2 setup.bash under /opt/ros. Set ROS_DISTRO or install ROS 2 first." >&2
  exit 1
fi

if [[ ! -f "${INSTALL_SETUP}" ]]; then
  echo "Workspace is not built yet. Run ./scripts/build_ros2.sh first." >&2
  exit 1
fi

UDP_BIN="${INSTALL_PREFIX}/lib/video_ingest/udp_ingest_node"
MQTT_BRIDGE_BIN="${INSTALL_PREFIX}/lib/mqtt_bridge/mqtt_bridge_node"
CUSTOM_BYTEBLOCK_BIN="${INSTALL_PREFIX}/lib/custom_byteblock/custom_byteblock_node"
DECODE_BIN="${INSTALL_PREFIX}/lib/video_decode/decoder_node"
VIEWER_BIN="${INSTALL_PREFIX}/lib/video_viewer_qt/video_viewer_qt"

# shellcheck disable=SC1091
source "${INSTALL_SETUP}"
set -u

export LD_LIBRARY_PATH="${INSTALL_PREFIX}/lib:${LD_LIBRARY_PATH:-}"
export CMAKE_PREFIX_PATH="${INSTALL_PREFIX}:${CMAKE_PREFIX_PATH:-}"
export AMENT_PREFIX_PATH="${INSTALL_PREFIX}:${AMENT_PREFIX_PATH:-}"

PIDS=()
cleanup() {
  for pid in "${PIDS[@]:-}"; do
    if kill -0 "${pid}" 2>/dev/null; then
      kill "${pid}" 2>/dev/null || true
      wait "${pid}" 2>/dev/null || true
    fi
  done
}
trap cleanup EXIT INT TERM

cd "${WORKSPACE}"
if [[ ! -x "${DECODE_BIN}" || ! -x "${VIEWER_BIN}" ]]; then
  echo "Workspace executables are incomplete. Run ./scripts/build_ros2.sh first." >&2
  exit 1
fi

if [[ "${MODE}" == "mqtt" ]]; then
  if [[ ! -x "${MQTT_BRIDGE_BIN}" || ! -x "${CUSTOM_BYTEBLOCK_BIN}" ]]; then
    echo "MQTT executables are incomplete. Run ./scripts/build_ros2.sh first." >&2
    exit 1
  fi
  "${MQTT_BRIDGE_BIN}" "${INGEST_ARGS[@]}" &
  PIDS+=("$!")
  "${CUSTOM_BYTEBLOCK_BIN}" &
  PIDS+=("$!")
else
  if [[ ! -x "${UDP_BIN}" ]]; then
    echo "UDP ingest executable not found: ${UDP_BIN}" >&2
    exit 1
  fi
  "${UDP_BIN}" "${INGEST_ARGS[@]}" &
  PIDS+=("$!")
fi

"${DECODE_BIN}" &
PIDS+=("$!")
"${VIEWER_BIN}" &
PIDS+=("$!")

wait -n "${PIDS[@]}"
