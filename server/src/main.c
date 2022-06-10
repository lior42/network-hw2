#include "grocerylist.h"
#include "setup.h"
#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printGroceryList(GroceryList *g);
void printGrocery(Grocery *g);

int main(void) {
    srand(time(0));
    GroceryList *my_list = setupGroceryList();

    printGroceryList(my_list);

    Grocery *rng = groceryListSearch(my_list, "Food");

    printGrocery(rng);

    groceryDestroy(rng);
    groceryListDestroy(my_list);
}

void printGroceryList(GroceryList *g) {
    char *p = groceryListToString(g);
    printf("%s\n", p);
    free(p);
}

void printGrocery(Grocery *g) {
    char *p = groceryToString(g);
    printf("%s\n", p);
    free(p);
}