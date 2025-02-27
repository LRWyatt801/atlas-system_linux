CC := gcc
CFLAGS := -Wall -Werror -Wextra -pedantic

todo_api_0: todo_api_0_src/main.c todo_api_0_src/httprequesthandlers.c
	$(CC) $(CFLAGS) -o $@ $^

todo_api_1: ./todo_api_1_src/main.c ./todo_api_1_src/httprequesthandlers.c ./todo_api_1_src/path_utils.c
	$(CC) $(CFLAGS) -o $@ $^

todo_api_2: ./todo_api_2_src/main.c ./todo_api_2_src/httprequesthandlers.c ./todo_api_2_src/path_utils.c ./todo_api_2_src/header_utils.c
	$(CC) $(CFLAGS) -o $@ $^

todo_api_3: ./todo_api_3_src/*.c
	$(CC) $(CFLAGS) -o $@ $^

todo_api_4: todo_api_4_src/*.c
	$(CC) $(CFLAGS) -o $@ $^

todo_api_5: todo_api_5_src/*.c
	$(CC) $(CFLAGS) -o $@ $^

.PHONY: todo_api_0 todo_api_1 todo_api_2 todo_api_3 todo_api_4 todo_api_5
