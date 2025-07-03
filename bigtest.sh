#!/bin/bash

# bigtest.sh
# Automated Performance Testing Script for Graham's Scan Project
# CCDSALG Term 3, AY 2024-2025

# Colors for output
RED='\033[0;31m'
GREEN='\033[0;32m'
YELLOW='\033[1;33m'
BLUE='\033[0;34m'
NC='\033[0m' # No Color

# Configuration
SLOW_EXE="./graham_slow"
FAST_EXE="./graham_fast"
RESULTS_DIR="results"
SUMMARY_FILE="$RESULTS_DIR/performance_summary.csv"

# Function to print colored output
print_status() {
    echo -e "${BLUE}[INFO]${NC} $1"
}

print_success() {
    echo -e "${GREEN}[SUCCESS]${NC} $1"
}

print_warning() {
    echo -e "${YELLOW}[WARNING]${NC} $1"
}

print_error() {
    echo -e "${RED}[ERROR]${NC} $1"
}

# Function to check if executables exist
check_executables() {
    print_status "Checking for executable files..."
    
    if [[ ! -f "$SLOW_EXE" ]]; then
        print_error "Slow version executable not found: $SLOW_EXE"
        print_status "Run 'make graham_slow' or 'make all' first"
        exit 1
    fi
    
    if [[ ! -f "$FAST_EXE" ]]; then
        print_error "Fast version executable not found: $FAST_EXE"
        print_status "Run 'make graham_fast' or 'make all' first"
        exit 1
    fi
    
    print_success "Both executables found"
}

# Function to check INPUT files
check_input_files() {
    print_status "Checking for INPUT files..."
    
    local found_files=0
    for i in {1..10}; do
        if [[ -f "INPUT${i}.TXT" ]]; then
            local size=$(head -1 "INPUT${i}.TXT")
            print_success "INPUT${i}.TXT found (${size} points)"
            ((found_files++))
        else
            print_warning "INPUT${i}.TXT not found"
        fi
    done
    
    if [[ $found_files -eq 0 ]]; then
        print_error "No INPUT files found!"
        print_status "Run 'python3 generate_inputs.py' to create test files"
        exit 1
    fi
    
    print_success "Found $found_files INPUT files"
}

# Function to run a single test case
run_test_case() {
    local case_num=$1
    local input_file="INPUT${case_num}.TXT"
    
    if [[ ! -f "$input_file" ]]; then
        print_warning "Skipping test case $case_num - $input_file not found"
        return 1
    fi
    
    echo
    print_status "=== Running Test Case $case_num ==="
    
    local input_size=$(head -1 "$input_file")
    print_status "Input size: $input_size points"
    
    # Run slow version
    print_status "Running slow version (Bubble Sort)..."
    echo -e "$input_file\n$RESULTS_DIR/OUTPUT${case_num}_SLOW.TXT" | $SLOW_EXE > "$RESULTS_DIR/slow_${case_num}.log" 2>&1
    
    if [[ $? -ne 0 ]]; then
        print_error "Slow version failed for test case $case_num"
        cat "$RESULTS_DIR/slow_${case_num}.log"
        return 1
    fi
    
    # Extract timing for slow version
    local slow_time=$(grep "execution time" "$RESULTS_DIR/slow_${case_num}.log" | grep -o '[0-9]*\.[0-9]*' | head -1)
    if [[ -z "$slow_time" ]]; then
        slow_time="N/A"
        print_warning "Could not extract timing from slow version"
    else
        print_success "Slow version completed in ${slow_time} ms"
    fi
    
    # Run fast version
    print_status "Running fast version (Merge Sort)..."
    echo -e "$input_file\n$RESULTS_DIR/OUTPUT${case_num}_FAST.TXT" | $FAST_EXE > "$RESULTS_DIR/fast_${case_num}.log" 2>&1
    
    if [[ $? -ne 0 ]]; then
        print_error "Fast version failed for test case $case_num"
        cat "$RESULTS_DIR/fast_${case_num}.log"
        return 1
    fi
    
    # Extract timing for fast version
    local fast_time=$(grep "execution time" "$RESULTS_DIR/fast_${case_num}.log" | grep -o '[0-9]*\.[0-9]*' | head -1)
    if [[ -z "$fast_time" ]]; then
        fast_time="N/A"
        print_warning "Could not extract timing from fast version"
    else
        print_success "Fast version completed in ${fast_time} ms"
    fi
    
    # Compare outputs
    print_status "Comparing outputs..."
    if diff "$RESULTS_DIR/OUTPUT${case_num}_SLOW.TXT" "$RESULTS_DIR/OUTPUT${case_num}_FAST.TXT" > /dev/null 2>&1; then
        print_success "Outputs are identical"
    else
        print_error "Outputs differ!"
        print_status "Check files: OUTPUT${case_num}_SLOW.TXT vs OUTPUT${case_num}_FAST.TXT"
    fi
    
    # Calculate speedup
    local speedup="N/A"
    if [[ "$slow_time" != "N/A" && "$fast_time" != "N/A" && "$fast_time" != "0" ]]; then
        speedup=$(echo "scale=2; $slow_time / $fast_time" | bc -l 2>/dev/null || echo "N/A")
    fi
    
    # Add to CSV
    echo "$case_num,$input_size,$slow_time,$fast_time,OUTPUT${case_num}_SLOW.TXT,OUTPUT${case_num}_FAST.TXT,$speedup" >> "$SUMMARY_FILE"
    
    print_success "Test case $case_num complete"
    if [[ "$speedup" != "N/A" ]]; then
        print_status "Speedup: ${speedup}x faster"
    fi
    
    return 0
}

