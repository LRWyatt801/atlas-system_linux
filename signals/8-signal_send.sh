#!/bin/bash

# Check if pid was provided
if [ $# -eq 0 ]; then
    echo "Usage: $0 <pid>"
    exit 1
fi

PID=$1

kill -s QUIT $PID