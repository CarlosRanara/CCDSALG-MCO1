#!/bin/zsh

# Increase stack size to handle large inputs
ulimit -s unlimited

# Don't exit on error so we can continue with other tests
# set -e

echo "========================================================"
echo "    Graham's Scan Performance Testing Script"
echo "    CCDSALG Term 3, AY 2024-2025"
echo "========================================================"

# Check executables
if [ ! -f main1 ]; then
    echo "[ERROR] main1 not found - compile first!"
    read -p "Press Enter to continue..."
    exit 1
fi

if [ ! -f main2 ]; then
    echo "[ERROR] main2 not found - compile first!"
    read -p "Press Enter to continue..."
    exit 1
fi

# Check if executables are actually executable
if [ ! -x main1 ]; then
    echo "[WARNING] main1 is not executable. Making it executable..."
    chmod +x main1
fi

if [ ! -x main2 ]; then
    echo "[WARNING] main2 is not executable. Making it executable..."
    chmod +x main2
fi

echo "[SUCCESS] Both executables found"

# Create results folder
mkdir -p results

echo "[INFO] Starting automated testing..."
echo

# Function to run a test
run_test() {
    local test_num=$1
    local input_file=$2
    local point_count=$3
    
    if [ -f "$input_file" ]; then
        echo "=== TEST $test_num: $(basename $input_file) ($point_count points) ==="
        
        # Run slow version with timeout
        if timeout 60 bash -c "echo -e '$input_file\nresults/OUTPUT${test_num}-slow.txt' | ./main1" > results/OUTPUT-log${test_num}-slow.txt 2>&1; then
            echo "SLOW: "
            grep "Bubble Sort.*execution time" results/OUTPUT-log${test_num}-slow.txt || echo "No timing data found in slow version"
        else
            echo "SLOW: [ERROR] main1 execution failed or timed out"
            echo "Check results/OUTPUT-log${test_num}-slow.txt for details"
        fi
        
        # Run fast version with timeout
        if timeout 60 bash -c "echo -e '$input_file\nresults/OUTPUT${test_num}-fast.txt' | ./main2" > results/OUTPUT-log${test_num}-fast.txt 2>&1; then
            echo "FAST:"
            grep "Merge Sort.*execution time" results/OUTPUT-log${test_num}-fast.txt || echo "No timing data found in fast version"
        else
            echo "FAST: [ERROR] main2 execution failed or timed out"
            echo "Check results/OUTPUT-log${test_num}-fast.txt for details"
        fi
        
        echo
    else
        echo "Skipping TEST $test_num: $input_file not found"
    fi
}

# Test 1: 2^6 = 64 points
if [ -f "data/input2^6.txt" ]; then
    echo "=== TEST 1: input2^6.txt (64 points) ==="
    echo -e "data/input2^6.txt\nresults/OUTPUT1-slow.txt" | ./main1 > results/OUTPUT-log1-slow.txt 2>&1
    echo -e "data/input2^6.txt\nresults/OUTPUT1-fast.txt" | ./main2 > results/OUTPUT-log1-fast.txt 2>&1
    
    echo "SLOW: "
    grep "Bubble Sort.*execution time" results/OUTPUT-log1-slow.txt || echo "No timing data found"
    echo "FAST:"
    grep "Merge Sort.*execution time" results/OUTPUT-log1-fast.txt || echo "No timing data found"
    echo
else
    echo "Skipping TEST 1: data/input2^6.txt not found"
fi

# Test 2: 2^7 = 128 points
if [ -f "data/input2^7.txt" ]; then
    echo "=== TEST 2: input2^7.txt (128 points) ==="
    echo -e "data/input2^7.txt\nresults/OUTPUT2-slow.txt" | ./main1 > results/OUTPUT-log2-slow.txt
    echo -e "data/input2^7.txt\nresults/OUTPUT2-fast.txt" | ./main2 > results/OUTPUT-log2-fast.txt
    
    echo "SLOW: "
    grep "Bubble Sort.*execution time" results/OUTPUT-log2-slow.txt
    echo "FAST:"
    grep "Merge Sort.*execution time" results/OUTPUT-log2-fast.txt
    echo
fi

# Test 3: 2^8 = 256 points
if [ -f "data/input2^8.txt" ]; then
    echo "=== TEST 3: input2^8.txt (256 points) ==="
    echo -e "data/input2^8.txt\nresults/OUTPUT3-slow.txt" | ./main1 > results/OUTPUT-log3-slow.txt
    echo -e "data/input2^8.txt\nresults/OUTPUT3-fast.txt" | ./main2 > results/OUTPUT-log3-fast.txt
    
    echo "SLOW: "
    grep "Bubble Sort.*execution time" results/OUTPUT-log3-slow.txt
    echo "FAST:"
    grep "Merge Sort.*execution time" results/OUTPUT-log3-fast.txt
    echo
fi

