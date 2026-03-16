CC = gcc
CFLAGS = -Wall -Wextra -O2

SRC = $(shell find src -name '*.c')
OBJ = $(patsubst src/%.c,build/%.o,$(SRC))

LIB = lib/termi.a

lib: $(LIB)

$(LIB): $(OBJ)
	mkdir -p $(dir $@)
	ar rcs $@ $^

build/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

clean:
	rm -rf build
	rm -f $(LIB)
