/**
 * main2.c
 * Driver program for Graham's Scan using quick sort (fast version)
 */

#include <stdio.h>
#include "graham_scan.h"

#define MAX_FILENAME_LENGTH 256

void processConvexHullFast(void);

int main(void) {
    processConvexHullFast();
    
    return 0;
}

void processConvexHullFast(void) {
    char szInputFilename[MAX_FILENAME_LENGTH];
    char szOutputFilename[MAX_FILENAME_LENGTH];
    FILE *pInputFile = NULL;
    FILE *pOutputFile = NULL;
    int nPoints;
    Point arrPoints[MAX_STACK_SIZE];
    Point arrHull[MAX_STACK_SIZE];
    int nHullSize;
    int i;
    int nScanResult;
    int bProceed;
    
    bProceed = 1;
    
    /* Get input filename from user */
    printf("Enter input filename (including extension): ");
    nScanResult = scanf("%255s", szInputFilename);
    
    if (nScanResult != 1) {
        fprintf(stderr, "Error reading input filename\n");
        bProceed = 0;
    }
    
    if (bProceed) {
        /* Get output filename from user */
        printf("Enter output filename (including extension): ");
        nScanResult = scanf("%255s", szOutputFilename);
        
        if (nScanResult != 1) {
            fprintf(stderr, "Error reading output filename\n");
            bProceed = 0;
        }
    }
    
    if (bProceed) {
        /* Open input file */
        pInputFile = fopen(szInputFilename, "r");
        if (pInputFile == NULL) {
            fprintf(stderr, "Error opening input file: %s\n", szInputFilename);
            bProceed = 0;
        }
    }
    
    if (bProceed) {
        /* Read number of points */
        nScanResult = fscanf(pInputFile, "%d", &nPoints);
        if (nScanResult != 1) {
            fprintf(stderr, "Error reading number of points\n");
            bProceed = 0;
        }
    }
    
    if (bProceed) {
        /* Read points from file */
        i = 0;
        while (i < nPoints && bProceed) {
            nScanResult = fscanf(pInputFile, "%lf %lf", &arrPoints[i].x, &arrPoints[i].y);
            if (nScanResult != 2) {
                fprintf(stderr, "Error reading point %d\n", i + 1);
                bProceed = 0;
            }
            i++;
        }
    }
    
    if (pInputFile != NULL) {
        /* Close input file */
        fclose(pInputFile);
    }
    
    if (bProceed) {
        /* Compute convex hull using Graham's Scan with quick sort */
        grahamScanFast(arrPoints, nPoints, arrHull, &nHullSize);
        
        /* Open output file */
        pOutputFile = fopen(szOutputFilename, "w");
        if (pOutputFile == NULL) {
            fprintf(stderr, "Error opening output file: %s\n", szOutputFilename);
            bProceed = 0;
        }
    }
    
    if (bProceed) {
        /* Write hull size to output file */
        fprintf(pOutputFile, "%d\n", nHullSize);
        
        /* Write hull points to output file with 6 decimal places */
        i = 0;
        while (i < nHullSize) {
            fprintf(pOutputFile, "%.6lf %.6lf\n", arrHull[i].x, arrHull[i].y);
            i++;
        }
    }
    
    if (pOutputFile != NULL) {
        /* Close output file */
        fclose(pOutputFile);
        
        if (bProceed) {
            printf("Convex hull computation complete. Results written to %s\n", szOutputFilename);
        }
    }
}