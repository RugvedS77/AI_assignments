#include <bits/stdc++.h>
using namespace std;

const int SIZE = 3;

// Print the board
void print_board(vector<vector<char>>& board) {
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            cout << board[i][j];
            if (j < SIZE - 1) cout << " | ";
        }
        cout << "\n";
    }
    cout << "\n";
}

// Check winner
char check_winner(vector<vector<char>>& board) {
    // Rows
    for (int i = 0; i < SIZE; i++) {
        if (board[i][0] == board[i][1] && board[i][1] == board[i][2] && board[i][0] != '_')
            return board[i][0];
    }
    // Cols
    for (int j = 0; j < SIZE; j++) {
        if (board[0][j] == board[1][j] && board[1][j] == board[2][j] && board[0][j] != '_')
            return board[0][j];
    }
    // Diagonals
    if (board[0][0] == board[1][1] && board[1][1] == board[2][2] && board[0][0] != '_')
        return board[0][0];
    if (board[0][2] == board[1][1] && board[1][1] == board[2][0] && board[0][2] != '_')
        return board[0][2];
    return 0;
}

// Check if board is full
bool is_full(vector<vector<char>>& board) {
    for (auto& row : board)
        for (char c : row)
            if (c == '_')
                return false;
    return true;
}

// Evaluation function
int evaluate(vector<vector<char>>& board) {
    char winner = check_winner(board);
    if (winner == 'X') return 1;   // AI
    if (winner == 'O') return -1;  // Human
    return 0;
}

// Get all possible moves
vector<vector<vector<char>>> get_children(vector<vector<char>>& board, char player) {
    vector<vector<vector<char>>> children;
    for (int i = 0; i < SIZE; i++) {
        for (int j = 0; j < SIZE; j++) {
            if (board[i][j] == '_') {
                auto new_board = board;
                new_board[i][j] = player;
                children.push_back(new_board);
            }
        }
    }
    return children;
}

// Minimax algorithm
pair<int, vector<vector<char>>> minimax(vector<vector<char>>& board, int depth, bool maximizing_player) {
    if (check_winner(board) || is_full(board) || depth == 0) {
        return {evaluate(board), board};
    }

    if (maximizing_player) { // AI = X
        int max_eval = INT_MIN;
        vector<vector<char>> best_board;
        for (auto& child : get_children(board, 'X')) {
            int eval_value = minimax(child, depth - 1, false).first;
            if (eval_value > max_eval) {
                max_eval = eval_value;
                best_board = child;
            }
        }
        return {max_eval, best_board};
    } else { // Human = O
        int min_eval = INT_MAX;
        vector<vector<char>> best_board;
        for (auto& child : get_children(board, 'O')) {
            int eval_value = minimax(child, depth - 1, true).first;
            if (eval_value < min_eval) {
                min_eval = eval_value;
                best_board = child;
            }
        }
        return {min_eval, best_board};
    }
}

int main() {
    vector<vector<char>> board = {
        {'_', '_', '_'},
        {'_', '_', '_'},
        {'_', '_', '_'}
    };

    while (true) {
        print_board(board);

        if (check_winner(board) || is_full(board))
            break;

        // Human move
        int row, col;
        cout << "Enter row and col (0-2): ";
        cin >> row >> col;

        if (row < 0 || row >= 3 || col < 0 || col >= 3) {
            cout << "Invalid input! Try again.\n";
            continue;
        }

        if (board[row][col] == '_') {
            board[row][col] = 'O';
        } else {
            cout << "Cell already taken! Try again.\n";
            continue;
        }

        print_board(board);

        if (check_winner(board) || is_full(board))
            break;

        // AI move
        auto result = minimax(board, 5, true);
        board = result.second;
    }

    char winner = check_winner(board);
    if (winner)
        cout << winner << " wins!\n";
    else
        cout << "It's a draw!\n";

    return 0;
}