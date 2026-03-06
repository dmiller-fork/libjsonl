#include <stdio.h>
#include "../libjsonl.h"
#include "../libs/libkr.h"

#define LINES 100

int main(int argc, char *argv[])
{
    if (argc < 3) {
        fprintf(stderr, "Usage: %s <filter_key> <filter_val>\n", argv[0]);
        return 1;
    }

    char *filter_key = argv[1];
	char *filter_val = argv[2];
	char *lineptr[LINES];
	int nlines;
	int len;

	if((nlines = kr_readlines(lineptr, LINES)) > 0){
		len = jsonl_filter(lineptr, filter_key, filter_val, nlines);
		kr_writelines(lineptr, len);
	} else
		printf("input too big to sort\n");
	return(0);
}
