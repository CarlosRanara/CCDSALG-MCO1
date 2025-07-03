# Convex Hull Using Graham's Scan Algorithm

## Project Overview

This project implements the **Graham's Scan algorithm** for computing the convex hull of a given set of 2D points. The implementation demonstrates the application of stack data structures and sorting algorithms in computational geometry.

### Key Features

- **Two sorting algorithm implementations**: Bubble Sort (O(n²)) and Merge Sort (O(n log n))
- **Stack-based convex hull construction** using Graham's Scan
- **Performance comparison** between slow and fast sorting algorithms
- **Support for large datasets** up to 32,768 points (2^15)
- **Modular programming** with separate header and source files

## Algorithm Description

**Graham's Scan** is a method for finding the convex hull of a finite set of points in the plane with time complexity O(n log n). The algorithm works by:

1. Finding the anchor point (lowest y-coordinate, then lowest x-coordinate)
2. Sorting all other points by polar angle with respect to the anchor
3. Using a stack to process points and eliminate those that create clockwise turns
4. Returning the points that form the convex hull in counterclockwise order

## Project Structure

```
├── stack.h              # Stack data structure header
├── stack.c              # Stack implementation with NEXT-TO-TOP operation
├── sort.h               # Sorting algorithms header  
├── sort.c               # Bubble Sort and Merge Sort implementations
├── graham_scan1.c       # Graham Scan with Bubble Sort (slow version)
├── graham_scan2.c       # Graham Scan with Merge Sort (fast version)
├── main1.c              # Driver program for slow version
├── main2.c              # Driver program for fast version
└── README.md            # This documentation file
```

## File Specifications

### Stack Implementation (`stack.h`, `stack.c`)
- **Operations**: CREATE, PUSH, POP, TOP, ISFULL, ISEMPTY, NEXT-TO-TOP
- **Capacity**: Maximum 32,768 elements
- **Implementation**: Array-based for efficiency

### Sorting Algorithms (`sort.h`, `sort.c`)
- **Bubble Sort**: O(n²) comparison-based sorting with early termination
- **Merge Sort**: O(n log n) divide-and-conquer iterative implementation
- **Comparison Method**: Cross product for accurate polar angle ordering

### Graham Scan (`graham_scan1.c`, `graham_scan2.c`)
- **Two versions**: One using Bubble Sort, one using Merge Sort
- **Timing measurement**: Displays execution time in milliseconds
- **Edge case handling**: Supports 0, 1, 2, or 3+ points

## Compilation Instructions

### Prerequisites
- **GCC Compiler** compatible with C99 standard
- **Operating System**: Windows, Linux, or macOS

### Compile Slow Version (Bubble Sort)
```bash
gcc -Wall -std=c99 -o main1 main1.c stack.c sort.c graham_scan1.c
```

### Compile Fast Version (Merge Sort)
```bash
gcc -Wall -std=c99 -o main2 main2.c stack.c sort.c graham_scan2.c
```

### Compilation Notes
- Use `-Wall` flag to enable all compiler warnings
- Use `-std=c99` to ensure C99 standard compliance
- All source files must be in the same directory

## Usage Instructions

### Running the Programs

**For Slow Version (Bubble Sort):**
```bash
./main1          # Linux/macOS
.\main1.exe      # Windows
```

**For Fast Version (Merge Sort):**
```bash
./main2          # Linux/macOS  
.\main2.exe      # Windows
```

### Input Format

The program will prompt for:
1. **Input filename** (e.g., `input.txt`)
2. **Output filename** (e.g., `output.txt`)

**Input file format:**
```
n
x1 y1
x2 y2
...
xn yn
```

Where:
- `n` = number of points (0 ≤ n ≤ 32,768)
- `xi yi` = coordinates of point i (double precision)

### Output Format

**Output file format:**
```
m
x1 y1
x2 y2
...
xm ym
```

