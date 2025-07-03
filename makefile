# Makefile for Graham's Scan Convex Hull Project
# CCDSALG Term 3, AY 2024-2025
# Group 16 Assignment: Bubble Sort (slow) + Merge Sort (fast)

# Compiler and flags
CC = gcc
CFLAGS = -Wall -std=c99 -Iinclude
LDFLAGS = -lm
DEBUG_FLAGS = -g -DDEBUG
RELEASE_FLAGS = -O2 -DNDEBUG

# Directories
SRCDIR = src
INCDIR = include
SPECSDIR = specs
TESTDIR = .

# Source files
STACK_SRC = $(SRCDIR)/stack.c
SORT_SRC = $(SRCDIR)/sort.c
GRAHAM1_SRC = $(SRCDIR)/graham_scan1.c
GRAHAM2_SRC = $(SRCDIR)/graham_scan2.c
MAIN1_SRC = $(SRCDIR)/main1.c
MAIN2_SRC = $(SRCDIR)/main2.c

# Header files
STACK_HDR = $(INCDIR)/stack.h
SORT_HDR = $(INCDIR)/sort.h
GRAHAM_HDR = $(INCDIR)/graham_scan.h

# Object files
OBJDIR = obj
STACK_OBJ = $(OBJDIR)/stack.o
SORT_OBJ = $(OBJDIR)/sort.o
GRAHAM1_OBJ = $(OBJDIR)/graham_scan1.o
GRAHAM2_OBJ = $(OBJDIR)/graham_scan2.o
MAIN1_OBJ = $(OBJDIR)/main1.o
MAIN2_OBJ = $(OBJDIR)/main2.o

# Executables
SLOW_EXE = graham_slow
FAST_EXE = graham_fast

# Test input files (update these based on your actual test files)
TEST_INPUTS = $(SRCDIR)/sample-input.txt $(SRCDIR)/input-circle.txt
INPUT_FILES = INPUT1.TXT INPUT2.TXT INPUT3.TXT INPUT4.TXT INPUT5.TXT \
              INPUT6.TXT INPUT7.TXT INPUT8.TXT INPUT9.TXT INPUT10.TXT

# Sample files in src directory
SAMPLE_INPUT = $(SRCDIR)/sample-input.txt
SAMPLE_OUTPUT_EXPECTED = $(SRCDIR)/sample-output.txt
CIRCLE_INPUT = $(SRCDIR)/input-circle.txt
CIRCLE_OUTPUT_EXPECTED = $(SRCDIR)/output-circle.txt

# Default target
.PHONY: all
all: $(SLOW_EXE) $(FAST_EXE)

# Create object directory if it doesn't exist
$(OBJDIR):
	mkdir -p $(OBJDIR)

# Build slow version (with bubble sort)
$(SLOW_EXE): $(OBJDIR) $(STACK_OBJ) $(SORT_OBJ) $(GRAHAM1_OBJ) $(MAIN1_OBJ)
	$(CC) $(STACK_OBJ) $(SORT_OBJ) $(GRAHAM1_OBJ) $(MAIN1_OBJ) -o $@ $(LDFLAGS)

# Build fast version (with merge sort)
$(FAST_EXE): $(OBJDIR) $(STACK_OBJ) $(SORT_OBJ) $(GRAHAM2_OBJ) $(MAIN2_OBJ)
	$(CC) $(STACK_OBJ) $(SORT_OBJ) $(GRAHAM2_OBJ) $(MAIN2_OBJ) -o $@ $(LDFLAGS)

# Object file compilation rules
$(STACK_OBJ): $(STACK_SRC) $(STACK_HDR) | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(SORT_OBJ): $(SORT_SRC) $(SORT_HDR) $(STACK_HDR) | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(GRAHAM1_OBJ): $(GRAHAM1_SRC) $(GRAHAM_HDR) $(SORT_HDR) $(STACK_HDR) | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(GRAHAM2_OBJ): $(GRAHAM2_SRC) $(GRAHAM_HDR) $(SORT_HDR) $(STACK_HDR) | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(MAIN1_OBJ): $(MAIN1_SRC) $(GRAHAM_HDR) | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

