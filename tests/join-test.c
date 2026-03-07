#include <stdio.h>
#include "../libjsonl.h"

#define SIZE 10
int main()
{
	int len;
	char *rows1[3], *rows2[3], *join_rows[9][2];
	char buff1[1000] = "{id:\"1\", name:\"alice\"}\0{id:\"3\", name:\"carl\"}\0{id:\"2\", name:\"bob\"}\0";
	char buff2[1000] = "{id:\"1\", name:\"alice\"}\0{id:\"3\", name:\"carl\"}\0{id:\"2\", name:\"bob\"}\0";
	rows1[0] = &buff1[0];
	rows1[1] = &buff1[23];
	rows1[2] = &buff1[45];
	rows2[0] = &buff2[0];
	rows2[1] = &buff2[23];
	rows2[2] = &buff2[45];
	char* key = "name";
	len = jsonl_join(rows1, rows2, key, 3, 3, join_rows);
	for(int i = 0; i<len; i++)
		printf("rows[%d]: %s-%s\n", i, join_rows[i][0], join_rows[i][1]);
	return(0);
}
