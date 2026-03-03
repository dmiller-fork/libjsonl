#include <stdio.h>
#include "libkr.h"

// used for getch and ungetch
#define MAXVAL 100
#define BUFSIZE 100


static int sp = 0, bufp = 0;
static double val[MAXVAL];
static char buf[BUFSIZE];

//used for alloc and free
//#define NULL 0
#define ALLOCSIZE 1000
static char allocbuf[ALLOCSIZE]; /*storage*/
static char *allocp = allocbuf;  /*next free position*/

//used for readlines [pg 107]
#define MAXLEN 1000

int kr_power(int x, int n)
{
	int i, p;

	p = 1;
	for(i = 1; i <= n; ++i)
		p = p * x;
	return(p);
}

int kr_getline(char s[], int lim)
{
	int c,i;
	for(i=0;i<lim&(c=getchar()) !=EOF && c!='\n'; ++i)
		s[i] = c;
	if(c=='\n'){
		s[i] = c;
		++i;
	}
	s[i] = '\0';
	return(i); //line length, another version is on pg. 67
}

void kr_copy(char s1[], char s2[])
{
	int i = 0;
	while ((s2[i] = s1[i]) != '\0')
		++i;
	return;
}

int kr_strlen(char s[])
{
	int i = 0;
	while(s[i] != '\0')
		++i;
	return(i);
}
//alternative version, [pg 95]
/*
int kr_strlen(char *s)
{
	int n;
	for (n = 0; *s != '\0'; s++)
		n++;
	return(n);
}
*/


int kr_atoi(char s[])
{
	int i,n,sign;
	for(i=0;s[i]==' ' || s[i]=='\n' || s[i]=='\t'; i++)
		; //skip leading? white space
	sign = 1;
	if (s[i] =='+' || s[i] == '-')
		sign = (s[i++]=='+') ? 1 : -1;
	for(n=0; s[i]>= '0' && s[i] <= '9'; i++)
		n = 10*n+s[i]-'0';
	return(sign*n);
}

char kr_lower(char c)
{
	if(c >= 'A' && c <='Z')
		return(c+'a'-'A');
	else
		return(c);
}

void kr_squeeze(char s[], int c)
{
	int i, j;
	for (i=j=0; s[i] != '\0'; i++)
		if(s[i] != c)
			s[j++] = s[i];
	s[j] = '\0';
}

void kr_strcat(char s[], char t[])
{
	int i, j;
	i = j = 0;
	while(s[i] != '\0') //find end of string
		i++;
	while((s[i++] = t[j++]) != '\0')
		;
}

unsigned kr_getbits(unsigned x, unsigned p, unsigned n)
{
	//~0 sets 16 bits to all 1s
	//then you shift them n=3 to the left, setting 1111 1111 1111 1000
	//then you compliment again with ~(), setting 0000 0000 0000 0111
	//the other statement pushes your number to the right
	return((x >>(p+1-n)) & ~(~0 <<n));
}

int kr_bitcount(unsigned n)
{
	int b;
	for(b = 0; n !=0; n>>=1)
		if(n & 01)
			b++;
	return(b);
}

int kr_binary(int x, int v[], int n) //find x in v[0] to v[n-1]
{
	int low, high, mid;
	low = 0;
	high = n - 1;
	while(low <= high){
		mid = (low+high)/2;
		if(x < v[mid])
			high = mid - 1;
		else if ( x > v[mid])
			low = mid + 1;
		else /* found match */
			return(mid);
	}
	return(-1); //return -1 if no match found
}

void kr_digitcount(char c, int ndigit[10], int* nwhite, int* nother)
{
	switch(c) {
	case '0':
	case '1':
	case '2':
	case '3':
	case '4':
	case '5':
	case '6':
	case '7':
	case '8':
	case '9':
		ndigit[c-'0']++;
		break;
	case ' ':
	case '\n':
	case '\t':
		(*nwhite)++;
		break;
	default:
		(*nother)++;
		break;
	}
	return;
}

