#!/usr/bin/env bash
set -eo pipefail

SCRIPT_DIR="$(cd "$(dirname "${BASH_SOURCE[0]}")" && pwd)"
WORKSPACE="$(cd "${SCRIPT_DIR}/.." && pwd)"

if [[ -n "${ROS_DISTRO:-}" && -f "/opt/ros/${ROS_DISTRO}/setup.bash" ]]; then
  # Reuse the caller's chosen ROS distribution when available.
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

set -u

cd "${WORKSPACE}"
colcon build --merge-install --cmake-args -DCMAKE_BUILD_TYPE=Release
