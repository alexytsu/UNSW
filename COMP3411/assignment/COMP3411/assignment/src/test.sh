#!/bin/bash

# Play my python3 program against the specified program

if [ "$#" -ne 2 ]; then
    echo "Usage: $0 <player> <port> " >&2
    exit 1
fi

./servt -p $2 & sleep 0.1
./agent.py -p $2 & sleep 0.1
./$1    -p $2