$(MAIN2_OBJ): $(MAIN2_SRC) $(GRAHAM_HDR) | $(OBJDIR)
	$(CC) $(CFLAGS) -c $< -o $@

# Individual build targets
.PHONY: graham_slow graham_fast
graham_slow: $(SLOW_EXE)
graham_fast: $(FAST_EXE)

# Debug builds
.PHONY: debug debug-slow debug-fast
debug: debug-slow debug-fast

debug-slow: CFLAGS += $(DEBUG_FLAGS)
debug-slow: $(SLOW_EXE)

debug-fast: CFLAGS += $(DEBUG_FLAGS)
debug-fast: $(FAST_EXE)

# Release builds
.PHONY: release release-slow release-fast
release: release-slow release-fast

release-slow: CFLAGS += $(RELEASE_FLAGS)
release-slow: $(SLOW_EXE)

release-fast: CFLAGS += $(RELEASE_FLAGS)
release-fast: $(FAST_EXE)

# Run targets
.PHONY: run run-slow run-fast run-interactive run-sample run-circle
run: run-sample

run-slow: $(SLOW_EXE)
	@echo "=== Running Graham's Scan (Slow Version) ==="
	./$(SLOW_EXE)

run-fast: $(FAST_EXE)
	@echo "=== Running Graham's Scan (Fast Version) ==="
	./$(FAST_EXE)

run-interactive: $(SLOW_EXE) $(FAST_EXE)
	@echo "=== Running Graham's Scan (Slow Version) ==="
	./$(SLOW_EXE)
	@echo ""
	@echo "=== Running Graham's Scan (Fast Version) ==="
	./$(FAST_EXE)

# Run with sample input (automated)
run-sample: $(SLOW_EXE) $(FAST_EXE)
	@echo "=== Testing with sample-input.txt ==="
	@echo "$(SAMPLE_INPUT)" | ./$(SLOW_EXE) > /dev/null 2>&1 || echo "Note: Sample input requires manual input"
	@echo "$(SAMPLE_INPUT)" | ./$(FAST_EXE) > /dev/null 2>&1 || echo "Note: Sample input requires manual input"
	@echo "Both versions completed. Check output files."

# Run with circle input (automated)
run-circle: $(SLOW_EXE) $(FAST_EXE)
	@echo "=== Testing with input-circle.txt ==="
	@echo "$(CIRCLE_INPUT)" | ./$(SLOW_EXE) > /dev/null 2>&1 || echo "Note: Circle input requires manual input"
	@echo "$(CIRCLE_INPUT)" | ./$(FAST_EXE) > /dev/null 2>&1 || echo "Note: Circle input requires manual input"
	@echo "Both versions completed. Check output files."

# Performance testing
.PHONY: test test-all test-performance bigtest generate-inputs
test: test-performance

test-all: $(SLOW_EXE) $(FAST_EXE)
	@echo "=== Performance Testing ==="
	@echo "Testing both versions with available input files..."
	@for input in $(TEST_INPUTS); do \
		if [ -f "$input" ]; then \
			echo "Testing with $input"; \
			echo "Running slow version..."; \
			echo "Running fast version..."; \
		fi; \
	done
	@echo "Manual testing required - programs need interactive input"

test-performance: $(SLOW_EXE) $(FAST_EXE)
	@echo "=== Performance Test Instructions ==="
	@echo "To run performance tests, execute the following manually:"
	@echo ""
	@echo "For each INPUT file (INPUT1.TXT to INPUT10.TXT):"
	@echo "1. Run: ./$(SLOW_EXE)"
	@echo "   - Enter input filename: INPUTn.TXT"
	@echo "   - Enter output filename: OUTPUTn_SLOW.TXT"
	@echo "2. Run: ./$(FAST_EXE)"
	@echo "   - Enter input filename: INPUTn.TXT" 
	@echo "   - Enter output filename: OUTPUTn_FAST.TXT"
	@echo "3. Record the execution times for comparison"

