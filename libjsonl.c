#include <stdio.h>
#include <string.h>
#include "libjsonl.h"
#include "./libs/libkr.h"
#define LINE_MAX 1000
#define LEN 10

char *ltrim(char *s) {
    while (*s == ' ' || *s == '\t' || *s == '\n') s++;
    return s;
}

void shift_left(char *s, int n) {
    int i = 0;
    while (s[i+n] != '\0') {
        s[i] = s[i+n];
        i++;
    }
    s[i] = '\0';
}

void jsonl_getval(char* line, const char* key, char val[], int val_size)
{
	char buffer[LINE_MAX];
	strncpy(buffer, line, sizeof(buffer));
	buffer[sizeof(buffer)-1] = '\0';	
	//return 0 if value is found, else return 1
	int len = kr_strlen(buffer);
	if (len >= 2 && line[0] == '{' && line[len-1] == '}') {
    	buffer[len-1] = '\0';   // remove trailing '}'
    	char *p = buffer + 1;   // skip leading '{'
   		char *tok = strtok(p, ",");
    	while (tok) {
			//other code here
			char *colon = strchr(tok, ':');
			if (colon) {
    			*colon = '\0';          /* Tok now ends at key */
				tok = ltrim(tok);
				//printf("tok is: %s\n", tok);
				//printf("key is: %s\n", key);
				if(!kr_strcmp(tok, key)){
					if(kr_strlen(colon+1) <= val_size){
						strcpy(val, colon + 1);
						int n = strlen(val);
						if (n >= 2 && val[0] == '"' && val[n-1] == '"') {
							val[n-1] = '\0';    // remove trailing quote
    						val[0] = ' ';
							char *p = val;
							while (*p == ' ' || *p == '\t' || *p == '\n') p++;
							shift_left(val, p - val);
						}
						return;
					}
				}
			}
        	tok = strtok(NULL, ",");
    	}
		printf("not found\n");
		return;
	} else {
		printf("jsonl line invalid\n");
		return;
	}
}

void jsonl_sort(char* rows[], const char* sort_key, int rows_nlines)
{
    int gap, i, j;
    char *temp;
	char source[LEN], target[LEN];
    for(gap = rows_nlines/2; gap > 0; gap /=2)
        for(i=gap; i<rows_nlines; i++)
            for(j = i-gap; j>=0; j-=gap){
                jsonl_getval(rows[j],sort_key, source, LEN);
                jsonl_getval(rows[j+gap],sort_key, target, LEN);
				//printf("source: %s\n", source);
				//printf("target: %s\n", target);
                if(kr_strcmp(source,target) <= 0)
                    break;
                temp = rows[j];
                rows[j] = rows[j+gap];
                rows[j+gap] = temp;
            }
    return;
}
float jsonl_sum(char* rows[], const char* sum_key, int rows_nlines)
{
	int i;
	float total = 0.0;
	char source[LEN];
	for(i = 0; i < rows_nlines; i++){
		jsonl_getval(rows[i], sum_key, source, LEN);
		total += kr_atof(source);
	}
	return total;
}
