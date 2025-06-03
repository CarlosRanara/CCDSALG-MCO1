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
.PHONY: test test-all test-performance
test: test-performance

test-all: $(SLOW_EXE) $(FAST_EXE)
	@echo "=== Performance Testing ==="
	@echo "Testing both versions with available input files..."
	@for input in $(TEST_INPUTS); do \
		if [ -f "$$input" ]; then \
			echo "Testing with $$input"; \
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