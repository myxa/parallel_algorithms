#include <iostream>
#include <ctype.h>
#include <omp.h>
#include <stdio.h>
#include <string.h>

using namespace std;

int main(int argc, char* argv[]) {
    int words = 0;
    bool flag = false;

    for (int i = 0; i < strlen(argv[1]); i++) {
        if (!((argv[1][i] == ' ') || (argv[1][i] == '\t') || (argv[1][i] == '\n')) && flag == false) {
            words++;
            flag = true;
        }
        else { flag = false; }
    }
    cout << words;
    return 0;
}