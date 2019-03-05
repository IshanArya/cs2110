#include <stdio.h>

//TODO: Declaring a struct you can refer to with the name Puppy (hint hint typedef) where each puppy has a name (char *) and an age (int)

typedef struct Puppy {
    char* name;
    int age;
} Puppy;


//TODO: Write your function prototypes for the functions in puppies.c

Puppy create_new_puppy(char *name, int age);

make_friends(Puppy pup1, Puppy pup2);