#include "todo.h"
#include "useful_strings.h"

char getUserOption(void);

    int main(int argc, char *argv[])
{
    printf("%d\n", argc);
    for(int i = 0; i < argc; i++) {
        printf("%s\n", argv[i]);
    }

    getUserOption();

    return 0;
}

char getUserOption(void) {
    printf("%s", OPTIONS_LIST);

    char input[2];
    if(fgets_no_newline(input, 2, stdin) == NULL) {
        return 0;
    }

    printf("User Input: %c\n", input[0]);

    return input[0];
}

