#!/bin/bash

echo "========================================================"
echo "    Graham's Scan Performance Testing Script"
echo "    CCDSALG Term 3, AY 2024-2025"
echo "========================================================"

# Check executables
if [ ! -f "main1" ]; then
    echo "[ERROR] main1 not found - compile first!"
    read -p "Press any key to continue..."
    exit 1
fi

if [ ! -f "main2" ]; then
    echo "[ERROR] main2 not found - compile first!"
    read -p "Press any key to continue..."
    exit 1
fi

echo "[SUCCESS] Both executables found"

# Create results folder
mkdir -p results

echo "[INFO] Starting automated testing..."
echo

# Function to run a test
run_test() {
    local test_num=$1
    local input_file="INPUT${test_num}.TXT"
    
    if [ -f "$input_file" ]; then
        echo "=== TEST $test_num: $input_file ==="
        
        # Create input for slow version
        echo "$input_file" > input.tmp
        echo "results/slow${test_num}.txt" >> input.tmp
        ./main1 < input.tmp > "results/log${test_num}_slow.txt"
        
        # Create input for fast version
        echo "$input_file" > input.tmp
        echo "results/fast${test_num}.txt" >> input.tmp
        ./main2 < input.tmp > "results/log${test_num}_fast.txt"
        
        # Display results
        echo "SLOW: "
        grep -E "Bubble Sort.*execution time" "results/log${test_num}_slow.txt" || echo "No timing data found"
        echo "FAST:"
        grep -E "Merge Sort.*execution time" "results/log${test_num}_fast.txt" || echo "No timing data found"
        echo
    fi
}

# Run all tests
for i in {1..10}; do
    run_test $i
done

# Clean up
rm -f input.tmp

echo "========================================================"
echo "ALL TESTS COMPLETED!"
echo "========================================================"
echo
echo "The timing data shown above is what you need for your table."
echo "Log files are saved in results/ folder for reference."
echo

# Open results folder (macOS)
open results

echo "Press any key to continue..."
read -n 1