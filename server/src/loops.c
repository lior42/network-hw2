#include "loops.h"
#include "grocerylist.h"
#include "logger.h"
#include "shared.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/poll.h>
#include <sys/socket.h>

static void clientLoop(FILE *client_io, GroceryList *data);

void serverLoop(int server_fd, GroceryList *data) {
    for (;;) {
        int client = accept(server_fd, NULL, NULL);

        logger("Accepted new client.");

        // Note - a very simple transformation since now we dont need buffers.
        FILE *to_pass = fdopen(client, "r+");
        clientLoop(to_pass, data);
        fclose(to_pass);
    }
}

static void clientLoop(FILE *client_io, GroceryList *data) {
    struct pollfd p = {.fd = fileno(client_io), .events = POLLIN};
    char *tmp;

    for (;;) {
        // %ms = malloced string.. useful in this case.
        poll(&p, 1, -1);
        printf("{.events = %d, .revents = %d}\n", p.events, p.revents);
        if (p.revents & POLLIN) {
            fscanf(client_io, "%ms", &tmp);
            logger(tmp);
            if (tmp == NULL) {
                free(tmp);
                break;
            }
            if (strcmp(tmp, SERVER_END_COMMUNICATION) == 0) {
                printf("Client ended conversation.\n");
                free(tmp);
                break;
            }

            Grocery *resp = groceryListSearch(data, tmp);

            if (resp != NULL) {
                char *tmp2 = groceryToString(resp);
                fprintf(client_io, "%s\n", tmp2);
                fflush(client_io);
                free(tmp2);
                groceryDestroy(resp);
            } else {
                fputs("No matching grocery found.\n", client_io);
            }

            fflush(client_io);

            free(tmp);
            tmp = NULL;
        }
    }
}