#include "grocerylist.h"
#include "loops.h"
#include "setup.h"
#include "shared.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>

void printGroceryList(GroceryList *g);
void printGrocery(Grocery *g);

int main(void) {
    srand(time(0));
    GroceryList *my_list = setupGroceryList();

    printf("List of groceries was created:\n");
    printGroceryList(my_list);

    int fd = setupServer();
    serverLoop(fd, my_list);
    close(fd);

    groceryListDestroy(my_list);
}

void printGroceryList(GroceryList *g) {
    char *p = groceryListToString(g);
    printf("%s\n", p);
    free(p);
}
