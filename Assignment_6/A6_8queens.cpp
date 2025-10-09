#include <bits/stdc++.h>
using namespace std;

const int N = 8;  // Board size (8x8)

// Utility to print the chessboard
void print_board(vector<vector<int>>& board) {
    for (int i = 0; i < N; i++) {
        for (int j = 0; j < N; j++) {
            cout << (board[i][j] == 1 ? "Q " : ". ");
        }
        cout << "\n";
    }
    cout << "\n";
}

// Check if a queen can be placed at board[row][col]
bool is_safe(vector<vector<int>>& board, int row, int col) {
    // Check this column
    for (int i = 0; i < row; i++) {
        if (board[i][col] == 1)
            return false;
    }

    // Check upper-left diagonal
    for (int i = row - 1, j = col - 1; i >= 0 && j >= 0; i--, j--) {
        if (board[i][j] == 1)
            return false;
    }

    // Check upper-right diagonal
    for (int i = row - 1, j = col + 1; i >= 0 && j < N; i--, j++) {
        if (board[i][j] == 1)
            return false;
    }

    return true;
}

// Backtracking algorithm to solve N-Queens
bool solve_nqueens(vector<vector<int>>& board, int row = 0) {
    if (row == N) {  // All queens placed
        cout << "Solution found:\n";
        print_board(board);
        return true; // if you want only 1 solution
        // return false; // if you want all solutions
    }

    for (int col = 0; col < N; col++) {
        if (is_safe(board, row, col)) {
            board[row][col] = 1; // Place queen
            if (solve_nqueens(board, row + 1))
                return true;    // if only 1 solution needed
            board[row][col] = 0; // Backtrack
        }
    }

    return false;
}

int main() {
    vector<vector<int>> board(N, vector<int>(N, 0));

    if (!solve_nqueens(board)) {
        cout << "No solution exists\n";
    }

    return 0;
}
