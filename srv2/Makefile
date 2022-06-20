CFLAGS = -g -Wall -D_REENTRANT

SRCS = client.c server.c
OBJS = $(SRCS:%.c=%.o)
PROGS = $(SRCS:%.c=%)

all : $(PROGS)

server4 : server4.o
	$(CC) -o $@ server4.o -lpthread

clean :
	rm -f $(OBJS) $(PROGS)
