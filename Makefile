CC = gcc
CFLAGS = -Wall -Wextra -std=c11

DEPS = libjsonl.c libs/libkr.c

all: sum-test sort-test getval-test print-test filter-test join-test

sum-test: tests/sum-test.c $(DEPS)
	$(CC) $(CFLAGS) tests/sum-test.c $(DEPS) -o sum-test

sort-test: tests/sort-test.c $(DEPS)
	$(CC) $(CFLAGS) tests/sort-test.c $(DEPS) -o sort-test

filter-test: tests/filter-test.c $(DEPS)
	$(CC) $(CFLAGS) tests/filter-test.c $(DEPS) -o filter-test

join-test: tests/join-test.c $(DEPS)
	$(CC) $(CFLAGS) tests/join-test.c $(DEPS) -o join-test

getval-test: tests/getval-test.c $(DEPS)
	$(CC) $(CFLAGS) tests/getval-test.c $(DEPS) -o getval-test

print-test: tests/print-test.c $(DEPS)
	$(CC) $(CFLAGS) tests/print-test.c $(DEPS) -o print-test

run_sum: sum-test
	./sum-test

run_sort: sort-test
	./sort-test

run_getval: getval-test
	./getval-test

run_print: print-test
	echo "hello world" | ./print-test

run_filter: filter-test
	./filter-test

run_join: join-test
	./join-test

run_all: run_sum run_sort run_getval run_print run_filter run_join

clean:
	rm -f sum-test sort-test getval-test print-test filter-test join-test

.PHONY: all run_sum run_sort run_getval run_print run_all run_filter run_join clean

EMCC = emcc
EFLAGS = -O2 \
         -sEXPORT_NAME=jsonl \
         -sEXPORTED_FUNCTIONS=_jsonl_wasm_sort,_jsonl_wasm_sum,_jsonl_wasm_filter,_jsonl_wasm_join \
         -sEXPORTED_RUNTIME_METHODS=ccall,cwrap \
         -sMODULARIZE \
         -sENVIRONMENT=web

SRC = jsonl.c libjsonl.c libs/libkr.c
OUT = jsonl.js

wasm: $(SRC)
	$(EMCC) $(SRC) $(EFLAGS) -o $(OUT)