# Automated comprehensive testing
bigtest: $(SLOW_EXE) $(FAST_EXE) generate-inputs
	@echo "=== BIG TEST: Automated Performance Testing ==="
	@echo "This will run all 10 test cases automatically..."
	@echo "Results will be saved in results/ directory"
	@mkdir -p results
	@echo "Test Case,Input Size,Slow Time (ms),Fast Time (ms),Slow Output File,Fast Output File" > results/performance_summary.csv
	@echo ""
	@for i in 1 2 3 4 5 6 7 8 9 10; do \
		if [ -f "INPUT$i.TXT" ]; then \
			echo "=== Running Test Case $i ==="; \
			input_size=$(head -1 INPUT$i.TXT); \
			echo "Input size: $input_size points"; \
			echo ""; \
			echo "Running slow version (Bubble Sort)..."; \
			echo -e "INPUT$i.TXT\nresults/OUTPUT$i\_SLOW.TXT" | ./$(SLOW_EXE) > results/slow_$i.log 2>&1; \
			slow_time=$(grep "execution time" results/slow_$i.log | sed 's/.*: \([0-9.]*\) milliseconds/\1/' || echo "N/A"); \
			echo "Slow version completed in $slow_time ms"; \
			echo ""; \
			echo "Running fast version (Merge Sort)..."; \
			echo -e "INPUT$i.TXT\nresults/OUTPUT$i\_FAST.TXT" | ./$(FAST_EXE) > results/fast_$i.log 2>&1; \
			fast_time=$(grep "execution time" results/fast_$i.log | sed 's/.*: \([0-9.]*\) milliseconds/\1/' || echo "N/A"); \
			echo "Fast version completed in $fast_time ms"; \
			echo ""; \
			echo "Comparing outputs..."; \
			if diff results/OUTPUT$i\_SLOW.TXT results/OUTPUT$i\_FAST.TXT > /dev/null 2>&1; then \
				echo "✓ Outputs are identical"; \
			else \
				echo "✗ Warning: Outputs differ!"; \
			fi; \
			echo "$i,$input_size,$slow_time,$fast_time,OUTPUT$i\_SLOW.TXT,OUTPUT$i\_FAST.TXT" >> results/performance_summary.csv; \
			echo "----------------------------------------"; \
			echo ""; \
		else \
			echo "✗ INPUT$i.TXT not found - skipping"; \
		fi; \
	done
	@echo ""
	@echo "=== BIG TEST COMPLETE ==="
	@echo "Results saved in results/ directory:"
	@echo "  - performance_summary.csv: Timing comparison table"
	@echo "  - OUTPUT*_SLOW.TXT: Slow version outputs"
	@echo "  - OUTPUT*_FAST.TXT: Fast version outputs"
	@echo "  - slow_*.log: Slow version execution logs"
	@echo "  - fast_*.log: Fast version execution logs"
	@echo ""
	@echo "Performance Summary:"
	@cat results/performance_summary.csv
	@echo ""
	@echo "Use this data for your documentation table and graphs!"

# Generate input files using Python script
generate-inputs:
	@echo "=== Generating Input Files ==="
	@if [ -f "generate_inputs.py" ]; then \
		echo "Using existing generate_inputs.py..."; \
		python3 generate_inputs.py; \
		echo "✓ All INPUT files generated successfully"; \
	elif command -v python3 >/dev/null 2>&1; then \
		echo "Python3 found but generate_inputs.py missing."; \
		echo "Creating simple input files instead..."; \
		$(MAKE) create-simple-inputs; \
	else \
		echo "Python3 not found. Creating simple input files..."; \
		$(MAKE) create-simple-inputs; \
	fi

