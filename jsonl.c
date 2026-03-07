#include <stdio.h>
#include "libjsonl.h"
#include "libs/libkr.h"
#include <string.h>

#define MAXLINES 1000
#define MAX_JOIN 10000

char* lineptr[MAXLINES];

int split_lines(char *buffer, int len, char *lineptr[], int maxlines);
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

void jsonl_wasm_join(const char* buf1, const char* buf2, int len1, int len2, const char* join_key) {
    static char buffer1[10000];
    static char buffer2[10000];

    if (len1 >= sizeof(buffer1)) len1 = sizeof(buffer1) - 1;
    if (len2 >= sizeof(buffer2)) len2 = sizeof(buffer2) - 1;

    memcpy(buffer1, buf1, len1);
    memcpy(buffer2, buf2, len2);

    buffer1[len1] = '\0';
    buffer2[len2] = '\0';

    char *rows1[MAXLINES];
    char *rows2[MAXLINES];

    int n1 = split_lines(buffer1, len1, rows1, MAXLINES);
    int n2 = split_lines(buffer2, len2, rows2, MAXLINES);

    char *join_rows[MAX_JOIN][2];

    int match_count = jsonl_join(rows1, rows2, join_key, n1, n2, join_rows);

    for (int i = 0; i < match_count; i++) {
        printf("%s | %s\n", join_rows[i][0], join_rows[i][1]);
    }
}
int split_lines(char *buffer, int len, char *lineptr[], int maxlines)
{
    int nlines = 0;

    if (maxlines <= 0)
        return 0;

    lineptr[nlines++] = buffer;

    for (int i = 0; i < len; i++) {
        if (buffer[i] == '\n') {
            buffer[i] = '\0';
            if (nlines < maxlines) {
                lineptr[nlines++] = &buffer[i + 1];
            }
        }
    }

    return nlines;
}
