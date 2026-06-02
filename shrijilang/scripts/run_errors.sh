#!/bin/bash

for f in tests/errors/*; do
    echo "RUNNING: $f"
    ./sri "$f"
    echo "----------------------"
done
