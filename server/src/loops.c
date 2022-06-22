#include "loops.h"
#include "constants.h"
#include "grocerylist.h"
#include "logger.h"
#include "shared.h"
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <sys/poll.h>
#include <sys/socket.h>

static void clientLoop(int client_io, GroceryList *data);

void serverLoop(int server_fd, GroceryList *data) {
    for (;;) {
        int client = accept(server_fd, NULL, NULL);

        logger("Accepted new client.");
        clientLoop(client, data);
        close(client);
    }
}

static void clientLoop(int client_io, GroceryList *data) {
    char inp_buff[4096] = {0};
    for (;;) {
        ssize_t is_end = read(client_io, inp_buff, 4095);
        if (is_end == -1) {
            logger("Unknown failure to read");
            continue;
        } else if (is_end == 0) {
            logger("Client disconnected.");
            break;
        }

        if (strcmp(inp_buff, SERVER_END_COMMUNICATION) == 0) {
            logger("Client requested to end communication");
            break;
        }

        char print_tmp[512] = {0};
        sprintf(print_tmp, "Client requested: %s.", inp_buff);
        logger(print_tmp);

        Grocery *res = groceryListSearch(data, inp_buff);
        if (res != NULL) {
            char *to_send = groceryToString(res);

            sprintf(print_tmp, "Found result: %s", to_send);
            write(client_io, to_send, strlen(to_send) + 1);

            free(to_send);
        } else {
            char to_send[] = "Not Matching Product Found.";
            logger(to_send);
            write(client_io, to_send, strlen(to_send) + 1);
        }
        groceryDestroy(res);
    }
}