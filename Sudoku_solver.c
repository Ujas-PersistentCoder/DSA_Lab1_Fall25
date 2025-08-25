#include <stdio.h>
#include <stdbool.h>

/**
 * @brief Checks if placing a number 'x' at (r, c) is valid by Sudoku rules.
 * @return True if the move is valid, otherwise false.
 */
bool is_valid(int sudoku[9][9], int r, int c, int x) {
    // Check row and column.
    for (int i = 0; i < 9; i++) {
        if (sudoku[i][c] == x) return false;
        if (sudoku[r][i] == x) return false;
    }

    // Check the 3x3 sub-grid.
    int rsc = (r / 3) * 3;
    int csc = (c / 3) * 3;
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            if (sudoku[rsc + i][csc + j] == x) return false;
        }
    }
    return true;
}

/**
 * @brief Finds the next empty cell (0) in the grid.
 * @param next_r Pointer to store the row of the empty cell.
 * @param next_c Pointer to store the column of the empty cell.
 * @return True if an empty cell is found, otherwise false.
 */
bool find_next_empty(int sudoku[9][9], int *next_r, int *next_c) {
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) {
            if (sudoku[i][j] == 0) {
                *next_r = i;
                *next_c = j;
                return true;
            }
        }
    }
    return false;
}

/**
 * @brief Solves the Sudoku puzzle in-place using backtracking.
 * @return True if a solution is found, otherwise false.
 */
bool sudoku_solver(int sudoku[9][9]) {
    int next_r, next_c;

    // Base Case: If no empty cells are left, the puzzle is solved.
    if (!find_next_empty(sudoku, &next_r, &next_c)) return true;

    // Try placing numbers 1 through 9 in the empty cell.
    for (int num = 1; num <= 9; num++) {
        if (is_valid(sudoku, next_r, next_c, num)) {
            // Tentatively place the number.
            sudoku[next_r][next_c] = num;

            // Recurse to solve the rest of the puzzle.
            if (sudoku_solver(sudoku)) return true;

            // If the guess didn't lead to a solution, undo it.
            sudoku[next_r][next_c] = 0; // Backtrack!
        }
    }
    return false; // No number worked, trigger backtracking in the previous call.
}

int main() {
    int sudoku[9][9];
    for (int i = 0; i < 9; i++) {
        for (int j = 0; j < 9; j++) scanf("%d", &sudoku[i][j]);
    }

    if (sudoku_solver(sudoku)) {
        for (int i = 0; i < 9; i++) {
            for (int j = 0; j < 9; j++) printf("%d ", sudoku[i][j]);
            printf("\n");
        }
    }

    return 0;
}
