# Graham's Scan Convex Hull Project
## CCDSALG/GDDASGO Term 1, AY 2024-2025

### Project Overview
This project implements the Graham's Scan algorithm to compute the convex hull of a set of 2D points. The implementation includes two versions: a "slow" version using Bubble Sort and a "fast" version using Quick Sort to demonstrate the impact of algorithm efficiency on performance.

### Project Structure
```
Graham's Scan Project/
│
├── Source Files
│   ├── stack.h              # Stack data structure header
│   ├── stack.c              # Stack data structure implementation
│   ├── sort.h               # Sorting algorithms header
│   ├── sort.c               # Sorting algorithms implementation
│   ├── graham_scan.h        # Graham's Scan algorithm header
│   ├── graham_scan1.c       # Graham's Scan with Bubble Sort (slow)
│   ├── graham_scan2.c       # Graham's Scan with Quick Sort (fast)
│   ├── main1.c              # Driver program for slow version
│   └── main2.c              # Driver program for fast version
│
├── Test Files
│   ├── INPUT1.TXT           # Test case 1 (2^6 = 64 points)
│   ├── INPUT2.TXT           # Test case 2 (2^8 = 256 points)
│   ├── INPUT3.TXT           # Test case 3 (2^10 = 1024 points)
│   ├── INPUT4.TXT           # Test case 4 (2^12 = 4096 points)
│   ├── INPUT5.TXT           # Test case 5 (2^15 = 32768 points)
│   ├── OUTPUT1.TXT          # Output for test case 1
│   ├── OUTPUT2.TXT          # Output for test case 2
│   ├── OUTPUT3.TXT          # Output for test case 3
│   ├── OUTPUT4.TXT          # Output for test case 4
│   └── OUTPUT5.TXT          # Output for test case 5
│
└── Documentation
    └── GROUPNUMBER.PDF      # Project documentation
```

## Compilation Instructions

### Prerequisites
- GCC compiler with C99 standard support
- Make sure you have `time.h` library available for timing functions

### Compilation Commands

**Compile Slow Version (Bubble Sort):**
```bash
gcc -Wall -std=c99 stack.c sort.c graham_scan1.c main1.c -o graham_slow -lm
```

**Compile Fast Version (Quick Sort):**
```bash
gcc -Wall -std=c99 stack.c sort.c graham_scan2.c main2.c -o graham_fast -lm
```

### Alternative: Using Makefile
Create a Makefile with the following content:
```makefile
CC = gcc
CFLAGS = -Wall -std=c99
LDFLAGS = -lm

all: graham_slow graham_fast

graham_slow: stack.o sort.o graham_scan1.o main1.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

graham_fast: stack.o sort.o graham_scan2.o main2.o
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

%.o: %.c
	$(CC) $(CFLAGS) -c $<

clean:
	rm -f *.o graham_slow graham_fast
```

Then compile with:
```bash
make
```

## Running the Programs

### Slow Version
```bash
./graham_slow
```

### Fast Version
```bash
./graham_fast
```

### Input Format
When prompted, enter:
1. Input filename (e.g., `INPUT1.TXT`)
2. Output filename (e.g., `OUTPUT1.TXT`)

## File Formats

### Input File Format
```
n
x1 y1
x2 y2
...
xn yn
```
Where:
- `n` is the number of points
- Each subsequent line contains x and y coordinates (double precision)

### Output File Format
```
m
x1 y1
x2 y2
...
xm ym
```
Where:
- `m` is the number of points in the convex hull
- Coordinates are formatted with 6 decimal places
- Points are listed in counterclockwise order starting with the anchor point

## Implementation Details

### Stack Data Structure
- **Implementation**: Array-based stack
- **Capacity**: Up to 32,768 elements (2^15)
- **Operations**: CREATE, PUSH, POP, TOP, NEXT-TO-TOP, ISFULL, ISEMPTY
- **Special Feature**: NEXT-TO-TOP operation for Graham's Scan algorithm

### Sorting Algorithms
- **Slow Algorithm**: Bubble Sort (O(n²) complexity)
- **Fast Algorithm**: Quick Sort (O(n log n) complexity)
- **Sorting Criteria**: Polar angle with respect to anchor point
- **Tie-breaking**: Distance from anchor point for collinear points

