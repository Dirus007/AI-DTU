#include <iostream>
#include <vector>
#include <climits>
using namespace std;

struct Move {
    int row, col;
};

bool isMovesLeft(char b[3][3]) {
    for(int i = 0; i < 3; i++)
        for(int j = 0; j < 3; j++)
            if(b[i][j] == '_')
                return true;
    return false;
}

int evaluate(char b[3][3]) {
    // Checking for Rows for X or O victory.
    for(int row = 0; row < 3; row++){
        if(b[row][0] == b[row][1] && b[row][1] == b[row][2]){
            if(b[row][0] == 'x') return +100;
            else if(b[row][0] == 'o') return -100;
        }
    }
    // Checking for Columns for X or O victory.
    for(int col = 0; col < 3; col++){
        if(b[0][col] == b[1][col] && b[1][col] == b[2][col]){
            if(b[0][col] == 'x') return +100;
            else if(b[0][col] == 'o') return -100;
        }
    }
    // Checking for Diagonals for X or O victory.
    if(b[0][0] == b[1][1] && b[1][1] == b[2][2]){
        if(b[0][0] == 'x') return +100;
        else if(b[0][0] == 'o') return -100;
    }
    if(b[0][2] == b[1][1] && b[1][1] == b[2][0]){
        if(b[0][2] == 'x') return +100;
        else if(b[0][2] == 'o') return -100;
    }
    return 0; // No winner yet
}

pair<int, Move> minimax(char b[3][3], bool isMax, int depth) {
    int score = evaluate(b);
    Move bestMove{-1, -1};

    if(score == 100) return make_pair(score - depth, bestMove);
    if(score == -100) return make_pair(score + depth, bestMove);
    if(!isMovesLeft(b)) return make_pair(0, bestMove);

    int bestVal = isMax ? -1e5 : +1e5 ;

    for(int i = 0; i < 3; i++){
        for(int j = 0; j < 3; j++){
            if(b[i][j] == '_'){
                b[i][j] = isMax ? 'x' : 'o' ;

                int moveVal = minimax(b, !isMax, depth+1).first;

                b[i][j] = '_';
                if((isMax && moveVal>bestVal) || (!isMax && moveVal<bestVal)) bestMove.row = i, bestMove.col = j, bestVal = moveVal;
            }
        }
    }
    return make_pair(bestVal, bestMove);
}

void printBoard(char b[3][3]) {
    for (int i = 0; i < 3; i++) {
        for (int j = 0; j < 3; j++) {
            cout << b[i][j] << " ";
        }
        cout << "\n";
    }
}

int main() {
    int turn = 0; // 0 for human, 1 for computer
    char board[3][3] = {{'_', '_', '_'}, {'_', '_', '_'}, {'_', '_', '_'}};
    while(isMovesLeft(board) && evaluate(board) == 0){
        printBoard(board);
        if(turn == 0){
            cout << "Your turn. Enter row (0-2) and column (0-2): ";
            int row, col;
            cin >> row >> col;
            if(row >= 0 && row < 3 && col >= 0 && col < 3 && board[row][col] == '_'){
                board[row][col] = 'o'; // Human is 'o'
                turn = 1;
            } 
            else cout << "Invalid move. Try again.\n";
        } 
        else{
            cout << "Computer's turn...\n";
            Move bestMove = minimax(board, true, 0).second;
            board[bestMove.row][bestMove.col] = 'x'; // Computer is 'x'
            turn = 0;
        }
    }

    printBoard(board);
    int score = evaluate(board);
    if(score == 100) cout << "Computer wins!\n";
    else if(score == -100) cout << "You win!\n";
    else cout << "It's a draw!\n";

    return 0;
}
