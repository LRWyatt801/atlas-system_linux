CC = gcc
CFLAGS = -Wall -Werror -Wextra -pedantic
SRCS = $(wildcard *.c)
OBJS = $(SRCS:.c=.o)

hnm: $(OBJS)
	$(CC) $(CFLAGS) $^ -o $@

%.o: %.c
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -f *.o 0-hreadelf
