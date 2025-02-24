CC := gcc
CFLAGS := -Wall -Werror -Wextra -pedantic

BUILD := ../

all: todo_api_0

todo_api_0: main.c httprequesthandlers.c
	$(CC) $(CFLAGS) -o $(BUILD)$@ $^
