#include <stdio.h>
#include "../libjsonl.h"

#define SIZE 10
int main()
{
	int len;
	char buff[1000] = "{id:\"1\", name:\"alice\"}\0{id:\"3\", name:\"carl\"}\0{id:\"2\", name:\"bob\"}\0";
	char* rows[3];
	rows[0] = &buff[0];
	rows[1] = &buff[23];
	rows[2] = &buff[45];
	char* key = "name";
	char* val = "carl";
	len = jsonl_filter(rows, key, val, 3);
	for(int i = 0; i<len; i++)
		printf("rows[%d]: %s\n", i, rows[i]);
	return(0);
}
