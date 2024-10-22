/*
 * This program performs a 2D convolution on a large matrix of input data using a specified filter kernel. 
 * It applies the convolution multiple times based on user input, storing the results in a matrix structure.
 * The program reads data from two input files: one for the matrix and one for the filter kernel.
 * It then processes the matrix using the filter to produce a series of convolved values, 
 * which are stored in a struct representing the original and new values. 
 * The results are written to an output file after the specified number of iterations.
 *
 * Usage:
 *     ./convolution1 <data_file> <filter_file> <output_file> <iterations>
 *
 * Arguments:
 *     data_file:    Path to the file containing the input matrix (1024x1024).
 *     filter_file:  Path to the file containing the filter kernel (5x5).
 *     output_file:  Path to the file where the convolved matrix will be written.
 *     iterations:   The number of times to apply the convolution.
 *
 * Error Handling:
 *     - The program checks if the input files are accessible and verifies that the iteration count is valid.
 *     - If any errors occur, appropriate messages are printed to the console, and the program exits.
 */

#include <stdio.h>
#include <stdlib.h>
#include<time.h>

struct matrix {
    int o_val;
    int n_val;
};
typedef struct matrix Matrix;


int main(int argc, char *argv[]) {
    FILE *file1, *file2, *file3;
    int i = 0;
    int filter[5][5];
    Matrix** data;
    int j, k, l, m;
    int val;
    int iter;

    if (argc < 5) {
    	printf("Usage: ./convolution1 data1.txt filter1.txt temp111 1\n");
    	return 1;
    }
    file1 = fopen(argv[1], "r");
    file2 = fopen(argv[2], "r");
    if ((file1 == NULL) || (file2 == NULL)) {
    	printf("Error: Files cannot open\n");
    	return 1;
    }
    iter = atoi(argv[4]);
    if (iter == 0) {
    	printf("Error: Invalid iteration\n");
    	return 1;
    }  
    file3 = fopen(argv[3], "w");
    data = (Matrix**) malloc(sizeof(Matrix*)*1024);
    for (i = 0; i < 1024; i++) {
        data[i] = (Matrix*) malloc(sizeof(Matrix)*1024);
    }


    i = 0;
    do {
        j = 0;
        do {
            if (j == 1023) {
                fscanf(file1, "%d\n", &val);
                data[i][j].o_val = val;
//                printf("%d\n", data[i][j]);
            }
            else {
                fscanf(file1, "%d,", &val);
                data[i][j].o_val = val;
//                printf("%d ", data[i][j]);
            }
            j = j + 1;
        } while (j < 1024);
        i = i + 1;
    } while (i < 1024);

    i = 0;
    do {
        int j = 0;
        do {
            if (j == 4) {
                fscanf(file2, "%d\n", &val);
                filter[i][j] = val;
//                printf("%d\n", filter[i][j]);
            }
            else {
                fscanf(file2, "%d,", &val);
                filter[i][j] = val;
//               printf("%d ", filter[i][j]);
            }
            j = j + 1;
        } while (j < 5);
        i = i + 1;
    } while (i < 5);




    /* 
    The following segment attempts to convolutionise a 2d matrix n amount of times specified by the user. 
    The program first works out y[p, q] and then scales it down and applies appropriate saturating depending filtered values applied by the kernel. 
    */
    int convolutions, sum, inverseKernelData; 
    for (convolutions = 0; convolutions < iter; convolutions++) { 
        for(i = 0; i < 1024; i++) { 
            for(j = 0; j < 1024; j++) { 
                //initalise sum 
                sum = 0;
                for(l = -2; l <= 2; l++) {
                    for(m = -2; m <= 2; m++) { 
                        //flip the inverse the kernal pointer
                        inverseKernelData = filter[2 - l][2 - m];
                        if ((i + l) >= 0 && (i + l) < 1024 && (j + m) >= 0 && (j + m) < 1024) {
                            sum += data[i + l][j + m].o_val * inverseKernelData;
                        }
                    }
                }
                //Apply scaling
                sum /= 16;

                //Apply saturation
                if (sum > 16) sum = 16;
                else if (sum >= -16 && sum <= 16) sum = sum;
                else if (sum < 16) sum = -16;

                //Set the output value (n_val) to the sum in the object. 
                data[i][j].n_val = sum;
            }
        }
        //replace original value with convolution data until max convolutions is reached.
        for(i = 0; i < 1024; i++) { 
            for(j = 0; j < 1024; j++) { 
                data[i][j].o_val = data[i][j].n_val;
            }
         }
    }

    for (i = 0; i < 1024; i++) {
        for (j = 0; j < 1024; j++) {
            fprintf(file3, "%d ", data[i][j].n_val);
        }
        fprintf(file3, "\n");
    }

    for (i = 0; i < 1024; i++) {
        free(data[i]);
    }
    free(data);
    fclose(file1);
    fclose(file2);
    fclose(file3);
    return 0;
}