# Function to generate summary report
generate_report() {
    print_status "Generating summary report..."
    
    if [[ ! -f "$SUMMARY_FILE" ]]; then
        print_error "No summary file found"
        return 1
    fi
    
    echo
    echo "=============================================="
    echo "           PERFORMANCE SUMMARY"
    echo "=============================================="
    echo
    
    # Print CSV header for readability
    printf "%-4s %-10s %-12s %-12s %-8s\n" "Case" "Input Size" "Slow (ms)" "Fast (ms)" "Speedup"
    printf "%-4s %-10s %-12s %-12s %-8s\n" "----" "----------" "--------" "--------" "--------"
    
    # Parse and display results
    tail -n +2 "$SUMMARY_FILE" | while IFS=',' read -r case size slow fast output_slow output_fast speedup; do
        printf "%-4s %-10s %-12s %-12s %-8s\n" "$case" "$size" "$slow" "$fast" "$speedup"
    done
    
    echo
    echo "Detailed results saved in: $RESULTS_DIR/"
    echo "CSV data for documentation: $SUMMARY_FILE"
    echo
}

# Function to show file locations
show_results() {
    print_status "Results saved in $RESULTS_DIR/ directory:"
    echo "  📊 performance_summary.csv - Timing comparison table"
    echo "  📄 OUTPUT*_SLOW.TXT - Slow version outputs"
    echo "  📄 OUTPUT*_FAST.TXT - Fast version outputs"
    echo "  📝 slow_*.log - Slow version execution logs"
    echo "  📝 fast_*.log - Fast version execution logs"
    echo
}

# Function to run quick test (first 3 cases)
run_quick_test() {
    print_status "=== QUICK TEST MODE ==="
    print_status "Running first 3 test cases only..."
    
    mkdir -p "$RESULTS_DIR"
    echo "Test Case,Input Size,Slow Time (ms),Fast Time (ms),Slow Output File,Fast Output File,Speedup" > "$SUMMARY_FILE"
    
    local success_count=0
    for i in {1..3}; do
        if run_test_case $i; then
            ((success_count++))
        fi
    done
    
    echo
    print_status "Quick test completed: $success_count/3 test cases passed"
    generate_report
    show_results
}

# Function to run all tests
run_full_test() {
    print_status "=== BIG TEST: Automated Performance Testing ==="
    print_status "Running all available test cases..."
    
    mkdir -p "$RESULTS_DIR"
    echo "Test Case,Input Size,Slow Time (ms),Fast Time (ms),Slow Output File,Fast Output File,Speedup" > "$SUMMARY_FILE"
    
    local success_count=0
    local total_cases=0
    
    for i in {1..10}; do
        if [[ -f "INPUT${i}.TXT" ]]; then
            ((total_cases++))
            if run_test_case $i; then
                ((success_count++))
            fi
        fi
    done
    
    echo
    echo "=============================================="
    print_status "BIG TEST COMPLETE!"
    print_status "Completed: $success_count/$total_cases test cases"
    echo "=============================================="
    
    generate_report
    show_results
    
    print_status "Use the CSV data in your documentation table and graphs!"
}

# Function to show usage
show_usage() {
    echo "Usage: $0 [OPTIONS]"
    echo
    echo "OPTIONS:"
    echo "  -q, --quick     Run quick test (first 3 test cases only)"
    echo "  -f, --full      Run full test (all available test cases)"
    echo "  -c, --check     Check prerequisites (executables and input files)"
    echo "  -h, --help      Show this help message"
    echo
    echo "Examples:"
    echo "  $0 --check     # Check if everything is ready"
    echo "  $0 --quick     # Quick test for development"
    echo "  $0 --full      # Full performance testing"
    echo "  $0             # Same as --full"
    echo
}

# Main script logic
main() {
    echo "🔬 Graham's Scan Performance Testing Script"
    echo "   CCDSALG Term 3, AY 2024-2025"
    echo
    
    # Parse command line arguments
    case "${1:-}" in
        -h|--help)
            show_usage
            exit 0
            ;;
        -c|--check)
            check_executables
            check_input_files
            print_success "All prerequisites satisfied!"
            exit 0
            ;;
        -q|--quick)
            check_executables
            check_input_files
            run_quick_test
            ;;
        -f|--full|"")
            check_executables
            check_input_files
            run_full_test
            ;;
        *)
            print_error "Unknown option: $1"
            show_usage
            exit 1
            ;;
    esac
}

# Run main function with all arguments
main "$@"