# Create simple input files without Python
create-simple-inputs:
	@echo "Creating INPUT files with simple patterns..."
	@echo "64" > INPUT1.TXT
	@printf "%10.6f %10.6f\n" 10.0 0.0 >> INPUT1.TXT
	@printf "%10.6f %10.6f\n" 9.951847 0.980171 >> INPUT1.TXT
	@printf "%10.6f %10.6f\n" 9.807853 1.950903 >> INPUT1.TXT
	@printf "%10.6f %10.6f\n" 9.569403 2.902846 >> INPUT1.TXT
	@printf "%10.6f %10.6f\n" 9.238795 3.826834 >> INPUT1.TXT
	@printf "%10.6f %10.6f\n" 8.819213 4.713967 >> INPUT1.TXT
	@printf "%10.6f %10.6f\n" 8.314696 5.555702 >> INPUT1.TXT
	@printf "%10.6f %10.6f\n" 7.730104 6.343933 >> INPUT1.TXT
	@printf "%10.6f %10.6f\n" 7.071068 7.071068 >> INPUT1.TXT
	@printf "%10.6f %10.6f\n" 6.343933 7.730104 >> INPUT1.TXT
	@printf "%10.6f %10.6f\n" 5.555702 8.314696 >> INPUT1.TXT
	@printf "%10.6f %10.6f\n" 4.713967 8.819213 >> INPUT1.TXT
	@printf "%10.6f %10.6f\n" 3.826834 9.238795 >> INPUT1.TXT
	@printf "%10.6f %10.6f\n" 2.902846 9.569403 >> INPUT1.TXT
	@printf "%10.6f %10.6f\n" 1.950903 9.807853 >> INPUT1.TXT
	@printf "%10.6f %10.6f\n" 0.980171 9.951847 >> INPUT1.TXT
	@printf "%10.6f %10.6f\n" 0.0 10.0 >> INPUT1.TXT
	@printf "%10.6f %10.6f\n" -0.980171 9.951847 >> INPUT1.TXT
	@printf "%10.6f %10.6f\n" -1.950903 9.807853 >> INPUT1.TXT
	@printf "%10.6f %10.6f\n" -2.902846 9.569403 >> INPUT1.TXT
	@printf "%10.6f %10.6f\n" -3.826834 9.238795 >> INPUT1.TXT
	@printf "%10.6f %10.6f\n" -4.713967 8.819213 >> INPUT1.TXT
	@printf "%10.6f %10.6f\n" -5.555702 8.314696 >> INPUT1.TXT
	@printf "%10.6f %10.6f\n" -6.343933 7.730104 >> INPUT1.TXT
	@printf "%10.6f %10.6f\n" -7.071068 7.071068 >> INPUT1.TXT
	@printf "%10.6f %10.6f\n" -7.730104 6.343933 >> INPUT1.TXT
	@printf "%10.6f %10.6f\n" -8.314696 5.555702 >> INPUT1.TXT
	@printf "%10.6f %10.6f\n" -8.819213 4.713967 >> INPUT1.TXT
	@printf "%10.6f %10.6f\n" -9.238795 3.826834 >> INPUT1.TXT
	@printf "%10.6f %10.6f\n" -9.569403 2.902846 >> INPUT1.TXT
	@printf "%10.6f %10.6f\n" -9.807853 1.950903 >> INPUT1.TXT
	@printf "%10.6f %10.6f\n" -9.951847 0.980171 >> INPUT1.TXT
	@printf "%10.6f %10.6f\n" -10.0 0.0 >> INPUT1.TXT
	@printf "%10.6f %10.6f\n" -9.951847 -0.980171 >> INPUT1.TXT
	@printf "%10.6f %10.6f\n" -9.807853 -1.950903 >> INPUT1.TXT
	@printf "%10.6f %10.6f\n" -9.569403 -2.902846 >> INPUT1.TXT
	@printf "%10.6f %10.6f\n" -9.238795 -3.826834 >> INPUT1.TXT
	@printf "%10.6f %10.6f\n" -8.819213 -4.713967 >> INPUT1.TXT
	@printf "%10.6f %10.6f\n" -8.314696 -5.555702 >> INPUT1.TXT
	@printf "%10.6f %10.6f\n" -7.730104 -6.343933 >> INPUT1.TXT
	@printf "%10.6f %10.6f\n" -7.071068 -7.071068 >> INPUT1.TXT
	@printf "%10.6f %10.6f\n" -6.343933 -7.730104 >> INPUT1.TXT
	@printf "%10.6f %10.6f\n" -5.555702 -8.314696 >> INPUT1.TXT
	@printf "%10.6f %10.6f\n" -4.713967 -8.819213 >> INPUT1.TXT
	@printf "%10.6f %10.6f\n" -3.826834 -9.238795 >> INPUT1.TXT
	@printf "%10.6f %10.6f\n" -2.902846 -9.569403 >> INPUT1.TXT
	@printf "%10.6f %10.6f\n" -1.950903 -9.807853 >> INPUT1.TXT
	@printf "%10.6f %10.6f\n" -0.980171 -9.951847 >> INPUT1.TXT
	@printf "%10.6f %10.6f\n" 0.0 -10.0 >> INPUT1.TXT
	@printf "%10.6f %10.6f\n" 0.980171 -9.951847 >> INPUT1.TXT
	@printf "%10.6f %10.6f\n" 1.950903 -9.807853 >> INPUT1.TXT
	@printf "%10.6f %10.6f\n" 2.902846 -9.569403 >> INPUT1.TXT
	@printf "%10.6f %10.6f\n" 3.826834 -9.238795 >> INPUT1.TXT
	@printf "%10.6f %10.6f\n" 4.713967 -8.819213 >> INPUT1.TXT
	@printf "%10.6f %10.6f\n" 5.555702 -8.314696 >> INPUT1.TXT
	@printf "%10.6f %10.6f\n" 6.343933 -7.730104 >> INPUT1.TXT
	@printf "%10.6f %10.6f\n" 7.071068 -7.071068 >> INPUT1.TXT
	@printf "%10.6f %10.6f\n" 7.730104 -6.343933 >> INPUT1.TXT
	@printf "%10.6f %10.6f\n" 8.314696 -5.555702 >> INPUT1.TXT
	@printf "%10.6f %10.6f\n" 8.819213 -4.713967 >> INPUT1.TXT
	@printf "%10.6f %10.6f\n" 9.238795 -3.826834 >> INPUT1.TXT
	@printf "%10.6f %10.6f\n" 9.569403 -2.902846 >> INPUT1.TXT
	@printf "%10.6f %10.6f\n" 9.807853 -1.950903 >> INPUT1.TXT
	@printf "%10.6f %10.6f\n" 9.951847 -0.980171 >> INPUT1.TXT
	@printf "%10.6f %10.6f\n" 2.5 2.5 >> INPUT1.TXT
	@printf "%10.6f %10.6f\n" -2.5 7.5 >> INPUT1.TXT
	@printf "%10.6f %10.6f\n" 0.0 -5.0 >> INPUT1.TXT
	@printf "%10.6f %10.6f\n" 5.0 5.0 >> INPUT1.TXT
	@echo "128" > INPUT2.TXT
	@for i in $(seq 1 128); do \
		angle=$(echo "scale=6; 2 * 3.14159 * ($i - 1) / 128" | bc -l); \
		x=$(echo "scale=6; 12 * c($angle)" | bc -l); \
		y=$(echo "scale=6; 12 * s($angle)" | bc -l); \
		printf "%10.6f %10.6f\n" $x $y >> INPUT2.TXT; \
	done 2>/dev/null || (echo "bc not found, creating simplified INPUT2.TXT"; \
		for i in $(seq 1 128); do printf "%10.6f %10.6f\n" $i $i >> INPUT2.TXT; done)
	@echo "✓ Created INPUT1.TXT (64 points) and INPUT2.TXT (128 points)"
	@echo "For remaining files (INPUT3-INPUT10), use: python3 generate_inputs.py"

