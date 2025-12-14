#!/bin/bash

count=0
while true; do
    count=$((count + 1))
    echo "=== Execução #$count ==="

    ./rubik -r
    exit_code=$?

    if [ $exit_code -ne 0 ]; then
        echo ""
        echo "❌ FALHA detectada na execução #$count"
        echo "Exit code: $exit_code"
        break
    fi
done