void kr_shell(int v[], int n)
{
	int gap, i, j, temp;
	for( gap = n/2; gap >0; gap /= 2)
		for(i=gap; i< n; i++)
			for(j=i-gap;j>=0&&v[j]>v[j+gap]; j -=gap){
				temp = v[j];
				v[j] = v[j+gap];
				v[j+gap] = temp;
			}
	return;
}
void kr_reverse(char s[])
{
	int c, i, j;
	for(i=0,j=kr_strlen(s)-1; i<j; i++, j--){
		c=s[i];
		s[i] = s[j];
		s[j] = c;
	}
	return;
}
void kr_itoa(int n, char s[])
{
	/*read int from left to right, then reverse*/
	int i, sign;
	if((sign=n) <0)
		n = -n;
	i = 0;
	do { 
		s[i++] = n % 10 + '0';
	} while ((n /= 10) > 0); 
	if (sign<0)
		s[i++] = '-';
	s[i] = '\0';
	kr_reverse(s);
}

void kr_trim(char line[])
{
	int n = kr_strlen(line);
	while (--n>=0)
		if (line[n] != ' ' && line[n] != '\t' && line[n] != '\n')
			break;
	line[n+1] = '\0';
	return;
}

int kr_index(char s[], char t[])
{
	int i, j, k;
	for(i=0; s[i] != '\0'; i++){
		for(j=i, k=0; t[k]!='\0' && s[j]==t[k]; j++, k++)
			;
		if(t[k] == '\0')
			return(i);
	}
	return(-1);
}

double kr_atof(char s[])
{
	double val, power;
	int i, sign;
	for(i=0; s[i]==' ' || s[i]=='\n' || s[i]=='\t'; i++)
		;
	sign = 1;
	if (s[i] == '+' || s[i] == '-')
		sign = (s[i++]=='+') ? 1 : -1;
	for (val = 0; s[i] >= '0' && s[i] <= '9'; i++){ /*run this loop for >1*/
		val = 10 * val + s[i]-'0';
	}
	if(s[i] == '.')
		i++;
	for(power=1; s[i]>='0' && s[i] <= '9'; i++){ /*run this loop for <1*/
		val = 10 * val + s[i] - '0';
		power *= 10;
	}
	return (sign * val/power);
}

//reverse polish notation calculator
//see global variables at the top
void kr_clear()
{
	sp = 0;
	return;
}
double kr_push(double f)
{
	if(sp < MAXVAL)
		return (val[sp++] = f);
	else {
		printf("error: stack full\n");
		kr_clear();
		return(0);
	}
}

double kr_pop()
{
	if(sp > 0)
		return(val[--sp]);
	else {
		printf("error: stack empty\n");
		kr_clear();
		return(0);
	}
}

char kr_getch()
{
	return((bufp > 0) ? buf[--bufp] : getchar());
}
	
void kr_ungetch(char c)
{
	if(bufp > BUFSIZE)
		printf("ungetch: too many characters]n");
	else
		buf[bufp++] = c;
	return;
}
//TOOBIG and NUMBER defined in header
char kr_getop(char s[], int lim)
{
	int i, c;
	
	while((c = kr_getch()) == ' ' || c == '\t' || c == '\n')
		;
	if ( c != '.' && (c<'0' || c > '9'))
		return(c);
	s[0] = c;
	for(i=1; (c=getchar()) >= '0' && c <= '9'; i++)
		if(i<lim)
			s[i] = c;
	if(c=='.'){
		if(i<lim)
			s[i] = c;
		for(i++; (c=getchar()) >= '0' && c <='9'; i++)
			if(i<lim)
				s[i]=c;
	}
	if(i < lim){ /*number is ok*/
		kr_ungetch(c);
		s[i] = '\0';
		return(NUMBER);
	}	else { /*it is too big; skip rest of line*/
		while(c != '\n' && c !=EOF)
			c = kr_getch();
		s[lim-1] = '\0';
		return(TOOBIG);
	}
}

void kr_printd(int n)
{
	int i;
	if(n<0){
		putchar('-');
		n=-n;
	}
	if((i=n/10)!=0)
		kr_printd(i);
	putchar(n%10 + '0');
	return;
}

void kr_swap(int *px, int *py)
{
	int temp;
	temp = *px;
	*px = *py;
	*py = temp;
	return;
}

