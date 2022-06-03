#pragma once

// note from lior - i did not forgot groceryInit, i just dont think
// it is neccesary.

/// Simple struct to hold our groceries
typedef struct Grocery {
    char *Department;
    char *ProductName;
} Grocery;

/// Simple struct to hold our inventory
typedef struct GroceryList {
    Grocery *Value;
    struct GroceryList *Next;
} GroceryList;

GroceryList *groceryListInit(void);

void groceryListDestroy(GroceryList *);

/// will return a random item from the department, note that you must call
/// groceryDestroy() on the result.
Grocery *groceryListSearch(GroceryList *, const char *const department);

// note that it will copy the grocery
void groceryListAppend(GroceryList *, Grocery *);

// just to have a nice printing functions
char *groceryToString(Grocery *);
char *groceryListToString(GroceryList *);

void groceryDestroy(Grocery *);
