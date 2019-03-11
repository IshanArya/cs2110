#include "todo.h"
#include "useful_strings.h"

char getUserOption(void);

int main(int argc, char *argv[]) {

    printf("Number of arguments: %d\n", argc);
    printf("First arg: %s\n", *argv);

    char menuOption;

    while ((menuOption = getUserOption()) != '6') {
        if(menuOption == 0) {
            printf("%s", INVALID_CHOICE);
            continue;
        }
        printf("User Input: %c\n\n", menuOption);
    }

    return 0;
}


char getUserOption(void) {
    printf("%s", MAIN_MENU_HEADER);
    printf("%s", QUERY);
    printf("%s", OPTIONS_LIST);
    printf("> ");

    char input[3];
    if(fgets(input, 3, stdin) == NULL) {
        return 0;
    }

    if(input[sizeof input - 1] == 0 && input[sizeof input - 2] != '\n') {
        int ch;
        while ((ch = fgetc(stdin)) != '\n' && ch != EOF) {}
        return 0;
    }
    
    if(input[0] < '1' || input[0] > '6') {
        return 0;
    }

    return input[0];
}



