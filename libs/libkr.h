#ifndef LIBKR_H
#define LIBKR_H

#define NUMBER '0' /*signal that number found */
#define TOOBIG '9' /*signal that string is too big*/

int kr_power(int x, int n);
int kr_getline(char s[], int lim);
void kr_copy(char s1[], char s2[]);
int kr_strlen(char s[]);
int kr_atoi(char s[]);
char kr_lower(char c);
void kr_squeeze(char s[], int c);
void kr_strcat(char s[], char t[]);
unsigned kr_getbits(unsigned x, unsigned p, unsigned n);
int kr_bitcount(unsigned n);
int kr_binary(int x, int v[], int n); //binary search/find
void kr_digitcount(char c, int ndigit[10], int* nwhite, int* nother);
void kr_shell(int v[], int n);
void kr_reverse(char s[]);
void kr_itoa(int n, char s[]);
void kr_trim(char line[]);
int kr_index(char s[], char t[]);
double kr_atof(char s[]);
void kr_clear();
double kr_push(double f);
double kr_pop();
char kr_getch();
void kr_ungetch(char c);
char kr_getop(char s[], int lim);
void kr_printd(int n); //print number as base10 string
void kr_swap(int *px, int *py);
int kr_getint(int *pn);
char* kr_alloc(int n);
void kr_free(char *p);
void kr_strcpy(char s[], char t[]);
int kr_strcmp(char s[], const char t[]);
char* kr_strsave(char *s);
int kr_dayofyear(int year, int month, int day);
void kr_monthday(int year, int yearday, int* pmonth, int* pday);
int kr_readlines(char* lineptr[], int maxlines);
void kr_writelines(char* lineptr[], int nlines);
void kr_sort(char* v[], int n);
char* kr_monthname(int n);
#endif
