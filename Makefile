# Makefile for Graham's Scan Project
# CCDSALG Term 3, AY 2024-2025

# Compiler and flags
CC = gcc
CFLAGS = -Wall -std=c99
SRCDIR = src
INCDIR = include

# Source files
STACK_SRC = $(SRCDIR)/stack.c
SORT_SRC = $(SRCDIR)/sort.c
GRAHAM1_SRC = $(SRCDIR)/graham_scan1.c
GRAHAM2_SRC = $(SRCDIR)/graham_scan2.c

# Main files
MAIN1_SRC = main1.c
MAIN2_SRC = main2.c

# Executables
MAIN1_EXE = main1
MAIN2_EXE = main2
MAIN1_WIN = main1.exe
MAIN2_WIN = main2.exe

# Include path
INCLUDES = -I$(INCDIR)

# Default target
all: $(MAIN1_EXE) $(MAIN2_EXE)

# Build main1 (slow version with bubble sort)
$(MAIN1_EXE): $(MAIN1_SRC) $(STACK_SRC) $(SORT_SRC) $(GRAHAM1_SRC)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^

# Build main2 (fast version with merge sort)
$(MAIN2_EXE): $(MAIN2_SRC) $(STACK_SRC) $(SORT_SRC) $(GRAHAM2_SRC)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^

# Windows executables (for cross-platform compatibility)
windows: $(MAIN1_WIN) $(MAIN2_WIN)

$(MAIN1_WIN): $(MAIN1_SRC) $(STACK_SRC) $(SORT_SRC) $(GRAHAM1_SRC)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^

$(MAIN2_WIN): $(MAIN2_SRC) $(STACK_SRC) $(SORT_SRC) $(GRAHAM2_SRC)
	$(CC) $(CFLAGS) $(INCLUDES) -o $@ $^

# Generate input files
generate_inputs:
	python3 generate_inputs.py

# Run both programs (requires input files to exist)
run: $(MAIN1_EXE) $(MAIN2_EXE)
	@echo "Running both Graham's Scan implementations..."
	@echo "Make sure you have input files in data/ directory"
	@echo "Use 'make generate_inputs' to create them if needed"
	@echo ""
	@echo "Example usage:"
	@echo "echo 'data/input2^6.txt' | ./$(MAIN1_EXE)"
	@echo "echo 'data/input2^6.txt' | ./$(MAIN2_EXE)"

# Test automation
test: $(MAIN1_EXE) $(MAIN2_EXE)
	@if [ -f "test_automation.sh" ]; then \
		chmod +x test_automation.sh; \
		./test_automation.sh; \
	elif [ -f "test_automation.bat" ]; then \
		echo "Run test_automation.bat on Windows"; \
	else \
		echo "No test automation script found"; \
	fi

# Clean targets
clean: clean_executables clean_input clean_output
	@echo "All clean operations completed"

clean_executables:
	@echo "Removing executables..."
	rm -f $(MAIN1_EXE) $(MAIN2_EXE) $(MAIN1_WIN) $(MAIN2_WIN)
	@echo "✓ Executables removed"

input_clean:
	@echo "Removing data directory..."
	rm -rf data/
	@echo "✓ data/ directory removed"

output_clean:
	@echo "Removing results directory..."
	rm -rf results/
	@echo "✓ results/ directory removed"

# Aliases for consistency
clean_input: input_clean
clean_output: output_clean

# Help target
help:
	@echo "Graham's Scan Project Makefile"
	@echo "============================="
	@echo ""
	@echo "Build targets:"
	@echo "  all              - Build both main1 and main2 (default)"
	@echo "  main1            - Build slow version (bubble sort)"
	@echo "  main2            - Build fast version (merge sort)"
	@echo "  windows          - Build Windows executables (.exe)"
	@echo ""
	@echo "Utility targets:"
	@echo "  generate_inputs  - Generate input files using Python script"
	@echo "  run              - Show example usage for running programs"
	@echo "  test             - Run automated testing script"
	@echo ""
	@echo "Clean targets:"
	@echo "  clean            - Remove all generated files"
	@echo "  clean_executables- Remove only executable files"
	@echo "  input_clean      - Remove data/ directory"
	@echo "  output_clean     - Remove results/ directory"
	@echo ""
	@echo "Other:"
	@echo "  help             - Show this help message"

# Individual executable targets for explicit building
main1: $(MAIN1_EXE)
main2: $(MAIN2_EXE)

# Phony targets
.PHONY: all clean clean_executables input_clean output_clean clean_input clean_output run test generate_inputs help windows main1 main2
