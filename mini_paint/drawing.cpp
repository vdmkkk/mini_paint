#include "mini_paint.h"

void rect_full (vector <vector <char>> &board, vector <string> command) {
    if (command.size() != 6) throw invalid_argument("WRONG AMOUNT OF ARGUMENTS");
    int x = stringToInt(command[1]);
    int y = stringToInt(command[2]);
    int width = stringToInt(command[3]);
    int height = stringToInt(command[4]);
    char symb = (char) command[5][0];
    for (int i = y; i < y + height; i++) for (int j = x; j < x + width; j++){
    if (i < board.size() && i >= 0 && j < board[i].size() && j >= 0) board[i][j] = symb;
    }
}

void rect(vector <vector <char>> &board, vector <string> command) {
    if (command.size() != 6) throw invalid_argument("WRONG AMOUNT OF ARGUMENTS");
    int x = stringToInt(command[1]);
    int y = stringToInt(command[2]);
    int width = stringToInt(command[3]);
    int height = stringToInt(command[4]);
    char symb = (char) command[5][0];
    for (int i = x; i < x + width; i++){
        if (y < board.size() && y >= 0 && i < board[y].size() && i >= 0) board[y][i] = symb;
        if (y + height - 1 < board.size() && y + height - 1 >= 0 && i < board[y + height - 1].size() && i >= 0) board[y + height - 1][i] = symb;
    }
    for (int i = y; i < y + height; i++){
        if (i < board.size() && i >= 0 && x < board[i].size() && x >= 0) board[i][x] = symb;
        if (i < board.size() && i >= 0 && x + width - 1 < board[i].size() && x + width - 1 >= 0) board[i][x + width - 1] = symb;
    }
}

void circle (vector <vector <char>> &board, vector <string> command) {
    if (command.size() != 5) throw invalid_argument("WRONG AMOUNT OF ARGUMENTS");
    int x = stringToInt(command[1]);
    int y = stringToInt(command[2]);
    int radius = stringToInt(command[3]);
    char symb = (char) command[4][0];
    if (radius == 0) return;
    int x1 = radius;
    int y1 = 0;
    int radiusError = 1 - radius;
    while (x1 >= y1)
    {
        if (y1 + y < board.size() && y1 + y >= 0 && x1 + x < board[y1 + y].size() && x1 + x >= 0) board[y1 + y][x1 + x] = symb;
        if (x1 + y < board.size() && x1 + y >= 0 && y1 + x < board[x1 + y].size() && y1 + x >= 0) board[x1 + y][y1 + x] = symb;
        if (y1 + y < board.size() && y1 + y >= 0 && -x1 + x < board[y1 + y].size() && -x1 + x >= 0) board[y1 + y][-x1 + x] = symb;
        if (x1 + y < board.size() && x1 + y >= 0 && -y1 + x < board[x1 + y].size() && -y1 + x >= 0) board[x1 + y][-y1 + x] = symb;
        if (-y1 + y < board.size() && -y1 + y >= 0 && -x1 + x < board[-y1 + y].size() && -x1 + x >= 0) board[-y1 + y][-x1 + x] = symb;
        if (-x1 + y < board.size() && -x1 + y >= 0 && -y1 + x < board[-x1 + y].size() && -y1 + x >= 0) board[-x1 + y][-y1 + x] = symb;
        if (-y1 + y < board.size() && -y1 + y >= 0 && x1 + x < board[-y1 + y].size() && x1 + x >= 0) board[-y1 + y][x1 + x] = symb;
        if (-x1 + y < board.size() && -x1 + y >= 0 && y1 + x < board[-x1 + y].size() && y1 + x >= 0) board[-x1 + y][y1 + x] = symb;
        y1++;
        if (radiusError < 0) ú  {
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
    if (command.size() != 5) throw invalid_argument("WRONG AMOUNT OF ARGUMENTS");
    int x = stringToInt(command[1]);
    int y = stringToInt(command[2]);
    int radius = stringToInt(command[3]) + 1;
    char symb = (char) command[4][0];
    for (int i = -radius; i < radius; i++) {
        int half_row_width = sqrt((radius * radius) - (i * i));
        for (int j = -half_row_width; j < half_row_width; j++){
            if (!(i == 0 && j == -half_row_width) && !(i == 0 && j == half_row_width - 1)) board[y + i][x + j] = symb;

        }
    }
}

void line (vector <vector <char>> &board, vector <string> command) {
    if (command.size() != 6) throw invalid_argument("WRONG AMOUNT OF ARGUMENTS");
    int x1 = stringToInt(command[1]);
    int y1 = stringToInt(command[2]);
    int x2 = stringToInt(command[3]) + 1;
    int y2 = stringToInt(command[4]) + 1;
    char symb = (char) command[5][0];

    float dx = x2 - x1;
    float dy = y2 - y1;
    float k = dy / dx;


    if (k <= 0.5 && k >= 0 && dy != 0) {dy = dy - 1; k = dy / dx;}
    if (dx == 0) {
        for (int y = 0; y < dy; y++){
            if (y + y1 < board.size() && x1 < board[y + y1].size() && x1 >= 0 && y1 + y >= 0) board[y + y1][x1] = symb;
        }
    }

    int y = 0;
    for (int x = 0; x < dx; x++) {
        y = round(k * x);
        if (y + y1 < board.size() && x + x1 < board[y + y1].size() && x1 + x >= 0 && y1 + y >= 0) board[y + y1][x + x1] = symb;
    }
}
