#!/bin/bash

chemin_executable=$EXECUTABLES

if [ -z "$chemin_executable" ]; then
    exit 1
fi
if [ ! -f "$chemin_executable" ]; then
    exit 1
fi
if [ ! -x "$chemin_executable" ]; then
    exit 1
fi
