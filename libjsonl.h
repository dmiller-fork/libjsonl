#ifndef LIBJSONL_H
#define LIBJSONL_H
void jsonl_getval(char* line, const char* key, char val[], int val_size);
void jsonl_sort(char* rows[], const char* sort_key, int rows_nlines);
float jsonl_sum(char* rows[], const char* sum_key, int rows_nlines);
int jsonl_filter(char* rows[], const char* filter_key, const char* filter_val, int row_nlines);
#endif 
