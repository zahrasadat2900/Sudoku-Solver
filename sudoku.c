#include <stdio.h>
#include <stdlib.h>

#define N 9          // Size of the Sudoku grid
#define SUBGRID_SIZE 3 // Size of the subgrid

/* A utility function to print the grid */
void printGrid(int grid[N][N]) {
    for (int row = 0; row < N; row++) {
        for (int col = 0; col < N; col++)
            printf("%d ", grid[row][col]);
        printf("\n");
    }
}

// Checks if it is legal to assign num to the given row, col
int isSafe(int grid[N][N], int row, int col, int num) {
    // Check the same row and column
    for (int i = 0; i < N; i++) {
        if (grid[row][i] == num || grid[i][col] == num) {
            return 0; // Not safe
        }
    }

    // Check the 3x3 subgrid
    int startRow = row - row % SUBGRID_SIZE;
    int startCol = col - col % SUBGRID_SIZE;
    for (int i = 0; i < SUBGRID_SIZE; i++) {
        for (int j = 0; j < SUBGRID_SIZE; j++) {
            if (grid[i + startRow][j + startCol] == num) {
                return 0; // Not safe
            }
        }
    }

    return 1; // Safe to place num
}

/* Solves the Sudoku puzzle using backtracking */
int solveSudoku(int grid[N][N], int row, int col) {
    // If we reach the end of the grid, return success
    if (row == N - 1 && col == N) {
        return 1;
    }

    // Move to the next row if we reach the end of the current column
    if (col == N) {
        row++;
        col = 0;
    }

    // If the cell is already filled, move to the next column
    if (grid[row][col] > 0) {
        return solveSudoku(grid, row, col + 1);
    }

    // Try placing numbers from 1 to 9
    for (int num = 1; num <= N; num++) {
        if (isSafe(grid, row, col, num)) {
            grid[row][col] = num; // Place num

            // Recur to place next numbers
            if (solveSudoku(grid, row, col + 1)) {
                return 1; // Success
            }
        }

        // Backtrack
        grid[row][col] = 0;
    }

    return 0; // Trigger backtracking
}

int main() {
    // 0 means unassigned cells
    int grid[N][N] = {
        {3, 0, 6, 5, 0, 8, 4, 0, 0},
        {5, 2, 0, 0, 0, 0, 0, 0, 0},
        {0, 8, 7, 0, 0, 0, 0, 3, 1},
        {0, 0, 3, 0, 1, 0, 0, 8, 0},
        {9, 0, 0, 8, 6, 3, 0, 0, 5},
        {0, 5, 0, 0, 9, 0, 6, 0, 0},
        {1, 3, 0, 0, 0, 0, 2, 5, 0},
        {0, 0, 0, 0, 0, 0, 0, 7, 4},
        {0, 0, 5, 2, 0, 6, 3, 0, 0}
    };

    if (solveSudoku(grid, 0, 0)) {
        printf("Solved Sudoku:\n");
        printGrid(grid);
    } else {
        printf("No solution exists\n");
    }

    return 0;
}

