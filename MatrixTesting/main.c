//
//  main.c
//  MatrixTesting
//
//  Created by Justin Roll on 1/19/13.
//  Copyright (c) 2013 Justin Roll. All rights reserved.
//

#include <stdio.h>

#define MAXSIZE 3
void matrixMultByScalar(float matrix[MAXSIZE][MAXSIZE], int scalar, int rows, int cols);
void printMatrix(float matrix[MAXSIZE][MAXSIZE], int rows, int cols);
int rowReduceNeeded(float matrix[MAXSIZE][MAXSIZE], int row);
void rowReduce(float matrix[MAXSIZE][MAXSIZE], int rows, int cols);
void swapRow(float matrix[MAXSIZE][MAXSIZE], int row1, int row2, int entries);
float findPivot(float matrix[MAXSIZE][MAXSIZE], int row, int columns);
float getLeadingNumber(float matrix[MAXSIZE][MAXSIZE], int row, int columns);
void reduceRow(float matrix[MAXSIZE][MAXSIZE], int firstRow, int secondRow, float pivotMultiplier);
void squareMatrixMult(float matrix1[MAXSIZE][MAXSIZE], float matrix2[MAXSIZE][MAXSIZE],
                      float outputMatrix[MAXSIZE][MAXSIZE], int rows, int cols);
float getDeterminant2by2(float matrix[MAXSIZE][MAXSIZE]);
float getPivotsAndMultiply(float matrix[MAXSIZE][MAXSIZE], int rows, int cols);

int main(int argc, const char * argv[])
{
    int n;
    float m1[MAXSIZE] [MAXSIZE];
    float m2[MAXSIZE][MAXSIZE];
    float m3[MAXSIZE][MAXSIZE]; //m3 is just the output matrix
    
    m1[0][0] = 1;    m1[0][1] = 3;    m1[0][2] = 5;
    m1[1][0] = 2;    m1[1][1] = 6;    m1[1][2] = 10;
    m1[2][0] = 3;    m1[2][1] = 9;   m1[2][2] = 15;

    m2[0][0] = 1;    m2[0][1] = 3;    m2[0][2] = 5;
    m2[1][0] = 1;    m2[1][1] = 6;    m2[1][2] = 10;
    m2[2][0] = 0;    m2[2][1] = 0;   m2[2][2] = 3;


    //multiply matrix m1 by a scalar
    matrixMultByScalar(m1, 2, 3, 3); //multiply this 3x3 matrix by a scalar of 2
    
    squareMatrixMult(m1, m2, m3, 3, 3); // multiply m1 and m2 into matrix m3
    printMatrix(m3, 3, 3);
    swapRow(m3, 1, 2, 3);
    printMatrix(m3, 3, 3);
    return 0;
}

/*
 [1 3 5  [1 3 5    [4 19 50
  2 6 10  1 6 10    8 42 100
  3 9 15] 0 0 3]   12 54 150
 */

void swapRow(float matrix[MAXSIZE][MAXSIZE], int row1, int row2, int entries)
{
    /* this method will swap row1 and row2 in the matrix */
    float swapArray[entries];
    
    for (int i=0; i < entries; i++)
    {
        swapArray[i] = matrix[row2][i]; //copy off the entries in row 2, since we are going to overrite them
        matrix[row2][i] = matrix[row1][i];
        matrix[row1][i] = swapArray[i];
    }
}

float findPivot(float matrix[MAXSIZE][MAXSIZE], int row, int columns)
{
    /* This is a function for finding the pivot in a first row.
     Cases we need to handle
     If there is no pivot, return 0, which is basically false
     0 0 0 
     0 1 0
     0 0 1
     */
    float leadingNumb = getLeadingNumber(matrix, row, columns);
    return leadingNumb;
}

float getLeadingNumber(float matrix[MAXSIZE][MAXSIZE], int row, int columns)
{
    //get first nonzero number
    for (int j = 0; j < columns; j++)
    {
        if (matrix[row][j] != 0)
            return matrix[row][j];
    }
    return 0;
}

float getPivotsAndMultiply(float matrix[MAXSIZE][MAXSIZE], int rows, int cols)
{
        //dummy method. to finish later!
    return 3.0;
}

float multiplyDiagonals(float matrix[MAXSIZE][MAXSIZE], int rows, int cols)
{
    /* If pivots arent along the diagonals, then we'll have a free column
     */
    float pivotMult = 0;
    for (int i = 0; i < rows; i++)
    {
        if (i==0)
            pivotMult = matrix[i][0];
        else
            pivotMult = pivotMult*matrix[i][i];
        
    }
    return pivotMult;
}

