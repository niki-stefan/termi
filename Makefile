CC = gcc
CFLAGS = -Wall -Wextra -O2 -Iinclude

SRC = $(shell find src -name '*.c')
OBJ = $(patsubst src/%.c,build/%.o,$(SRC))

TEST_SRC = tests/main.c
TEST_BIN = build/main

LIB = lib/termi.a

lib: $(LIB)

$(LIB): $(OBJ)
	mkdir -p $(dir $@)
	ar rcs $@ $^

build/%.o: src/%.c
	@mkdir -p $(dir $@)
	$(CC) $(CFLAGS) -c $< -o $@

test: $(LIB)
	$(CC) $(CFLAGS) -Iinclude $(TEST_SRC) $(LIB) -o $(TEST_BIN)
	./$(TEST_BIN)

clean:
	rm -rf build
	rm -f $(LIB)
