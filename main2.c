/* ============================================================================
 * FILE: main2.c
 * Driver Program for Fast Version - Fully C99 Procedural Compliant
 * Programmer: [Your Name]
 * Tester: [Your Name]
 * ============================================================================ */
#include <stdio.h>
#include <stdlib.h>
#include "stack.h"

/* Function prototype for Graham Scan with fast sorting */
int grahamScan2(pointType points[], int nSize, pointType result[]);

int main() {
    FILE *pInputFile, *pOutputFile;
    char sInputFilename[256], sOutputFilename[256];
    pointType points[32768], result[32768];
    int nSize, nHullSize, i, nReadResult, bFileError;
    
    /* Ask user for input filename */
    printf("Enter the filename and extension of the input text file: ");
    nReadResult = scanf("%s", sInputFilename);
    if (nReadResult != 1) {
        printf("Error: Cannot read input filename\n");
        return 1;
    }
    
    /* Ask user for output filename */
    printf("Enter the filename and extension of the output text file: ");
    nReadResult = scanf("%s", sOutputFilename);
    if (nReadResult != 1) {
        printf("Error: Cannot read output filename\n");
        return 1;
    }
    
    /* Open input text file */
    pInputFile = fopen(sInputFilename, "r");
    if (pInputFile == NULL) {
        printf("Error: Cannot open input file %s\n", sInputFilename);
        return 1;
    }
    
    /* Read input text file contents */
    nReadResult = fscanf(pInputFile, "%d", &nSize);
    if (nReadResult != 1) {
        printf("Error: Cannot read number of points from input file\n");
        fclose(pInputFile);
        return 1;
    }
    
    if (nSize > 32768 || nSize < 0) {
        printf("Error: Invalid number of points (%d). Must be between 0 and 32768.\n", nSize);
        fclose(pInputFile);
        return 1;
    }
    
    bFileError = 0;
    for (i = 0; i < nSize && bFileError == 0; i++) {
        nReadResult = fscanf(pInputFile, "%lf %lf", &points[i].x, &points[i].y);
        if (nReadResult != 2) {
            printf("Error: Cannot read point %d from input file\n", i + 1);
            bFileError = 1;
        }
    }
    
    /* Close input file */
    fclose(pInputFile);
    
    if (bFileError == 0) {
        /* Call Graham scan algorithm implementation */
        nHullSize = grahamScan2(points, nSize, result);
        
        /* Open output text file */
        pOutputFile = fopen(sOutputFilename, "w");
        if (pOutputFile == NULL) {
            printf("Error: Cannot create output file %s\n", sOutputFilename);
            return 1;
        }
        
        /* Write output points to file */
        fprintf(pOutputFile, "%d\n", nHullSize);
        for (i = 0; i < nHullSize; i++) {
            fprintf(pOutputFile, "%.6f %.6f\n", result[i].x, result[i].y);
        }
        
        /* Close output file */
        fclose(pOutputFile);
        
        printf("Convex hull computation completed successfully!\n");
        printf("Number of input points: %d\n", nSize);
        printf("Number of hull points: %d\n", nHullSize);
    }
    
    return 0;
}