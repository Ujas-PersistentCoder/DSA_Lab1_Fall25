#include <stdio.h>
#include <stdlib.h>
#include <stdbool.h>

// Represents a coordinate pair.
typedef struct {
    int x;
    int y;
} pair;

// Checks if a square (r, c) is on the board and unvisited.
bool is_valid(int n, int m, int board[n][m], int r, int c) {
    return r >= 0 && r < n && c >= 0 && c < m && board[r][c] == 0;
}

// Counts the number of valid onward moves from a given square (r, c).
int move_count(int n, int m, int board[n][m], int r, int c) {
    int rc[8] = {-2, -2, -1, -1, 1, 1, 2, 2};
    int cc[8] = {1, -1, 2, -2, 2, -2, 1, -1};
    int cnt = 0;
    for (int i = 0; i < 8; i++) {
        if (is_valid(n, m, board, r + rc[i], c + cc[i])) cnt++;
    }
    return cnt;
}

// Finds and sorts next moves according to Warnsdorff's rule.
pair* get_sorted_moves(int n, int m, int board[n][m], int r, int c, int *cnt) {
    int rc[8] = {-2, -2, -1, -1, 1, 1, 2, 2};
    int cc[8] = {1, -1, 2, -2, 2, -2, 1, -1};
    pair moves[8];
    int deg[8]; // Degree: number of onward moves from each potential next square.
    *cnt = 0;

    // Find all valid moves and calculate their degrees.
    for (int i = 0; i < 8; i++) {
        int nr = r + rc[i];
        int nc = c + cc[i];
        if (is_valid(n, m, board, nr, nc)) {
            moves[*cnt] = (pair){nr, nc};
            deg[*cnt] = move_count(n, m, board, nr, nc);
            (*cnt)++;
        }
    }

    // Sort moves in ascending order of their degree.
    for (int i = 0; i < *cnt - 1; i++) {
        for (int j = i + 1; j < *cnt; j++) {
            if (deg[j] < deg[i]) {
                int tmpdeg = deg[i]; deg[i] = deg[j]; deg[j] = tmpdeg;
                pair tmp = moves[i]; moves[i] = moves[j]; moves[j] = tmp;
            }
        }
    }

    pair* sorted_moves = malloc(*cnt * sizeof(pair));
    for (int i = 0; i < *cnt; i++) sorted_moves[i] = moves[i];
    return sorted_moves;
}

/**
 * @brief Recursive backtracking function to find a knight's tour.
 * @param r, c The original starting coordinates.
 * @param move The current move number.
 * @param cur_r, cur_c The knight's current coordinates.
 * @return True if a closed tour is found, otherwise false.
 */
bool knights_closed_tour(int n, int m, int board[n][m], int r, int c, int move, int cur_r, int cur_c) {
    // Base Case: All squares are visited.
    if (move == n * m) {
        // Check if the tour can be closed by returning to the start.
        int rc[8] = {-2, -2, -1, -1, 1, 1, 2, 2};
        int cc[8] = {1, -1, 2, -2, 2, -2, 1, -1};
        for (int i = 0; i < 8; i++) {
            if (cur_r + rc[i] == r && cur_c + cc[i] == c) return true;
        }
        return false;
    }

    // Get next moves, sorted by Warnsdorff's rule.
    int cnt;
    pair* next_moves = get_sorted_moves(n, m, board, cur_r, cur_c, &cnt);

    // Try each move recursively.
    for (int i = 0; i < cnt; i++) {
        int nr = next_moves[i].x;
        int nc = next_moves[i].y;
        board[nr][nc] = move + 1;
        if (knights_closed_tour(n, m, board, r, c, move + 1, nr, nc)) {
            free(next_moves);
            return true; // Solution found.
        }
        board[nr][nc] = 0; // Backtrack.
    }

    free(next_moves);
    return false; // No solution from this path.
}

int main() {
    int n, m, r, c;
    scanf("%d %d %d %d", &n, &m, &r, &c);

    // A closed tour is impossible if the number of squares is odd.
    if ((n * m) % 2 != 0) {
        printf("-1");
        return 0;
    }

    int board[n][m];
    for (int i = 0; i < n; i++) {
        for (int j = 0; j < m; j++) {
            board[i][j] = 0;
        }
    }

    board[r][c] = 1;
    if (knights_closed_tour(n, m, board, r, c, 1, r, c)) {
        for (int i = 0; i < n; i++) {
            for (int j = 0; j < m; j++) {
                printf("%d ", board[i][j]);
            }
            printf("\n");
        }
    } else {
        printf("-1");
    }
    return 0;
}
