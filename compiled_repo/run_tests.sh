#!/bin/bash

echo "Attempting to compile with sanitizers..."
make re
if [ $? -ne 0 ]; then
    echo "Compilation failed. Aborting tests."
    exit 1
fi

echo "Compilation successful. Running with test maps..."
echo "--- Testing with maps/good/subject_map.cub ---"
./cub3d maps/good/subject_map.cub
# Check exit code of cub3d if needed, though sanitizers output to stderr
if [ $? -ne 0 ]; then
    echo "Warning: maps/good/subject_map.cub exited with error code $?."
fi

echo "--- Testing with maps/good/easy.cub ---"
./cub3d maps/good/easy.cub
if [ $? -ne 0 ]; then
    echo "Warning: maps/good/easy.cub exited with error code $?."
fi

echo "--- Testing with maps/good/test_map.cub ---"
./cub3d maps/good/test_map.cub
if [ $? -ne 0 ]; then
    echo "Warning: maps/good/test_map.cub exited with error code $?."
fi

echo "Test script finished. Check for sanitizer output or crashes above."
# Note: Sanitizer output (if any) goes to stderr.
# This script doesn't automatically fail based on sanitizer messages,
# it's for manual observation or integration into a more complex test harness.
# To make it stricter, one could redirect stderr to a file and grep for sanitizer messages.
# For example: ./cub3d maps/good/subject_map.cub 2> error.log
#             if grep -q "AddressSanitizer" error.log; then echo "Sanitizer error detected"; fi
# However, MLX often produces some stderr output which can be noisy.
# Games also might not auto-exit, requiring manual closure or timeout for full automation.
# For this task, manual observation of the output is the primary goal.
# Adding a small delay/prompt if games don't auto-close after an error.
# Since this is a batch script, if one map crashes, subsequent ones might not run if exit is not 0.
# The script will exit if `make re` fails. For cub3d runs, it just prints a warning.
# If cub3d crashes due to sanitizer, the script will stop there.
