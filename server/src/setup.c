
#include "setup.h"
#include "grocerylist.h"
#include "shared.h"

#include <string.h>

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

int setupServer(void) {
    int socket_fd = socket(AF_INET, SOCK_STREAM, 0);
    validate_or_die(socket_fd != -1, "Socket creation failed.\n");
    printf("Socket created successfuly.\n");

    sockaddr_in server_addr;
    bzero(&server_addr, sizeof(server_addr));

    server_addr.sin_family = AF_INET;
    server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
    server_addr.sin_port = htons(SERVER_PORT);

    validate_or_die(
        bind(socket_fd, (sockaddr *)&server_addr, sizeof(server_addr)) != 0,
        "Failed to bind server to port %d.\n", SERVER_PORT
    );

    validate_or_die(
        listen(socket_fd, SOMAXCONN),
        "Failed to listen for incomming connections.\n"
    );

    printf("Server now starting on %s:%d.\n", SERVER_ADDRESS, SERVER_PORT);

    return socket_fd;
}