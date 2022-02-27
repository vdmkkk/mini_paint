#include "mini_paint.h"

void rect_full (vector <vector <char>> &board, vector <string> command) {
    int x = stringToInt(command[1]);
    int y = stringToInt(command[2]);
    int width = stringToInt(command[3]);
    int height = stringToInt(command[4]);
    char symb = (char) command[5][0];
    for (int i = y; i < y + height; i++) for (int j = x; j < x + width; j++){
    //cout << "YE " << i << " " << j << endl;
    board[i][j] = symb;
    }
}

void rect(vector <vector <char>> &board, vector <string> command) {
    int x = stringToInt(command[1]);
    int y = stringToInt(command[2]);
    int width = stringToInt(command[3]);
    int height = stringToInt(command[4]);
    char symb = (char) command[5][0];
    for (int i = x; i < x + width; i++){
        board[y][i] = symb;
        board[y + height - 1][i] = symb;
    }
    for (int i = y; i < y + height; i++){
        board[i][x] = symb;
        board[i][x + width - 1] = symb;
    }
}

void circle (vector <vector <char>> &board, vector <string> command) {
    int x = stringToInt(command[1]);
    int y = stringToInt(command[2]);
    int radius = stringToInt(command[3]);
    char symb = (char) command[4][0];
    int x1 = radius;
    int y1 = 0;
    int radiusError = 1 - radius;
    while (x1 >= y1)
    {
        board[y1 + y][x1 + x] = symb;
        board[x1 + y][y1 + x] = symb;
        board[y1 + y][-x1 + x] = symb;
        board[x1 + y][-y1 + x] = symb;
        board[-y1 + y][-x1 + x] = symb;
        board[-x1 + y][-y1 + x] = symb;
        board[-y1 + y][x1 + x] = symb;
        board[-x1 + y][y1 + x] = symb;
        y1++;
        if (radiusError < 0)
        {
            radiusError += 2 * y1 + 1;
        }
        else
        {
            x1--;
            radiusError += 2 * (y1 - x1 + 1);
        }
    }
}

void circle_full (vector <vector <char>> &board, vector <string> command) {
    int x = stringToInt(command[1]);
    int y = stringToInt(command[2]);
    int radius = stringToInt(command[3]);
    char symb = (char) command[4][0];
    for (int i = -radius; i < radius; i++) {
        int half_row_width = sqrt((radius * radius) - (i * i));
        for (int j = -half_row_width; j < half_row_width; j++){
            board[y + i][x + j] = symb;
        }
    }
}

void line (vector <vector <char>> &board, vector <string> command) {
    int x1 = stringToInt(command[1]);
    int y1 = stringToInt(command[2]);
    int x2 = stringToInt(command[3]);
    int y2 = stringToInt(command[4]);
    char symb = (char) command[5][0];

    float dx = x2 - x1;
    float dy = y2 - y1;
    float k = dy / dx;

    int y = 0;
    for (int x = 0; x < dx; x++) {
        y = round(k * x);
        board[y + y1][x + x1] = symb;
    }
}
