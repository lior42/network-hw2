#pragma once

#include "grocerylist.h"
#include <stdio.h>

// Setup function for our grocries.. need to call groceryListDestroy() afterward
GroceryList *setupGroceryList(void);

// Setup function for our server, return a file-descriptor
int setupServer(void);