int kr_getint(int *pn)
{
	/*pn is the output*/
	int c, sign;
	while((c = kr_getch()) == ' ' || c == '\n' || c == '\t')
		; /*skip white space*/
	sign = 1;
	if( c == '+' || c == '-'){
		sign = (c=='+') ? 1 : -1;
		c = kr_getch();
	}
	for (*pn = 0; c >= '0' && c<='9'; c = kr_getch())
		*pn = 10 * *pn + c - '0';
	*pn *= sign;
	if (c != EOF)
		kr_ungetch(c);
	return(c);
}

char* kr_alloc(int n) /*two ptrs, return p is last p in stack, allocp is next p in stack*/
{
	if(allocp + n <= allocbuf + ALLOCSIZE){ /*fits*/
		allocp +=n;
		return(allocp-n); /*old p*/
	} else 
		return(NULL);
}

void kr_free(char *p)
{
	if(p >= allocbuf && p < allocbuf + ALLOCSIZE)
		allocp = p;
}

void kr_strcpy(char s[], char t[])
{
	int i = 0;
	while((s[i] = t[i]) != '\0')
		i++;
	return;
}

//same code with pointers
/*
void kr_strcpy(char *s, char *t)
{
	while((*s = *t))
		;
	return;
} //works because dereference *s eventually leads to '\0', which is 0 in ascii
*/ 

int kr_strcmp(char s[], const char t[])
{
	int i = 0;
	while(s[i] == t[i])
		if(s[i++] == '\0')
			return(0);
	return(s[i] - t[i]);
}

//same code written with pointers
/*
int kr_strcmp(char *s, char *t)
{
	for( ; *s == *t; s++, t++)
		if(s == '\0')
			return(0);
	return(*s - *t);
}
*/

char* kr_strsave(char *s)
{
	char *p;
	if((p=kr_alloc(kr_strlen(s)+1)) != NULL)
		kr_strcpy(p, s);
	return(p);
}

static int day_tab[2][13] = {
	{0, 31, 28, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
	{0, 31, 29, 31, 30, 31, 30, 31, 31, 30, 31, 30, 31},
};

int kr_dayofyear(int year, int month, int day)
{
	int i, leap;
	leap = (year%4 == 0 && year%100 != 0) || year%400 == 0;
	for(i = 1; i < month; i++) 
		day += day_tab[leap][i];
	return(day);
}
void kr_monthday(int year, int yearday, int* pmonth, int *pday)
{
	int i, leap;
	leap = (year%4 == 0 && year%100 != 0) || year%400 == 0;
	for (i=1; yearday > day_tab[leap][i]; i++)
		yearday -= day_tab[leap][i];
	*pmonth = i;
	*pday = yearday;
	return;
}

int kr_readlines(char* lineptr[], int maxlines)
{
	int len, nlines;
	char *p, line[MAXLEN];
	nlines = 0;
	while((len = kr_getline(line, MAXLEN)) > 0)
		if(nlines >= maxlines)
			return(-1);
		else if ((p = kr_alloc(len)) == NULL)
			return(-1);
		else {
			line[len-1] = '\0';
			kr_strcpy(p, line);
		lineptr[nlines++] = p;
	}
	return(nlines);
}

void kr_writelines(char* lineptr[], int nlines)
{
	int i;
	for(i=0; i< nlines; i++)
		printf("%s\n", lineptr[i]);
}

void kr_sort(char* v[], int n)
{
	int gap, i, j;
	char *temp;
	for (gap = n/2; gap > 0; gap /= 2)
		for(i=gap; i<n; i++)
			for(j = i-gap; j>= 0; j-= gap){
				if(kr_strcmp(v[j], v[j+gap])<=0)
					break;
				temp = v[j];
				v[j] = v[j+gap];
				v[j+gap] = temp;
			}
}

char* kr_monthname(int n)
{
	static char *name[] = {
		"illegal month",
		"January",
		"February",
		"March",
		"April",
		"May",
		"June",
		"July",
		"August",
		"September",
		"October",
		"November",
		"December"
	};
	return((n<1|| n>12) ? name[0] : name[n]);
}
