#include <stdio.h>
#include "../libjsonl.h"
#include "../libs/libkr.h"
#include <stdlib.h>
#include <string.h>

#define MAX_ROWS 10000
#define MAX_JOIN 100000
#define BUF 4096

int main(int argc, char *argv[])
{
    if (argc < 4) {
        fprintf(stderr, "Usage: %s <jsonl_rows1> <jsonl_rows2> <join_key>\n", argv[0]);
        return 1;
    }

    char *file1 = argv[1];
    char *file2 = argv[2];
    char *join_key = argv[3];

    FILE *f1 = fopen(file1, "r");
    FILE *f2 = fopen(file2, "r");
    if (!f1 || !f2) {
        perror("fopen");
        return 1;
    }

    char *rows1[MAX_ROWS];
    char *rows2[MAX_ROWS];
    int n1 = 0, n2 = 0;

    char buf[BUF];

    while (fgets(buf, sizeof(buf), f1) && n1 < MAX_ROWS) {
        buf[strcspn(buf, "\n")] = '\0';
        rows1[n1++] = strdup(buf);
    }

    while (fgets(buf, sizeof(buf), f2) && n2 < MAX_ROWS) {
        buf[strcspn(buf, "\n")] = '\0';
        rows2[n2++] = strdup(buf);
    }

    fclose(f1);
    fclose(f2);

    char *join_rows[MAX_JOIN][2];

    int match_count = jsonl_join(rows1, rows2, join_key, n1, n2, join_rows);

    for (int i = 0; i < match_count; i++) {
        printf("%s | %s\n", join_rows[i][0], join_rows[i][1]);
    }

    for (int i = 0; i < n1; i++) free(rows1[i]);
    for (int i = 0; i < n2; i++) free(rows2[i]);

    return 0;
}
