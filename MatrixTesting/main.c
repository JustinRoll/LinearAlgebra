//
//  main.c
//  MatrixTesting
//
//  Created by Justin Roll on 1/19/13.
//  Copyright (c) 2013 Justin Roll. All rights reserved.
//

#include <stdio.h>
#define MAXSIZE 3
void matrixMultByScalar(int matrix[MAXSIZE][MAXSIZE], int scalar, int rows, int cols);
void printMatrix(int matrix[MAXSIZE][MAXSIZE], int rows, int cols);
int rowReduceNeeded(float matrix[MAXSIZE][MAXSIZE], int row);
float findPivot(float matrix[MAXSIZE][MAXSIZE], int row);
float getLeadingNumber(float matrix[MAXSIZE][MAXSIZE], int row);
void reduceRow(float matrix[MAXSIZE][MAXSIZE], int firstRow, int secondRow, float pivotMultiplier);

int main(int argc, const char * argv[])
{
    int n;
    int m1[MAXSIZE] [MAXSIZE];
    int m2[MAXSIZE][MAXSIZE];
    
    m1[0][0] = 1;    m1[0][1] = 3;    m1[0][2] = 5;
    m1[1][0] = 2;    m1[1][1] = 6;    m1[1][2] = 10;
    m1[2][0] = 3;    m1[2][1] = 9;   m1[2][2] = 15;

    m2[0][0] = 1;    m2[0][1] = 3;    m2[0][2] = 5;
    m2[1][0] = 1;    m2[1][1] = 6;    m2[1][2] = 10;
    m2[2][0] = 0;    m2[2][1] = 0;   m2[2][2] = 3;


    //multiply matrix m1 by a scalar
    matrixMultByScalar(m1, 2, 3, 3); //multiply this 3x3 matrix by a scalar of 2
    printMatrix(m1, 3, 3);
    return 0;
}

void matrixMultByScalar(int matrix[MAXSIZE][MAXSIZE], int scalar, int rows, int cols)
{
    /*
       This function will simply multiply a matrix by a scalar
       integer. go thru entries in i and j
     */
    for (int i = 0; i < rows; i++)
    {
        for (int j=0; j< cols; j++)
        {
            matrix[i][j]=matrix[i][j]*scalar;
        }
    }
}

float** rowReduce(float matrix[MAXSIZE][MAXSIZE], int rows, int cols)
{
    /*
    Row reduce details
    
    3 4 5  -> 3 4 5     ->3 4 5    -> 3 4 5
    6 6 4     0 -2 -6     0 -2 6      0 -2 -6
    9 4 7     9 4 7       0 -8 -8     0  0 -32
    
    Matrix is a multidimensional array with a maxsize
    Make pass on row 2 through N
    Each row must have N-1 leading zeroes
    
    Main matrix loop
    for row n + 1 to N
        does row have n - 1 or more leading zeroes? if so, then skip it
            else row reduce it
                want a function for making a temporary copy of a row and then subtracting it
    
    int getPivotMultiple(int firstRowNumber, int secondRowNumber); //get pivots
    void rowReduce(matrix* matrix, int firstRowNumber, int secondRowNumber); //row reduce one row at a time
    void rowReduceComplete(matrix*); //this will contain a loop to row reduce the entire matrix
    int findPivot(matrix*, int rowNumber); //find the first nonzero row number that we will need to reduce
*/
    
    float currentPivot;
    for (int i = 0; i < rows; i++) //to do: make sure we keep row reducing until done! Multiple passes
    {
        //to add: method to figure out if we need a row swap
        currentPivot = findPivot(matrix, i); //this will find the pivot on 0-based row i
        if ((i + 1)<rows) //if i+1 is in the bounds of the matrix
        {
            //do we need to row reduce?
            if (rowReduceNeeded(matrix, i+1))
            {
                float leadingNumber = getLeadingNumber(matrix, i+1);
                float pivotMultiplier = leadingNumber / currentPivot;
                reduceRow(matrix, i, i+1, pivotMultiplier); //multiply first row by pivot multiplier, then subtract from second
            }
        }
    }
    return matrix;
}

int** squareMatrixMult(int matrix1[MAXSIZE][MAXSIZE], int matrix2[MAXSIZE][MAXSIZE], int rows, int cols)
{
    /* This function will multiply two matrices together using dot products
     row 1 dotted with column 1, row 1 dotted with column 2, row 1 dotted with column 3
     row 2 dotted with column 2, row 2 dotted with column 2, row 2 dotted with column 3
     row 3 dotted with column 1, row 3 dotted with column 2, row 3 dotted with column 3
     [3 4 3  [2 1 2    [6+12+3
     2 6 8    3 1 2
     3 6 4]   1 1 1]
     
     Loop thru first row of matrix 1 (each entry is a j)
    */
    
    int outputMatrix[MAXSIZE][MAXSIZE];
    
    for (int i =0; i < rows; i++)
    {
        for (int colCount = 0; colCount < cols; colCount++)
        {
            int newValue = 0;
            int colCount = 0;
            //for each row of matrix 1, multiply it with column 1 of matrix 2
            for (int j=0; j < cols; j++)
            {
                newValue+= matrix1[i][j]*matrix2[j][colCount];
            }
            outputMatrix[i][colCount] = newValue;
        }
    }
}



void printMatrix(int matrix[MAXSIZE][MAXSIZE], int rows, int cols)
{
    for (int i=0; i < rows; i++)
    {
        for (int j=0; j < cols; j++)
        {
            printf("%d ", matrix[i][j]);
        }
        printf("\n");
    }
}

