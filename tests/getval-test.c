#include <stdio.h>
#include "../libjsonl.h"

#define SIZE 10
int main()
{
	
	char* line = "{id:\"1\", name:\"alice\"}";
	char val[SIZE];
	char* key = "name";
	jsonl_getval(line, key, val, SIZE);
	printf("val is %s\n", val);
	return(0);
}
