#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>

using namespace std;


long long itc_abs(long long num){
    if (num >= 0) return num;
    return -num;
}


double itc_pow(long long num, long long n){
    if (n == 0) return 1;
    long long res = num;
    for (int i=1; i < itc_abs(n); i++){
        res *= num;
    }
    if (n >= 0) return res;
    return 1.0 / res;
}

long itc_len(string str) {
    int i = 0;
    while (str[i] != '\0'){
        i += 1;
    }
    return i;
}

string itc_slice_str(string str, int start, int ending){
    if (ending > itc_len(str)) ending = itc_len(str) - 1;
    int i = 0;
    string newstring = "";
    while (str[i] != '\0'){
        if (i >= start && i <= ending){
            newstring += str[i];
        }
        i += 1;

    }
    return newstring;
}


void input(vector <vector <string>> &commands, char* path) {
    ifstream in;
    string line;
    in.open(path);
    while(in.good()){
        vector <string> commandsLine;
        getline(in, line);
        int start = 0;
        for (int i = 0; i < itc_len(line); i++) {
            if (line[i] == ' '){
                commandsLine.push_back(itc_slice_str(line, start, i - 1));
                start = i + 1;
            }
        }
        commandsLine.push_back(itc_slice_str(line, start, itc_len(line) - 1));
        commands.push_back(commandsLine);
    }
    //for (int i = 0; i < commands.size(); i++) for (int j = 0; j < commands[i].size(); j++) cout << "c" << i << ": " << commands[i][j] << endl;

    in.close();
}

int stringToInt(string s) {
    int num = 0;
    for (int i = 0; i < itc_len(s); i++) {
        num += (int(s[i]) - 48) * itc_pow(10, itc_len(s) - i - 1);
    }
    return num;
}

float stringToFloat(string s) {
    float num = 0;
    int i = 0;
    while (s[i] != '.') i++;
    string dec = itc_slice_str(s, 0, i - 1);
    string frac = itc_slice_str(s, i + 1, itc_len(s));
    num += stringToInt(dec);
    num += stringToInt(frac) / itc_pow(10, itc_len(frac));
    return num;
}

void print(vector <vector <char>> board) {
    for (int i = 0; i < board.size(); i++){
        for (int j = 0; j < board[i].size(); j++) cout << board[i][j];
        cout << endl;
    }
}


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
        cout << x << " @ " << y << " @ " << k << endl;
        board[y + y1][x + x1] = symb;
    }
}


int main(int argc, char* argv[]) {
    // catch errors
    if (argc != 2){
        cerr << "Too many / not enough arguments";
        return -1;
    }
    vector <vector <string>> commands;
    input(commands, argv[1]);
    int WIDTH = stringToInt(commands[0][0]);
    int HEIGHT = stringToInt(commands[0][1]);
    char BG_CHAR = (char) commands[0][2][0];

    vector <vector <char>> board;
    vector <char> temp;
    for (int i = 0; i < HEIGHT; i++) {
        temp = {};
        for (int j = 0; j < WIDTH; j++) temp.push_back(BG_CHAR);
        board.push_back(temp);
    }
    //for (int i = 0; i < commands.size(); i++) for (int j = 0; j < commands[i].size(); j++) cout << commands[i][j] << endl;

    for (int i = 1; i < commands.size(); i++) {
        if (commands[i][0] == "r") rect(board, commands[i]);
        if (commands[i][0] == "R") rect_full(board, commands[i]);
        if (commands[i][0] == "c") circle(board, commands[i]);
        if (commands[i][0] == "C") circle_full(board, commands[i]);
        if (commands[i][0] == "L") line(board, commands[i]);

    }
    print(board);
}