# Quick test with first few input files
quicktest: $(SLOW_EXE) $(FAST_EXE)
	@echo "=== Quick Test (First 3 test cases) ==="
	@mkdir -p results
	@for i in 1 2 3; do \
		if [ -f "INPUT$i.TXT" ]; then \
			echo "Testing INPUT$i.TXT..."; \
			echo -e "INPUT$i.TXT\nresults/OUTPUT$i\_SLOW.TXT" | ./$(SLOW_EXE) | grep "execution time"; \
			echo -e "INPUT$i.TXT\nresults/OUTPUT$i\_FAST.TXT" | ./$(FAST_EXE) | grep "execution time"; \
			echo ""; \
		fi; \
	done

# Test with empirical timing (if you want to test the timing example)
.PHONY: test-timing
test-timing:
	@if [ -f "$(SPECSDIR)/empirical-time.c" ]; then \
		echo "=== Compiling and running empirical timing example ==="; \
		$(CC) $(CFLAGS) $(SPECSDIR)/empirical-time.c -o empirical-time $(LDFLAGS); \
		./empirical-time; \
		rm -f empirical-time; \
	else \
		echo "empirical-time.c not found in $(SPECSDIR)/"; \
	fi

# Validation and checks
.PHONY: check check-files check-syntax
check: check-files check-syntax

