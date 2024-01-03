#include <stdio.h>
#include <stdlib.h>

#define RED_TEXT    "\x1b[31m"
#define RESET_TEXT  "\x1b[0m"

int main(int argc, char *argv[]) {
    
    if (argc == 1) {
        printf(RED_TEXT "Missing arguments\n" RESET_TEXT);
        return 0;
    }

    int sum = 0;
    for (int i = 1; i < argc; i++) {
        sum += atoi(argv[i]);
    }

    printf("%d \n", sum);

    return 0;
}