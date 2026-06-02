#!/bin/bash

for f in tests/runtime/*; do
    echo "RUNNING: $f"
    ./sri "$f"
    echo "----------------------"
done
