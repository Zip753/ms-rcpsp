#!/bin/bash

BINARY_NAME='ga_bin'
LIBRARY_NAME='ga_lib'

bazel build -c opt ":${LIBRARY_NAME}"

package_dir=$(mktemp -d)
mkdir "$package_dir/lib" "$package_dir/bin"
cp "bazel-bin/$BINARY_NAME" "$package_dir/bin/"
cp "bazel-bin/lib${LIBRARY_NAME}.a" "$package_dir/lib/"
cp -R "include/" "$package_dir/"

tar -czvf 'ms-rcpsp.tar.gz' -C $package_dir bin lib include
