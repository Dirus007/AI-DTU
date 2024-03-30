#include <iostream>
#include <vector>
#include <random>
using namespace std;

struct Move {
    int row, col;
};

char board[3][3] = {{'_', '_', '_'}, {'_', '_', '_'}, {'_', '_', '_'}};

bool isMovesLeft(char board[3][3]) {
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            if(board[i][j] == '_')
                return true;
    return false;
}

bool checkWin(char player, char board[3][3]) {
    // Check all rows, columns, and diagonals for a win
    for(int i = 0; i < 3; i++)
        if(board[i][0] == player && board[i][1] == player && board[i][2] == player) return true;
    for(int i = 0; i < 3; i++)
        if(board[0][i] == player && board[1][i] == player && board[2][i] == player) return true;
    if(board[0][0] == player && board[1][1] == player && board[2][2] == player) return true;
    if(board[0][2] == player && board[1][1] == player && board[2][0] == player) return true;
    return false;
}

Move findBestMove(char board[3][3], char computerChar, char humanChar) {
    Move bestMove = {-1, -1};

    // Check if a move can win the game
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(board[i][j] == '_') {
                board[i][j] = computerChar;
                if(checkWin(computerChar, board)) return {i, j};
                board[i][j] = '_';
            }
        }
    }

    // Check if opponent is winning and block
    for(int i = 0; i < 3; i++) {
        for(int j = 0; j < 3; j++) {
            if(board[i][j] == '_') {
                board[i][j] = humanChar;
                if(checkWin(humanChar, board)) return {i, j};
                board[i][j] = '_';
            }
        }
    }

    // If no immediate win or block, choose a random free space
    vector<Move> freeSpaces;
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(board[i][j] == '_') freeSpaces.push_back({i, j});
        }
    }

    if(!freeSpaces.empty()){
        random_device rd;
        mt19937 rng(rd());
        uniform_int_distribution<int> uni(0, freeSpaces.size() - 1);
        return freeSpaces[uni(rng)];
    }

    return bestMove; // No move available
}

void printBoard(char board[3][3]) {
    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            cout << board[i][j] << " ";
        }
        cout << "\n";
    }
}

int main() {
    int turn = 0; // 0 for human, 1 for computer
    while (isMovesLeft(board) && !checkWin('x', board) && !checkWin('o', board)) {
        printBoard(board);
        if (turn == 0) {
            cout << "Your turn. Enter row (0-2) and column (0-2): ";
            int row, col;
            cin >> row >> col;
            if (row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == '_') {
                board[row][col] = 'o'; // Human is 'o'
                turn = 1;
            } 
            else cout << "Invalid move. Try again.\n";
        }
        else{
            cout << "Computer's turn...\n";
            Move bestMove = findBestMove(board, 'x', 'o');
            if(bestMove.row != -1) board[bestMove.row][bestMove.col] = 'x'; // Computer is 'x'
            turn = 0;
        }
    }

    printBoard(board);
    if(checkWin('x', board)) cout << "Computer wins!\n";
    else if (checkWin('o', board)) cout << "You win!\n";
    else cout << "It's a draw!\n";

    return 0;
}