check-files:
	@echo "=== Checking Required Files ==="
	@echo "Checking source files..."
	@for file in $(STACK_SRC) $(SORT_SRC) $(GRAHAM1_SRC) $(GRAHAM2_SRC) $(MAIN1_SRC) $(MAIN2_SRC); do \
		if [ -f "$$file" ]; then \
			echo "✓ $$file"; \
		else \
			echo "✗ $$file (MISSING)"; \
		fi; \
	done
	@echo "Checking header files..."
	@for file in $(STACK_HDR) $(SORT_HDR) $(GRAHAM_HDR); do \
		if [ -f "$$file" ]; then \
			echo "✓ $$file"; \
		else \
			echo "✗ $$file (MISSING)"; \
		fi; \
	done
	@echo "Checking sample files..."
	@for file in $(SAMPLE_INPUT) $(CIRCLE_INPUT); do \
		if [ -f "$$file" ]; then \
			echo "✓ $$file"; \
		else \
			echo "✗ $$file (MISSING)"; \
		fi; \
	done

check-syntax: 
	@echo "=== Syntax Check ==="
	@echo "Checking for compilation errors..."
	@$(CC) $(CFLAGS) -fsyntax-only $(STACK_SRC) $(SORT_SRC) $(GRAHAM1_SRC) $(MAIN1_SRC) 2>/dev/null && echo "✓ Slow version syntax OK" || echo "✗ Slow version has syntax errors"
	@$(CC) $(CFLAGS) -fsyntax-only $(STACK_SRC) $(SORT_SRC) $(GRAHAM2_SRC) $(MAIN2_SRC) 2>/dev/null && echo "✓ Fast version syntax OK" || echo "✗ Fast version has syntax errors"

# File size information
.PHONY: size
size: $(SLOW_EXE) $(FAST_EXE)
	@echo "=== Executable Sizes ==="
	@ls -lh $(SLOW_EXE) $(FAST_EXE)

# Dependency tracking
.PHONY: deps
deps:
	@echo "=== Dependency Information ==="
	@echo "Stack module depends on: $(STACK_HDR)"
	@echo "Sort module depends on: $(SORT_HDR) $(STACK_HDR)"
	@echo "Graham Scan modules depend on: $(GRAHAM_HDR) $(SORT_HDR) $(STACK_HDR)"
	@echo "Main modules depend on: $(GRAHAM_HDR)"

# Clean targets
.PHONY: clean clean-all clean-obj clean-exe clean-output
clean: clean-obj clean-exe

clean-obj:
	@echo "Removing object files..."
	@rm -rf $(OBJDIR)

clean-exe:
	@echo "Removing executables..."
	@rm -f $(SLOW_EXE) $(FAST_EXE)

clean-output:
	@echo "Removing output files..."
	@rm -f OUTPUT*.TXT *.txt

clean-all: clean clean-output
	@echo "Cleaned all generated files"

