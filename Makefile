CC = gcc
CFLAGS = -Wall -Wextra

LIBSRC = libjsonl.c libs/libkr.c
CMD_BINS = jsonl_sort
TEST_SRC = $(wildcard tests/*_test.c)
TEST_BINS = $(TEST_SRC:.c=)

jsonl_sort:
	$(CC) $(CFLAGS) cmds/jsonl_sort.c $(LIBSRC) -o jsonl_sort

run_all: $(TEST_BINS)
	@for t in $(TEST_BINS); do \
		echo "Running $$t"; \
		./$$t || exit 1; \
	done

tests/%_test: tests/%_test.c
	$(CC) $(CFLAGS) $< $(LIBSRC) -o $@

clean:
	rm -f $(CMD_BINS) $(TEST_BINS)

EMCC = emcc
EFLAGS = -O2 -sEXPORT_NAME=jsonl \
         -sEXPORTED_FUNCTIONS=_process \
         -sEXPORTED_RUNTIME_METHODS=ccall,cwrap \
         -sMODULARIZE \
         -sENVIRONMENT=web

SRC = jsonl.c libjsonl.c libs/libkr.c
OUT = jsonl.js

wasm: $(SRC)
	$(EMCC) $(SRC) $(EFLAGS) -o $(OUT)




