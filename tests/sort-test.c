#include <stdio.h>
#include "../libjsonl.h"

#define SIZE 10
int main()
{
	
	char buff[1000] = "{id:\"1\", name:\"alice\"}\0{id:\"3\", name:\"carl\"}\0{id:\"2\", name:\"bob\"}\0";
	char* rows[3];
	rows[0] = &buff[0];
	rows[1] = &buff[23];
	rows[2] = &buff[45];
	char val[SIZE];
	char* key = "name";
	jsonl_sort(rows, key, 3);
	for(int i = 0; i<3; i++)
		printf("rows[%d]: %s\n", i, rows[i]);
	return(0);
}
