#include "grocerylist.h"
#include <stdio.h>
#include <stdlib.h>

void printGroceryList(GroceryList *g);
void printGrocery(Grocery *g);

int main(void) {
    GroceryList *my_list = groceryListInit();
    Grocery one = {.Department = "Cleaning", .ProductName = "Bleach"};

    Grocery two = {.Department = "Food", .ProductName = "Omlet"};

    Grocery three = {.Department = "Food", .ProductName = "Salad"};
    groceryListAppend(my_list, &one);
    groceryListAppend(my_list, &two);
    groceryListAppend(my_list, &three);

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