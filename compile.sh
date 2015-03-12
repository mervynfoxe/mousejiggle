#!/bin/bash
SRC_DIR="src"
BIN_DIR="bin"

if [[ ! -d "${SRC_DIR}" ]]; then
    echo "Error: Source directory does not exist"
    exit 1
fi

if [[ ! -d "${BIN_DIR}" ]]; then
    echo "Creating directory ${BIN_DIR}/"
    mkdir "${BIN_DIR}"
fi

gcc -o "${BIN_DIR}/mousejiggle.x86_64" "${SRC_DIR}/mousejiggle.c" -lX11
