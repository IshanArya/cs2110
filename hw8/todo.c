#include "todo.h"
#include "useful_strings.h"

char getUserOption(void);
void printToDoList(void);
char addItem(void);
void markCompleted(void);
int removeCompleted(void);

int main(int argc, char *argv[]) {

    if(argc > 2) {
        fprintf(stderr, "%s", ERROR_USAGE);
        exit(1);
    }
    if(argc == 2) {
        FILE *saveFile = fopen(argv[1], "r");
        if(saveFile == NULL) {
            fprintf(stderr, FILE_NOT_FOUND, argv[1]);
            exit(1);
        }
        while(read_todo_list_item(saveFile) == 1) {
        }
    }

    char menuOption;

    while ((menuOption = getUserOption()) != '6') {
        switch (menuOption) {
            case '1':
                printToDoList();
                break;
            case '2':
                if(addItem() == 0) {
                    printf("%s", LIST_MAX);
                }
                break;
            case '3':
                markCompleted();
                break;
            case '4':
                printf("Success! %d items removed!\n", removeCompleted());
                break;
            case '5':
                break;
            default:
                printf("%s", INVALID_CHOICE);
                continue;
                break;
        }
    }

    exit(0);
    return 0;
}


char getUserOption(void) {
    printf("%s", MAIN_MENU_HEADER);
    printf("%s", QUERY);
    printf("%s", OPTIONS_LIST);
    printf("%s", GRAB_INPUT);

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

void printToDoList(void) {
    printf("%s", TODO_LIST_HEADER);

    for (int i = 0; i < Todo_list_length; i++) {
        struct todo_list_item_t currentItem = Todo_list[i];
        printf("%s\n\n", currentItem.title);
        if(currentItem.is_done == 1) {
            printf("%s", COMPLETED);
        } else {
            printf("Due: %02d/%02d/%04d\n", currentItem.due_month, currentItem.due_day, currentItem.due_year);
        }

        printf("Description: %s\n", currentItem.description);
        printf("%s", LINE_BREAK);
    }
}

char addItem(void) {
    printf("%s", ADD_TO_LIST_HEADER);
    if(Todo_list_length >= TODO_LIST_MAX) {
        return 0;
    }

    printf("%s", ADD_TO_LIST);
    return read_todo_list_item(stdin);
}

void markCompleted(void) {
    printf("%s", MARK_ITEM_COMPLETED_HEADER);
    printf("%s", MARK_ITEM_USER_INPUT);

    printf("%s", GRAB_INPUT);

    char input[10];
    if (fgets(input, 10, stdin) == NULL) {
    }

    int index = atoi(input);

    Todo_list[index].is_done = 1;
}

int removeCompleted(void) {
    printf("%s", REMOVE_ITEM_HEADER);

    int numberRemoved = 0;
    for(int i = 0; i < Todo_list_length; i++) {
        if(Todo_list[i].is_done == 1) {
            numberRemoved++;
        } else {
            Todo_list[i - numberRemoved] = Todo_list[i];
        }
    }

    Todo_list_length -= numberRemoved;
    return numberRemoved;
}