int rowReduceNeeded(float matrix[MAXSIZE][MAXSIZE], int row)
{
    /* With this function, we try and figure out if row reduction is needed.
       If the matrix has N rows, and the first row is not something like 0 0 0
        then use the first row and compare it to the 2nd row, 3rd row, etc. Find
     a column multiplier and then row reduce the other columns now, swapping them if 
     needed.
     
     */
    return 0;
}

void reduceRow(float matrix[MAXSIZE][MAXSIZE], int firstRow, int secondRow, float pivotMultiplier)
{
        //dummy method. to finish later!
}
void matrixMultByScalar(float matrix[MAXSIZE][MAXSIZE], int scalar, int rows, int cols)
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

float getDeterminant(float matrix[MAXSIZE][MAXSIZE], int rows, int cols)
{
    if (cols > rows) //if we have a free variable
        return 0;
    else if ((cols == 2) && (rows == 2)) //if this is a 2x2 matrix, use ad-bc
        getDeterminant2by2(matrix);
    else
    {
        rowReduce(matrix, rows, cols);
        return (getPivotsAndMultiply(matrix, rows, cols)); //return the multiples of the pivots of the row reduced matrix
    }
}

float getDeterminant2by2(float matrix[MAXSIZE][MAXSIZE])
{
    /* Given a 2x2 Matrix of
     [a  b
      c  d]
     return ad - bc
     */
    return (matrix[0][0]*matrix[1][1]) - (matrix[0][1]*matrix[1][0]);
}

void rowReduce(float matrix[MAXSIZE][MAXSIZE], int rows, int cols)
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
    void rowReduce(matrix* matrix, int firstRowNumber, int secondRowNumber); //subtract one row from another
    void rowReduceComplete(matrix*); //this will contain a loop to row reduce the entire matrix
    int findPivot(matrix*, int rowNumber); //find the first nonzero row number that we will need to reduce
*/
    
    float currentPivot;
    for (int i = 0; i < rows; i++) //to do: make sure we keep row reducing until done! Multiple passes
    {
        //to add: method to figure out if we need a row swap
        currentPivot = findPivot(matrix, i, cols); //this will find the pivot on 0-based row i
        if ((i + 1)<rows) //if i+1 is in the bounds of the matrix
        {
            //do we need to row reduce?
            if (rowReduceNeeded(matrix, i+1))
            {
                float leadingNumber = getLeadingNumber(matrix, i+1, cols);
                float pivotMultiplier = leadingNumber / currentPivot;
                reduceRow(matrix, i, i+1, pivotMultiplier); //multiply first row by pivot multiplier, then subtract from second
            }
        }
    }
}

void squareMatrixMult(float matrix1[MAXSIZE][MAXSIZE], float matrix2[MAXSIZE][MAXSIZE],
                      float outputMatrix[MAXSIZE][MAXSIZE], int rows, int cols)
{
    /* This function will multiply two matrices together using dot products
     row 1 dotted with column 1, row 1 dotted with column 2, row 1 dotted with column 3
     row 2 dotted with column 2, row 2 dotted with column 2, row 2 dotted with column 3
     row 3 dotted with column 1, row 3 dotted with column 2, row 3 dotted with column 3
     [3 4 3  [2 1 2    [6+12+3
     2 6 8    3 1 2
     3 6 4]   1 1 1]
     
     Loop thru first row of matrix 1 (each entry is a j)
     
     for each row of matrix1
        for each column of matrix1 
     
     matrix1[0][0] * matrix2[0][0] + matrix1[0][1]*matrix2[1][0] + matrix1[0][2]*matrix2[2][0]
     m1[0][0] * m2[0][1] + m1[0][1] * m2[1][1] + m1[0][2] * m2[2][1]
     row1 * column1, row1 * column 2, row1 * column 3
    */
    
    for (int i = 0; i < rows; i++)
    {
        //want to dot each row of matrix 1 with a column of matrix 2, this will make an entry
        //in the output matrix
        for (int outColumn = 0; outColumn < cols; outColumn++) {
            float newValue = 0;
            
            for (int j = 0; j < cols; j++) //j in this case is cols of matrix 1
            {
                newValue+=(matrix1[i][j] * matrix2[j][outColumn]);
            }
            outputMatrix[i][outColumn] = newValue; //output row/column = the row and column dotted
        }
    }
 }

void printMatrix(float matrix[MAXSIZE][MAXSIZE], int rows, int cols)
{
    for (int i=0; i < rows; i++)
    {
        for (int j=0; j < cols; j++)
        {
            printf("%f ", matrix[i][j]);
        }
        printf("\n");
    }
}

