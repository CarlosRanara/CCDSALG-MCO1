#include "graham_scan1.c"

typedef char String50[51];

int main(){
    String50 inputFile, outputFile;
    point set[MAX];
    stack hullPoints;
    FILE *fpInput, *fpOutput;
    int n, ctr = 0;

    //get input and output file
    printf("Input the name and extension type of the input text file: ");
    scanf("%s", inputFile);
    printf("\nInput the name and extension type of the output text file: ");
    scanf("%s", outputFile);

    //ensure inputFile exists and can be opened + outputFile can be written
    if((fpInput = fopen(inputFile, "r")) && (fpOutput = fopen(outputFile, "w"))){
        //get n number of points given
        fscanf(fpInput, "%d", &n);
        
        //read n number of points
        while( !(feof(fpInput)) && ctr < n){
            fscanf(fpInput, "%lf", &set[ctr].x);
            fscanf(fpInput, "%lf", &set[ctr].y);
            ctr++;
        }

        //close inputFile when done reading
        fclose(fpInput);

        for(int i = 0; i < n; i++)
            printf("\n%d). %lf, %lf", (i+1), set[i].x, set[i].y);

        printf("\n run1");
        //perform Graham's scan
        grahamScanSlow(set, &hullPoints, n);

        //print m number of points on convex hull
        fprintf(fpOutput, "%d\n", hullPoints.top);

        //print convex hull points in outputFile
        for(ctr = 0; ctr < hullPoints.top; ctr++){
            fprintf(fpOutput, "%.6lf\t%.6lf\n", hullPoints.array[ctr].x, hullPoints.array[ctr].y);
        }

        //close outputFile when done writing
        fclose(fpOutput);
    }

    return 0;
}