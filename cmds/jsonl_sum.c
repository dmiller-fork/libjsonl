#include <stdio.h>
#include "../libjsonl.h"
#include "../libs/libkr.h"

#define LINES 100

int main(int argc, char *argv[])
{
    if (argc < 2) {
        fprintf(stderr, "Usage: %s <sum_key>\n", argv[0]);
        return 1;
    }

    char *sum_key = argv[1];
	char *lineptr[LINES];
	int nlines;

	if((nlines = kr_readlines(lineptr, LINES)) > 0){
		jsonl_sum(lineptr, sum_key, nlines);
		kr_writelines(lineptr, nlines);
	} else
		printf("input too big to sort\n");
	return(0);
}
