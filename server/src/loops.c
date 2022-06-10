#include "loops.h"
#include "grocerylist.h"
#include "shared.h"

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/socket.h>

static void clientLoop(FILE *client_io, GroceryList *data);

void serverLoop(int server_fd, GroceryList *data) {
    for (;;) {
        int client = accept(server_fd, NULL, NULL);

        // Note - a very simple transformation since now we dont need buffers.
        FILE *to_pass = fdopen(client, "r+");
        clientLoop(to_pass, data);
        fclose(to_pass);
    }
}

static void clientLoop(FILE *client_io, GroceryList *data) {
    for (;;) {
        char *tmp;
        // %ms = malloced string.. useful in this case.
        fscanf(client_io, "%ms", &tmp);

        if (strncmp(
                tmp, SERVER_END_COMMUNICATION, strlen(SERVER_END_COMMUNICATION)
            ) == 0) {
            printf("Client ended conversation.\n");
            free(tmp);
            break;
        }

        Grocery *resp = groceryListSearch(data, tmp);

        if (resp != NULL) {
            char *tmp2 = groceryToString(resp);
            fputs(tmp2, client_io);
            free(tmp2);
            groceryDestroy(resp);
        } else {
            fputs("No matching grocery found.", client_io);
        }

        free(tmp);
    }
}