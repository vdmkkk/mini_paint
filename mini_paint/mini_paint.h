#ifndef MINI_PAINT_H_INCLUDED
#define MINI_PAINT_H_INCLUDED
#include <iostream>
#include <fstream>
#include <vector>
#include <cmath>
using namespace std;

long long itc_abs(long long num);
double itc_pow(long long num, long long n);
long itc_len(string str);
string itc_slice_str(string str, int start, int ending);
void rect_full (vector <vector <char>> &board, vector <string> command);
void rect(vector <vector <char>> &board, vector <string> command);
void circle (vector <vector <char>> &board, vector <string> command);
void circle_full (vector <vector <char>> &board, vector <string> command);
void line (vector <vector <char>> &board, vector <string> command);
int stringToInt(string s);

#endif // MINI_PAINT_H_INCLUDED
