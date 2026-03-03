#ifndef LIBJSONL_H
#define LIBJSONL_H
void jsonl_getval(char* line, const char* key, char val[], int val_size);
void jsonl_sort(char* rows[], const char* sort_key, int rows_nlines);
#endif 
