#include "matrix.h"

int** createMatrix(int rows, int columns)
{
    int i;

    int **matrix = (int **) calloc(rows, sizeof(int *));    
    for (i = 0; i < rows; i++)
    {
        matrix[i] = (int *) calloc(columns, sizeof(int));
    }

    return matrix;
} 

void printMatrix(int **matrix, int rows, int columns)
{
    int i, j;

    for (i = 0; i < rows; i++)
    {
        for(j = 0; j < columns; j++)
        {
            printf("%i ", matrix[i][j]);
        }
        printf("\n");
    }
}

float** createFloatMatrix(int rows, int columns)
{
    int i;

    float **matrix = (float **) calloc(rows, sizeof(float *));    
    for (i = 0; i < rows; i++)
    {
        matrix[i] = (float *) calloc(columns, sizeof(float));
    }

    return matrix;
} 

void printFloatMatrix(float **matrix, int rows, int columns)
{
    int i, j;

    printf("\n");
    for (i = 0; i < rows; i++)
    {
        for(j = 0; j < columns; j++)
        {
            printf("%10f ", matrix[i][j]);
        }
        printf("\n\n");
    }
}