#include <stdio.h>
#include <stdlib.h>
#include <ctype.h>

#define BOARD_SIZE 8

char board[BOARD_SIZE][BOARD_SIZE];

void initBoard() {
    char initialBoard[BOARD_SIZE][BOARD_SIZE] = {
        {'r', 'n', 'b', 'q', 'k', 'b', 'n', 'r'},
        {'p', 'p', 'p', 'p', 'p', 'p', 'p', 'p'},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {' ', ' ', ' ', ' ', ' ', ' ', ' ', ' '},
        {'P', 'P', 'P', 'P', 'P', 'P', 'P', 'P'},
        {'R', 'N', 'B', 'Q', 'K', 'B', 'N', 'R'}
    };

    for (int i = 0; i < BOARD_SIZE; i++) {
        for (int j = 0; j < BOARD_SIZE; j++) {
            board[i][j] = initialBoard[i][j];
        }
    }
}

void printBoard() {
    printf("  a b c d e f g h\n");
    for (int i = 0; i < BOARD_SIZE; i++) {
        printf("%d ", 8 - i);
        for (int j = 0; j < BOARD_SIZE; j++) {
            printf("%c ", board[i][j]);
        }
        printf("\n");
    }
}

int isValidMove(char piece, int startX, int startY, int endX, int endY) {
    // Simplified move validation (example for pawns only)
    if (endX < 0 || endX >= BOARD_SIZE || endY < 0 || endY >= BOARD_SIZE) {
        return 0;
    }

    if (startX == endX && startY == endY) {
        return 0;
    }

    char destPiece = board[endX][endY];
    if (destPiece != ' ' && ((isupper(piece) && isupper(destPiece)) || (islower(piece) && islower(destPiece)))) {
        return 0;
    }

    int deltaX = endX - startX;
    int deltaY = endY - startY;

    switch (tolower(piece)) {
        case 'p':
            if (isupper(piece)) { // White pawns
                if (deltaX == -1 && deltaY == 0 && destPiece == ' ') return 1;
                if (startX == 6 && deltaX == -2 && deltaY == 0 && board[startX - 1][startY] == ' ' && destPiece == ' ') return 1;
                if (deltaX == -1 && abs(deltaY) == 1 && islower(destPiece)) return 1;
            } else { // Black pawns
                if (deltaX == 1 && deltaY == 0 && destPiece == ' ') return 1;
                if (startX == 1 && deltaX == 2 && deltaY == 0 && board[startX + 1][startY] == ' ' && destPiece == ' ') return 1;
                if (deltaX == 1 && abs(deltaY) == 1 && isupper(destPiece)) return 1;
            }
            break;
        // Add other pieces (rook, knight, bishop, queen, king) move validation here
        default:
            break;
    }

    return 0;
}

void movePiece(int startX, int startY, int endX, int endY) {
    char piece = board[startX][startY];
    board[endX][endY] = piece;
    board[startX][startY] = ' ';
}

int main() {
    char input[10];
    int startX, startY, endX, endY;
    int turn = 1; // 1 for white, -1 for black

    initBoard();

    while (1) {
        printBoard();

        printf("Player %c, enter your move (e.g., e2 e4): ", turn == 1 ? 'W' : 'B');
        fgets(input, sizeof(input), stdin);

        startX = 8 - (input[1] - '0');
        startY = input[0] - 'a';
        endX = 8 - (input[4] - '0');
        endY = input[3] - 'a';

        char piece = board[startX][startY];

        if ((turn == 1 && isupper(piece)) || (turn == -1 && islower(piece))) {
            if (isValidMove(piece, startX, startY, endX, endY)) {
                movePiece(startX, startY, endX, endY);
                turn = -turn;
            } else {
                printf("Invalid move. Try again.\n");
            }
        } else {
            printf("It's not your turn. Try again.\n");
        }
    }

    return 0;
}
