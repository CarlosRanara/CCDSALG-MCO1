# Makefile for Graham's Scan Convex Hull Project
# CCDSALG/GDDASGO Term 1, AY 2024-2025

# Compiler and flags
CC = gcc
CFLAGS = -Wall -std=c99 -g
LDFLAGS = -lm

# Executable names
GRAHAM_SLOW = graham_slow
GRAHAM_FAST = graham_fast

# Object files
COMMON_OBJS = stack.o sort.o
SLOW_OBJS = $(COMMON_OBJS) graham_scan1.o main1.o
FAST_OBJS = $(COMMON_OBJS) graham_scan2.o main2.o

# Test files
TEST_INPUT = sample-input.txt
TEST_OUTPUT_SLOW = test_output_slow.txt
TEST_OUTPUT_FAST = test_output_fast.txt

# Default target
all: $(GRAHAM_SLOW) $(GRAHAM_FAST)

# Build slow version (bubble sort)
$(GRAHAM_SLOW): $(SLOW_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Build fast version (quick sort)
$(GRAHAM_FAST): $(FAST_OBJS)
	$(CC) $(CFLAGS) -o $@ $^ $(LDFLAGS)

# Generic rule for object files
%.o: %.c
	$(CC) $(CFLAGS) -c $<

# Run both versions with sample input
run: $(GRAHAM_SLOW) $(GRAHAM_FAST)
	@echo "=== Running Graham's Scan (Slow Version) ==="
	@echo "$(TEST_INPUT)" | ./$(GRAHAM_SLOW) | echo "$(TEST_OUTPUT_SLOW)"
	@echo ""
	@echo "=== Running Graham's Scan (Fast Version) ==="
	@echo "$(TEST_INPUT)" | ./$(GRAHAM_FAST) | echo "$(TEST_OUTPUT_FAST)"
	@echo ""
	@echo "=== Execution Complete ==="
	@echo "Check $(TEST_OUTPUT_SLOW) and $(TEST_OUTPUT_FAST) for results"

# Interactive run - prompts user for input/output files
run-interactive: $(GRAHAM_SLOW) $(GRAHAM_FAST)
	@echo "=== Running Graham's Scan (Slow Version) ==="
	./$(GRAHAM_SLOW)
	@echo ""
	@echo "=== Running Graham's Scan (Fast Version) ==="
	./$(GRAHAM_FAST)

# Run only slow version
run-slow: $(GRAHAM_SLOW)
	@echo "=== Running Graham's Scan (Slow Version Only) ==="
	./$(GRAHAM_SLOW)

# Run only fast version
run-fast: $(GRAHAM_FAST)
	@echo "=== Running Graham's Scan (Fast Version Only) ==="
	./$(GRAHAM_FAST)

# Test with all provided test cases
test: $(GRAHAM_SLOW) $(GRAHAM_FAST)
	@echo "=== Running Performance Tests ==="
	@for i in 1 2 3 4 5; do \
		if [ -f "INPUT$$i.TXT" ]; then \
			echo "Testing INPUT$$i.TXT..."; \
			echo "INPUT$$i.TXT" | ./$(GRAHAM_SLOW) | echo "OUTPUT$$i\_SLOW.TXT"; \
			echo "INPUT$$i.TXT" | ./$(GRAHAM_FAST) | echo "OUTPUT$$i\_FAST.TXT"; \
		fi; \
	done
	@echo "=== Performance Tests Complete ==="

# Check if source files exist
check:
	@echo "=== Checking Required Files ==="
	@for file in stack.h stack.c sort.h sort.c graham_scan.h graham_scan1.c graham_scan2.c main1.c main2.c; do \
		if [ -f "$$file" ]; then \
			echo "✓ $$file exists"; \
		else \
			echo "✗ $$file missing"; \
		fi; \
	done

# Clean build artifacts
clean:
	@echo "=== Cleaning build artifacts ==="
	rm -f *.o $(GRAHAM_SLOW) $(GRAHAM_FAST)
	@echo "Clean complete"

# Clean everything including test outputs
clean-all: clean
	@echo "=== Cleaning all generated files ==="
	rm -f OUTPUT*.TXT test_output_*.txt
	@echo "Clean all complete"

# Show help
help:
	@echo "Graham's Scan Makefile Commands:"
	@echo ""
	@echo "Build targets:"
	@echo "  all                 - Build both slow and fast versions (default)"
	@echo "  $(GRAHAM_SLOW)      - Build slow version only"
	@echo "  $(GRAHAM_FAST)      - Build fast version only"
	@echo ""
	@echo "Run targets:"
	@echo "  run                 - Run both versions with sample input"
	@echo "  run-interactive     - Run both versions with user input"
	@echo "  run-slow            - Run slow version only"
	@echo "  run-fast            - Run fast version only"
	@echo "  test                - Run performance tests on all INPUT files"
	@echo ""
	@echo "Utility targets:"
	@echo "  check               - Check if all required source files exist"
	@echo "  clean               - Remove object files and executables"
	@echo "  clean-all           - Remove all generated files including outputs"
	@echo "  help                - Show this help message"

# Install dependencies (for development)
install-deps:
	@echo "=== Checking development dependencies ==="
	@which gcc > /dev/null || (echo "Install GCC compiler" && exit 1)
	@echo "✓ GCC compiler found"
	@echo "All dependencies satisfied"

# Debug build with extra flags
debug: CFLAGS += -DDEBUG -O0
debug: clean all
	@echo "=== Debug build complete ==="
	@echo "Built with debug symbols and no optimization"

# Release build with optimization
release: CFLAGS += -O2 -DNDEBUG
release: clean all
	@echo "=== Release build complete ==="
	@echo "Built with optimization"

# Show file sizes
size: $(GRAHAM_SLOW) $(GRAHAM_FAST)
	@echo "=== Executable Sizes ==="
	@ls -lh $(GRAHAM_SLOW) $(GRAHAM_FAST)

# Declare phony targets
.PHONY: all run run-interactive run-slow run-fast test check clean clean-all help install-deps debug release size
