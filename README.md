## Compilation Instructions

### Prerequisites
- GCC compiler with C99 standard support
- Make utility (for using Makefile)
- Math library support (`-lm` flag)
- Python3 (optional, for generating additional test files)

### Quick Start with Makefile

**Build everything:**
```bash
make
# or
make all
```

**Run automated performance tests:**
```bash
make bigtest        # Full automated testing (uses bigtest.sh)
make quicktest      # Quick test (first 3 cases only)
```

**Run both versions interactively:**
```bash
make run-interactive
```

**Other useful targets:**
```bash
make clean          # Clean build artifacts
make generate-inputs # Generate INPUT files
make help           # See all available commands
```

### Manual Compilation Commands

**One-Step Compilation (Recommended):**

Slow Version (Bubble Sort):
```bash
gcc -Wall -std=c99 -Iinclude src/stack.c src/sort.c src/graham_scan1.c src/main1.c -o graham_slow -lm
```

Fast Version (Merge Sort):
```bash
gcc -Wall -std=c99 -Iinclude src/stack.c src/sort.c src/graham_scan2.c src/main2.c -o graham_fast -lm
```

**Step-by-Step Compilation:**
```bash
# Compile object files
gcc -Wall -std=c99 -Iinclude -c src/stack.c -o stack.o
gcc -Wall -std=c99 -Iinclude -c src/sort.c -o sort.o
gcc -Wall -std=c99 -Iinclude -c src/graham_scan1.c -o graham_scan1.o
gcc -Wall -std=c99 -Iinclude -c src/graham_scan2.c -o graham_scan2.o
gcc -Wall -std=c99 -Iinclude -c src/main1.c -o main1.o
gcc -Wall -std=c99 -Iinclude -c src/main2.c -o main2.o

# Link executables
gcc stack.o sort.o graham_scan1.o main1.o -o graham_slow -lm
gcc stack.o sort.o graham_scan2.o main2.o -o graham_fast -lm

# Clean up
rm *.o
```
