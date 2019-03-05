#include "puppies.h"
/**
 * TODO: Create two functions:
 * 1) create_new_puppy that takes in a name and an age and returns a new Puppy
 * 2) make_friends that takes in two puppies and prints out "[puppy1's name] and [puppy2's name] are now friends!"
 * 
 **/

Puppy create_new_puppy(char *name, int age)
{
    Puppy newPup;
    newPup.name = name;
    newPup.age = age;
    return newPup;
}

make_friends(Puppy pup1, Puppy pup2) {
    printf("%s and %s are now friends!\n", pup1.name, pup2.name);
}