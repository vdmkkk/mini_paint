#include "mini_paint.h"


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




void print(vector <vector <char>> board) {
    for (int i = 0; i < board.size(); i++){
        for (int j = 0; j < board[i].size(); j++) cout << board[i][j];
        cout << endl;
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

    for (int i = 1; i < commands.size(); i++) {
        if (commands[i][0] == "r") rect(board, commands[i]);
        if (commands[i][0] == "R") rect_full(board, commands[i]);
        if (commands[i][0] == "c") circle(board, commands[i]);
        if (commands[i][0] == "C") circle_full(board, commands[i]);
        if (commands[i][0] == "L") line(board, commands[i]);

    }
    print(board);
}
