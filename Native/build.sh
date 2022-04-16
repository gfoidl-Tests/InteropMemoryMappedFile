#!/usr/bin/env bash

config=${1:-Debug}

mkdir -p out/$config
cd $_

cmake ../..
cmake --build . --config $config

cd - > /dev/null
