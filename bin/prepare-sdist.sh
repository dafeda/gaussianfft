#!/usr/bin/env bash
set -euo pipefail

readonly ROOT_DIR="$(cd "$(dirname -- "$0")/.." >/dev/null; pwd -P)"
readonly PYTHON=${PYTHON:-python3}

# Remove all, but the oldest supported version of boost
# add that version to a file, which is read by `find_boost_version.py`

readonly boost_version="$("$PYTHON" "$ROOT_DIR/bin/find_boost_version.py" --sdist)"

shopt -s extglob
cd "$ROOT_DIR/sources/boost"
rm -rf !("$boost_version")
cd - >/dev/null

echo "$boost_version" > "$ROOT_DIR/USE_BOOST_VERSION.txt"