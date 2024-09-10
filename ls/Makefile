CFLAGS := -Wall -Werror -Wextra -pedantic

.PHONY := all clean

all: hls

hls: *.c
	gcc -o $@ $^ $(CFLAGS)

clean:
	rm -f hls
