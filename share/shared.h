#pragma once

#include "constants.h"
#include "err_handler.h"

#include <netdb.h>
#include <netinet/in.h>
#include <stddef.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

typedef struct sockaddr_in sockaddr_in;
typedef struct sockaddr sockaddr;
// add all network includes here