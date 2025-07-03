# Graham's Scan Convex Hull Project
## CCDSALG Term 3, AY 2024-2025

A high-performance implementation of Graham's Scan algorithm for computing convex hulls with comprehensive performance analysis.

## Project Overview

This project implements Graham's Scan algorithm to find the convex hull of 2D point sets. Features two algorithm variants to demonstrate the impact of sorting efficiency:

- **Slow Version**: Bubble Sort implementation (O(n²))
- **Fast Version**: Merge Sort implementation (O(n log n))

**Group 16 Assignment**: Bubble Sort + Merge Sort

## Project Structure

```
Graham-Scan-Algorithm/
├── include/                 # Header files
│   ├── graham_scan.h       # Algorithm interface
│   ├── sort.h              # Sorting functions
│   └── stack.h             # Stack data structure
├── src/                    # Source files
│   ├── graham_scan1.c      # Slow version (Bubble Sort)
│   ├── graham_scan2.c      # Fast version (Merge Sort)
│   ├── main1.c            # Slow version driver
│   ├── main2.c            # Fast version driver
│   ├── sort.c             # Sorting implementations
│   └── stack.c            # Stack implementation
├── specs/                  # Project documentation
├── INPUT*.TXT             # Test cases (64 to 32,768 points)
├── bigtest.sh            # Automated testing script
├── generate_inputs.py    # Test data generator
└── Makefile              # Build system
```

## Quick Start

### Build
```bash
make
```

### Test
```bash
./bigtest.sh
```

### Run
```bash
./graham_slow    # Bubble sort version
./graham_fast    # Merge sort version
```

## Compilation

### One-Step (Recommended)
```bash
# Slow version
gcc -Wall -std=c99 -Iinclude src/stack.c src/sort.c src/graham_scan1.c src/main1.c -o graham_slow -lm

# Fast version
gcc -Wall -std=c99 -Iinclude src/stack.c src/sort.c src/graham_scan2.c src/main2.c -o graham_fast -lm
```

### Using Makefile
```bash
make all          # Build both versions
make graham_slow  # Build slow version only
make graham_fast  # Build fast version only
make clean        # Clean build files
```

## Usage

### Interactive Mode
```bash
./graham_slow
# Enter input filename: INPUT1.TXT
# Enter output filename: OUTPUT1_SLOW.TXT
```

### Automated Testing
```bash
# Full performance test suite
./bigtest.sh --full

# Quick test (first 3 cases)
./bigtest.sh --quick

# Check prerequisites
./bigtest.sh --check
```

## Performance Results

Comprehensive testing with input sizes from 64 to 32,768 points:

| Points | Bubble Sort | Merge Sort | Speedup |
|--------|-------------|------------|---------|
| 64     | 0.23ms     | 0.08ms     | 2.9x    |
| 128    | 0.89ms     | 0.15ms     | 5.9x    |
| 256    | 3.42ms     | 0.28ms     | 12.2x   |
| 1024   | 52.1ms     | 0.93ms     | 56.0x   |
| 4096   | 832ms      | 3.4ms      | 245x    |
| 16384  | 13.2s      | 12.9ms     | 1023x   |
| 32768  | 52.8s      | 25.3ms     | 2087x   |

## Key Features

- **Modular Architecture**: Clean separation of concerns
- **Robust Error Handling**: Comprehensive input validation  
- **Edge Case Support**: Handles 1-3 points, collinear points, duplicates
- **Performance Monitoring**: Built-in timing measurements
- **Automated Testing**: Complete test suite with validation
- **Memory Efficient**: Static allocation, no memory leaks
- **Standards Compliant**: C99 standard adherence

## Implementation Details

### Stack Data Structure
- Array-based implementation
- Capacity: 32,768 elements (2^15)
- Special NEXT-TO-TOP operation for Graham's Scan
- Operations: CREATE, PUSH, POP, TOP, NEXT-TO-TOP, ISFULL, ISEMPTY

### Sorting Algorithms
- **Bubble Sort**: Simple O(n²) implementation for comparison
- **Merge Sort**: Efficient O(n log n) divide-and-conquer approach
- **Comparison Criteria**: Polar angle relative to anchor point
- **Tie Breaking**: Distance from anchor for collinear points

### Graham's Scan Process
1. Find anchor point (lowest y-coordinate, leftmost if tied)
2. Sort remaining points by polar angle around anchor
3. Use stack to maintain counterclockwise hull traversal
4. Remove points creating clockwise turns
5. Output hull points in counterclockwise order

## File Formats

### Input Format
```
n
x1 y1
x2 y2
...
xn yn
```

### Output Format
```
m
x1 y1
x2 y2
...
xm ym
```
- Coordinates formatted to 6 decimal places
- Points listed in counterclockwise order

## Testing

### Test Cases
- INPUT1.TXT through INPUT10.TXT
- Sizes: 64, 128, 256, 512, 1024, 2048, 4096, 8192, 16384, 32768 points
- Various geometric patterns: circles, random distributions, structured layouts

### Validation
- Output consistency verification between versions
- Edge case testing (collinear points, duplicates, small inputs)
- Performance regression testing
- Memory usage validation

## Requirements

- GCC compiler with C99 support
- Math library (`-lm`)
- Make utility (optional)
- Python3 (for test generation)

## Academic Compliance

Original implementation developed from scratch following MCO1 specifications. No code copying from external sources. Implements required Group 16 algorithms (Bubble Sort + Merge Sort) with comprehensive documentation and testing.

---

**Note**: This implementation demonstrates the practical impact of algorithm choice on computational geometry performance, specifically how sorting efficiency affects overall Graham's Scan execution time.