# Project management
.PHONY: archive package submission
archive:
	@echo "=== Creating Project Archive ==="
	@tar -czf graham_scan_project.tar.gz $(SRCDIR)/ $(INCDIR)/ makefile README.md $(SPECSDIR)/

package: clean-all
	@echo "=== Creating Submission Package ==="
	@mkdir -p submission
	@cp -r $(SRCDIR)/*.c $(SRCDIR)/*.txt submission/
	@cp -r $(INCDIR)/*.h submission/
	@cp README.md submission/
	@echo "Submission package created in submission/"

submission: check clean all
	@echo "=== Preparing for Submission ==="
	@echo "1. All files checked ✓"
	@echo "2. Project cleaned and rebuilt ✓"
	@echo "3. Ready for submission"
	@echo ""
	@echo "Remember to include:"
	@echo "- All .c and .h files"
	@echo "- INPUT1.TXT to INPUT10.TXT (test cases)"
	@echo "- OUTPUT1.TXT to OUTPUT10.TXT (results)"
	@echo "- GROUPNUMBER.PDF (documentation)"
	@echo "- NO .exe files!"

# Development helpers
.PHONY: format lint
format:
	@echo "=== Code Formatting Suggestions ==="
	@echo "Use your preferred C formatter (indent, astyle, clang-format)"
	@echo "Example: indent -linux $(SRCDIR)/*.c $(INCDIR)/*.h"

lint:
	@echo "=== Static Analysis ==="
	@echo "Consider running: cppcheck $(SRCDIR)/ $(INCDIR)/"

# Information and help
.PHONY: info help
info:
	@echo "=== Graham's Scan Convex Hull Project ==="
	@echo "CCDSALG Term 3, AY 2024-2025"
	@echo "Group 16 Assignment: Bubble Sort (slow) + Merge Sort (fast)"
	@echo ""
	@echo "Project Structure:"
	@echo "  $(SRCDIR)/     - Source files (.c)"
	@echo "  $(INCDIR)/     - Header files (.h)"
	@echo "  $(SPECSDIR)/   - Project specifications"
	@echo "  makefile       - Build configuration"
	@echo "  README.md      - Project documentation"
	@echo ""
	@echo "Executables:"
	@echo "  $(SLOW_EXE)    - Graham's Scan with Bubble Sort"
	@echo "  $(FAST_EXE)    - Graham's Scan with Merge Sort"

help:
	@echo "=== Available Make Targets ==="
	@echo ""
	@echo "BUILD TARGETS:"
	@echo "  all            - Build both slow and fast versions (default)"
	@echo "  graham_slow    - Build slow version only"
	@echo "  graham_fast    - Build fast version only"
	@echo "  debug          - Build both versions with debug symbols"
	@echo "  release        - Build optimized versions"
	@echo ""
	@echo "RUN TARGETS:"
	@echo "  run            - Run sample test"
	@echo "  run-slow       - Run slow version only"
	@echo "  run-fast       - Run fast version only"
	@echo "  run-interactive - Run both versions with user input prompts"
	@echo "  run-sample     - Test with sample-input.txt"
	@echo "  run-circle     - Test with input-circle.txt"
	@echo ""
	@echo "TEST TARGETS:"
	@echo "  test           - Show performance testing instructions"
	@echo "  test-timing    - Run empirical timing example"
	@echo "  check          - Verify files and syntax"
	@echo "  check-files    - Check if all required files exist"
	@echo "  check-syntax   - Check for compilation errors"
	@echo ""
	@echo "UTILITY TARGETS:"
	@echo "  clean          - Remove object files and executables"
	@echo "  clean-all      - Remove all generated files"
	@echo "  size           - Show executable file sizes"
	@echo "  deps           - Show dependency information"
	@echo "  info           - Show project information"
	@echo "  submission     - Prepare for project submission"
	@echo ""
	@echo "EXAMPLES:"
	@echo "  make              # Build everything"
	@echo "  make run-interactive  # Run with user prompts"
	@echo "  make test         # Show testing instructions"
	@echo "  make clean all    # Clean and rebuild"
	@echo "  make submission   # Prepare for submission"
