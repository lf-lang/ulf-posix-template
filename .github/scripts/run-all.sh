#!/usr/bin/env bash
set -e

build_and_run_test() {
  local program=$1
  echo "========================================="
  echo "Building and running $program"
  echo "========================================="
  cmake -Bbuild \
    -DLF_MAIN="$program"
  cmake --build build -j "$(nproc)"
  ./build/"$program"
  rm -rf build src-gen
}

# Automatically discover all micro-LF examples in src directory
EXAMPLES=()
for lf_file in src/*.ulf; do
  if [ -f "$lf_file" ]; then
    # Extract filename without path and extension
    example=$(basename "$lf_file" .ulf)
    EXAMPLES+=("$example")
  fi
done

echo "Found examples: " "${EXAMPLES[@]}"

for example in "${EXAMPLES[@]}"; do
  build_and_run_test "$example"
done

echo ""
echo "========================================"
echo "All tests completed successfully!"
echo "========================================"
