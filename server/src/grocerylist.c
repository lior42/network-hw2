#include "grocerylist.h"
#include <stdlib.h>
#include <string.h>

static int getLen(GroceryList *);
static GroceryList *getSubList(GroceryList *, const char *const department);

GroceryList *groceryListInit(void) {
    GroceryList *res = calloc(1, sizeof(GroceryList));

    res->Value = NULL;
    res->Next = NULL;

    return res;
}

void groceryListDestroy(GroceryList *self) {
    if (self == NULL)
        return;
    groceryListDestroy(self->Next);
    groceryDestroy(self->Value);
    free(self);
}

/// will return a random item from the department, note that you must call
/// groceryDestroy() on the result.
Grocery *groceryListSearch(GroceryList *self, const char *const department) {
    GroceryList *temp = getSubList(self, department);
    if (getLen(temp) == 0) {
        groceryListDestroy(temp);
        return NULL;
    }
    Grocery *res = calloc(1, sizeof(Grocery));
    GroceryList *iter = self;
    int elements_to_skip = rand() % getLen(temp);

    for (int i = 0; i < elements_to_skip; i++) {
        iter = iter->Next;
    }

    if (iter->Value->Department != NULL) {
        res->Department = calloc(1, strlen(iter->Value->Department) + 1);
        strcpy(res->Department, iter->Value->Department);
    }
    if (iter->Value->ProductName != NULL) {
        res->ProductName = calloc(1, strlen(iter->Value->ProductName) + 1);
        strcpy(res->ProductName, iter->Value->ProductName);
    }

    groceryListDestroy(temp);

    return res;
}

static int getLen(GroceryList *self) {
    if (self == NULL) {
        return 0;
    }
    return 1 + getLen(self->Next);
}

static GroceryList *
getSubList(GroceryList *list, const char *const department) {
    if (list == NULL)
        return groceryListInit();
    GroceryList *res = getSubList(list->Next, department);
    if (strcmp(department, list->Value->Department) == 0) {
        groceryListAppend(res, list->Value);
    }
    return res;
}

// note that it will copy the grocery
void groceryListAppend(GroceryList *self, Grocery *item) {
    if (self == NULL)
        return;
    if (self->Next != NULL)
        return groceryListAppend(self->Next, item);

    Grocery *cpy = calloc(1, sizeof(Grocery));
    cpy->Department = strdup(item->Department);
    cpy->ProductName = strdup(item->ProductName);

    self->Next = groceryListInit();
    self->Next->Value = cpy;
}

// just to have a nice printing functions
char *groceryToString(Grocery *self);
char *groceryListToString(GroceryList *self);

void groceryDestroy(Grocery *self) {
    if (self != NULL) {
        if (self->Department != NULL)
            free(self->Department);

        if (self->ProductName != NULL)
            free(self->ProductName);

        free(self);
    }
}