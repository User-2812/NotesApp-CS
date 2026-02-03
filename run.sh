#!/usr/bin/env bash
set -e
cd "$(dirname "$0")"

unset SESSION_MANAGER || true
export LD_LIBRARY_PATH=/home/user-2812/STEMgraph/cpplibs/cs1.9_libs/lib:$LD_LIBRARY_PATH
export CS_PLUGIN_PATH="$PWD/copperspice/deploy"

exec ./build/NotesApp
