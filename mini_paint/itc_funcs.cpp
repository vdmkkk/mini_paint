#include "mini_paint.h"

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

int stringToInt(string s) {
    int num = 0;
    for (int i = 0; i < itc_len(s); i++) {
        num += (int(s[i]) - 48) * itc_pow(10, itc_len(s) - i - 1);
    }
    return num;
}