Where:
- `m` = number of points in convex hull
- `xi yi` = coordinates formatted to 6 decimal places
- Points listed in counterclockwise order starting from anchor

## Sample Usage

### Example Input File (`sample-input.txt`)
```
9
 5.0    5.0
10.0    2.5
 5.0   10.0
10.0    0.0
 7.5    0.0
 5.0    0.0
 0.0    0.0
 1.0    8.0
 0.0   10.0
```

### Expected Output File (`sample-output.txt`)
```
5
 0.000000   0.000000
10.000000   0.000000
10.000000   2.500000
 5.000000  10.000000
 0.000000  10.000000
```

### Running Example
```bash
# Compile the fast version
gcc -Wall -std=c99 -o main2 main2.c stack.c sort.c graham_scan2.c

# Run the program
./main2

# Program prompts:
Enter the filename and extension of the input text file: sample-input.txt
Enter the filename and extension of the output text file: sample-output.txt

# Expected output:
Reading 9 points from input file...
Successfully read 9 points from input file.
Computing convex hull using Graham Scan with Merge Sort...
Graham Scan (Merge Sort) execution time: 0.125 milliseconds
Convex hull computation completed successfully!
Number of input points: 9
Number of hull points: 5
Results written to: sample-output.txt
```

## Performance Analysis

### Time Complexity
- **Bubble Sort Version**: O(n²) due to sorting step
- **Merge Sort Version**: O(n log n) due to efficient sorting
- **Graham Scan**: O(n) for hull construction after sorting

### Space Complexity
- **Stack storage**: O(n) for hull construction
- **Temporary arrays**: O(n) for merge sort operations
- **Input/Output**: O(n) for point storage

### Expected Performance Differences
For large datasets (n ≥ 1000), the Merge Sort version should significantly outperform the Bubble Sort version. Test with progressively larger datasets to observe the performance gap.

## Testing Recommendations

### Test Cases
Create test files with point counts following powers of 2:
- `test1.txt`: 64 points (2^6)
- `test2.txt`: 128 points (2^7)
- `test3.txt`: 256 points (2^8)
- ...
- `test10.txt`: 32,768 points (2^15)

### Performance Testing
1. Run both versions on the same input files
2. Record execution times for analysis
3. Create graphs comparing performance as n increases
4. Verify both versions produce identical output

## Troubleshooting

### Common Compilation Errors
- **"undefined reference"**: Ensure all source files are included in compilation command
- **"multiple definition"**: Check for duplicate function definitions across files
- **"cannot find file"**: Verify all source files are in the current directory

### Runtime Issues
- **"Cannot open input file"**: Check filename spelling and file existence
- **"Invalid number of points"**: Ensure input file format is correct
- **Program crashes**: Verify input file contains valid numeric data

### File Format Issues
- **Incorrect output**: Check input file format matches specification
- **Missing points**: Ensure no blank lines or extra whitespace in input file
- **Precision errors**: Verify coordinates are within reasonable ranges

## Implementation Notes

### C99 Standard Compliance
- All variables declared at beginning of functions
- Hungarian notation used for variable naming
- No use of restricted libraries (math.h, malloc/free)
- Compatible with `-Wall -std=c99` compilation flags

### Memory Management
- No dynamic memory allocation used
- Fixed-size arrays for maximum portability
- Stack-based data structures for efficiency

### Code Organization
- Modular design with separate header/source files
- Consistent naming conventions throughout
- Comprehensive error checking and validation

## Academic Use

This implementation was created for educational purposes to demonstrate:
- Stack data structure applications
- Sorting algorithm performance comparison
- Computational geometry algorithms
- Modular programming practices in C

**Note**: This code follows academic integrity guidelines and should be used as a reference for learning computational geometry concepts.

## Authors

- **Programmer**: [Your Name]
- **Tester**: [Your Name]
- **Course**: CCDSALG Term 3, AY 2024-2025
- **Project**: Convex Hull (Application of Stack Data Structure & Sorting Algorithms)