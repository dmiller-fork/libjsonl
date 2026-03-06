#include <stdio.h>
#include "libjsonl.h"
#include "libs/libkr.h"
#include <string.h>

#define MAXLINES 1000

char* lineptr[MAXLINES];

void jsonl_wasm_sort(const char* buf, int len, const char* sort_key) {
    // Copy to a mutable buffer
    static char buffer[65536]; // big enough for your input
    if (len >= sizeof(buffer)) len = sizeof(buffer)-1;
    memcpy(buffer, buf, len);
    buffer[len] = '\0';

    int nlines = 0;
    lineptr[nlines++] = buffer;
    for (int i = 0; i < len; i++) {
        if (buffer[i] == '\n') {
            buffer[i] = '\0';
            if (nlines < MAXLINES)
                lineptr[nlines++] = &buffer[i+1];
        }
    }

    jsonl_sort(lineptr, sort_key, nlines);

    for (int i = 0; i < nlines; i++)
        printf("%s\n", lineptr[i]);
}

void jsonl_wasm_sum(const char* buf, int len, const char* sum_key) {
    // Copy to a mutable buffer
    static char buffer[65536]; // big enough for your input
    if (len >= sizeof(buffer)) len = sizeof(buffer)-1;
    memcpy(buffer, buf, len);
    buffer[len] = '\0';

    int nlines = 0;
    lineptr[nlines++] = buffer;
    for (int i = 0; i < len; i++) {
        if (buffer[i] == '\n') {
            buffer[i] = '\0';
            if (nlines < MAXLINES)
                lineptr[nlines++] = &buffer[i+1];
        }
    }

    float total = jsonl_sum(lineptr, sum_key, nlines);

    printf("{%s: %6.2f}\n", sum_key, total);
}

void jsonl_wasm_filter(const char* buf, int len, const char* filter_key, const char* filter_val) {
    // Copy to a mutable buffer
    static char buffer[65536]; // big enough for your input
    if (len >= sizeof(buffer)) len = sizeof(buffer)-1;
    memcpy(buffer, buf, len);
    buffer[len] = '\0';

    int nlines = 0;
    lineptr[nlines++] = buffer;
    for (int i = 0; i < len; i++) {
        if (buffer[i] == '\n') {
            buffer[i] = '\0';
            if (nlines < MAXLINES)
                lineptr[nlines++] = &buffer[i+1];
        }
    }

    int size = jsonl_filter(lineptr, filter_key, filter_val, nlines);

    for (int i = 0; i < size; i++)
        printf("%s\n", lineptr[i]);
}