### Graham's Scan Algorithm
1. Find anchor point (lowest y-coordinate, leftmost if tie)
2. Sort remaining points by polar angle around anchor
3. Process points using stack to maintain counterclockwise turns
4. Remove points that create clockwise turns
5. Output convex hull points in counterclockwise order

## Performance Testing

The project includes timing measurements to compare the performance of slow vs. fast versions:

- **Bubble Sort Version**: Expected O(n²) performance
- **Quick Sort Version**: Expected O(n log n) performance
- **Test Cases**: 5 different input sizes from 64 to 32,768 points
- **Timing**: Measured in milliseconds using clock() function

## Key Features

✅ **Modular Design**: Separate files for different components  
✅ **Error Handling**: Comprehensive error checking and reporting  
✅ **Memory Efficient**: No dynamic memory allocation  
✅ **Standards Compliant**: Follows C99 standard  
✅ **Performance Analysis**: Built-in timing for algorithm comparison  
✅ **Robust Testing**: Handles edge cases and large datasets  

## Sample Usage

```bash
# Compile both versions
gcc -Wall -std=c99 stack.c sort.c graham_scan1.c main1.c -o graham_slow -lm
gcc -Wall -std=c99 stack.c sort.c graham_scan2.c main2.c -o graham_fast -lm

# Run slow version
./graham_slow
Enter input filename (including extension): INPUT1.TXT
Enter output filename (including extension): OUTPUT1_SLOW.TXT
Graham's Scan (Bubble Sort) execution time: 1.23 milliseconds
Convex hull computation complete. Results written to OUTPUT1_SLOW.TXT

# Run fast version
./graham_fast
Enter input filename (including extension): INPUT1.TXT
Enter output filename (including extension): OUTPUT1_FAST.TXT
Graham's Scan (Quick Sort) execution time: 0.45 milliseconds
Convex hull computation complete. Results written to OUTPUT1_FAST.TXT
```

## Expected Performance Results

For large datasets (32,768 points), expect:
- **Slow Version**: Several seconds to minutes
- **Fast Version**: Milliseconds to seconds
- **Performance Ratio**: Fast version typically 10-100x faster for large inputs

## Troubleshooting

### Common Issues

1. **Compilation Errors**
   - Ensure all source files are in the same directory
   - Check that GCC supports C99 standard
   - Verify the `-lm` flag is included for math library

2. **Runtime Errors**
   - Verify input file exists and has correct format
   - Check file permissions for reading input and writing output
   - Ensure sufficient memory for large test cases

3. **Performance Issues**
   - For very large inputs, the slow version may take significant time
   - Consider testing with smaller datasets first

### File Requirements
- All source files must be present in the same directory
- Input files must follow the specified format
- No executable files should be included in submission

## Academic Integrity

This implementation follows the project requirements for original code development. All algorithms are implemented from scratch without copying existing implementations, in compliance with academic honesty policies.

## Git Commit Conventions

This project follows conventional commit types for better version control management:

| Type | Purpose |
|------|---------|
| `feat` | Add a new feature (functions, logic) |
| `fix` | Fix a bug (incorrect output, logic errors) |
| `refactor` | Improve code without changing behavior |
| `perf` | Optimize performance (faster loops, better memory usage) |
| `style` | Formatting changes (indentation, comments) |
| `test` | Add or update test cases |
| `build` | Modify Makefile or compilation setup |
| `docs` | Update README, specs, or comments |
| `chore` | Non-code maintenance (renaming files, updating .gitignore) |

### Example Commit Messages:
```
feat: implement stack data structure with NEXT-TO-TOP operation
fix: correct orientation calculation for collinear points
perf: optimize quick sort partitioning algorithm
test: add test cases for 32768 points
docs: update README with compilation instructions
style: format code according to project standards
```

---

**Note**: This project demonstrates the practical impact of algorithm choice on performance, particularly how sorting algorithm efficiency affects the overall performance of computational geometry algorithms like Graham's Scan.
