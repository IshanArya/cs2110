/**
 * CS 2110 - Spring 2019 - Timed Lab #5
 *
 * @author Ishan Arya
 *
 * tl5.c: Complete the functions!
 */

// Do not add ANY additional includes!!!
#include "tl5.h"
#include "string.h"

///* You should NOT have any global variables. */


struct list *create_list(void) {
    struct list *newList = malloc(sizeof(struct list));
    if (newList == NULL) {
        return NULL;
    }

    newList->starter_pokemon = NULL;

    return newList;
}

struct pokemon *create_pokemon(int level, char *type) {
    struct pokemon *newPokemon = malloc(sizeof(struct pokemon));
    if (newPokemon == NULL) {
        return NULL;
    }

    newPokemon->type = malloc(strlen(type) + 1);
    if(newPokemon->type == NULL) {
      free(newPokemon);
      return NULL;
    }

    strcpy(newPokemon->type, type);
    newPokemon->level = level;
    newPokemon->evolve = NULL;

    return newPokemon;
}

struct pokemon *copy_pokemon(struct pokemon *oldPokemon) {
    if(oldPokemon == NULL) {
      return NULL;
    }
    return create_pokemon(oldPokemon->level, oldPokemon->type);
}

struct pokemon *free_pokemon(struct pokemon *p) {
  if(p == NULL) {
    return NULL;
  }

  free(p->type);
  struct pokemon *next = p->evolve;
  free(p);

  return next;
}

/** copy_list
  *
  * Create a new list and new pokemon nodes  
  *
  * If listToCopy is NULL return NULL. For any memory allocations
  * failures your code must not leak memory. This means that if any
  * memory allocation failures occur, before you return NULL, you must destroy
  * the list 
  *
  * @param listToCopy A pointer to the struct list structure to make a copy of
  * @return The struct list structure created by copying the old one, or NULL on
  *         failure (includes any of the parameters being null)
  */
struct list *copy_list(struct list *listToCopy)
{
    if(listToCopy == NULL) {
      return NULL;
    }

    struct list *newList = create_list();
    if(newList == NULL) {
      return NULL;
    }
    struct pokemon *currentOld = listToCopy->starter_pokemon;
    if(currentOld == NULL) {
      return newList;
    }

    newList->starter_pokemon = copy_pokemon(currentOld);
    struct pokemon *currentNew = newList->starter_pokemon;
    if(currentNew == NULL) {
      free(newList);
      return NULL;
    }
    currentOld = currentOld->evolve;


    while(currentOld != NULL) {
      currentNew->evolve = copy_pokemon(currentOld);
      if(currentNew->evolve == NULL) {
        destroy(newList);
        return NULL;
      }

      currentNew = currentNew->evolve;
      currentOld = currentOld->evolve;
    }


    return newList;
}

/** Destroy
  *
  * Destroys the entire struct list. This function removes every list node
  * and finally remove the list itself.
  *
  * HINT: remember every malloc needs a respective free
  * 
  * @param listToEmpty a pointer to the struct list
  */
void destroy(struct list *listToDestroy) {
    if(listToDestroy == NULL) {
      return;
    }

    struct pokemon *current = listToDestroy->starter_pokemon;
    free(listToDestroy);

    while(current != NULL) {
      current = free_pokemon(current);
    }
}

