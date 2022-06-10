
#include "setup.h"
#include "grocerylist.h"
#include <stddef.h>

GroceryList *setupGroceryList(void) {
    GroceryList *ret = groceryListInit();
    Grocery arr[] = {
        {.Department = "Cleaning", .ProductName = "Bleach"},
        {.Department = "Food", .ProductName = "Omlet"},
        {.Department = "Food", .ProductName = "Salad"}};

    size_t s = sizeof(arr) / sizeof(Grocery);

    for (size_t i = 0; i < s; i++) {
        groceryListAppend(ret, &arr[i]);
    }

    return ret;
}