# Test 4: 2^9 = 512 points
if [ -f "data/input2^9.txt" ]; then
    echo "=== TEST 4: input2^9.txt (512 points) ==="
    echo -e "data/input2^9.txt\nresults/OUTPUT4-slow.txt" | ./main1 > results/OUTPUT-log4-slow.txt
    echo -e "data/input2^9.txt\nresults/OUTPUT4-fast.txt" | ./main2 > results/OUTPUT-log4-fast.txt
    
    echo "SLOW: "
    grep "Bubble Sort.*execution time" results/OUTPUT-log4-slow.txt
    echo "FAST:"
    grep "Merge Sort.*execution time" results/OUTPUT-log4-fast.txt
    echo
fi

# Test 5: 2^10 = 1024 points
if [ -f "data/input2^10.txt" ]; then
    echo "=== TEST 5: input2^10.txt (1024 points) ==="
    echo -e "data/input2^10.txt\nresults/OUTPUT5-slow.txt" | ./main1 > results/OUTPUT-log5-slow.txt
    echo -e "data/input2^10.txt\nresults/OUTPUT5-fast.txt" | ./main2 > results/OUTPUT-log5-fast.txt
    
    echo "SLOW: "
    grep "Bubble Sort.*execution time" results/OUTPUT-log5-slow.txt
    echo "FAST:"
    grep "Merge Sort.*execution time" results/OUTPUT-log5-fast.txt
    echo
fi

# Test 6: 2^11 = 2048 points
if [ -f "data/input2^11.txt" ]; then
    echo "=== TEST 6: input2^11.txt (2048 points) ==="
    echo -e "data/input2^11.txt\nresults/OUTPUT6-slow.txt" | ./main1 > results/OUTPUT-log6-slow.txt
    echo -e "data/input2^11.txt\nresults/OUTPUT6-fast.txt" | ./main2 > results/OUTPUT-log6-fast.txt
    
    echo "SLOW: "
    grep "Bubble Sort.*execution time" results/OUTPUT-log6-slow.txt
    echo "FAST:"
    grep "Merge Sort.*execution time" results/OUTPUT-log6-fast.txt
    echo
fi

# Test 7: 2^12 = 4096 points
if [ -f "data/input2^12.txt" ]; then
    echo "=== TEST 7: input2^12.txt (4096 points) ==="
    echo -e "data/input2^12.txt\nresults/OUTPUT7-slow.txt" | ./main1 > results/OUTPUT-log7-slow.txt
    echo -e "data/input2^12.txt\nresults/OUTPUT7-fast.txt" | ./main2 > results/OUTPUT-log7-fast.txt
    
    echo "SLOW: "
    grep "Bubble Sort.*execution time" results/OUTPUT-log7-slow.txt
    echo "FAST:"
    grep "Merge Sort.*execution time" results/OUTPUT-log7-fast.txt
    echo
fi

# Test 8: 2^13 = 8192 points
if [ -f "data/input2^13.txt" ]; then
    echo "=== TEST 8: input2^13.txt (8192 points) ==="
    echo -e "data/input2^13.txt\nresults/OUTPUT8-slow.txt" | ./main1 > results/OUTPUT-log8-slow.txt
    echo -e "data/input2^13.txt\nresults/OUTPUT8-fast.txt" | ./main2 > results/OUTPUT-log8-fast.txt
    
    echo "SLOW: "
    grep "Bubble Sort.*execution time" results/OUTPUT-log8-slow.txt
    echo "FAST:"
    grep "Merge Sort.*execution time" results/OUTPUT-log8-fast.txt
    echo
fi

# Test 9: 2^14 = 16384 points
if [ -f "data/input2^14.txt" ]; then
    echo "=== TEST 9: input2^14.txt (16384 points) ==="
    echo -e "data/input2^14.txt\nresults/OUTPUT9-slow.txt" | ./main1 > results/OUTPUT-log9-slow.txt
    echo -e "data/input2^14.txt\nresults/OUTPUT9-fast.txt" | ./main2 > results/OUTPUT-log9-fast.txt
    
    echo "SLOW: "
    grep "Bubble Sort.*execution time" results/OUTPUT-log9-slow.txt
    echo "FAST:"
    grep "Merge Sort.*execution time" results/OUTPUT-log9-fast.txt
    echo
fi

# Test 10: 2^15 = 32768 points
if [ -f "data/input2^15.txt" ]; then
    echo "=== TEST 10: input2^15.txt (32768 points) ==="
    echo -e "data/input2^15.txt\nresults/OUTPUT10-slow.txt" | ./main1 > results/OUTPUT-log10-slow.txt
    echo -e "data/input2^15.txt\nresults/OUTPUT10-fast.txt" | ./main2 > results/OUTPUT-log10-fast.txt
    
    echo "SLOW: "
    grep "Bubble Sort.*execution time" results/OUTPUT-log10-slow.txt
    echo "FAST:"
    grep "Merge Sort.*execution time" results/OUTPUT-log10-fast.txt
    echo
fi

echo "========================================================"
echo "ALL TESTS COMPLETED!"
echo "========================================================"
echo
echo "The timing data shown above is what you need for your table."
echo "Log files are saved in results/ folder for reference."
echo

# Open results folder (works on both macOS and Linux)
if command -v open > /dev/null 2>&1; then
    open results  # macOS
elif command -v xdg-open > /dev/null 2>&1; then
    xdg-open results  # Linux
else
    echo "Results folder: $(pwd)/results"
fi

read -p "Press Enter to continue..."
