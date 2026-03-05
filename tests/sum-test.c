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
	char* key = "id";
	float total = jsonl_sum(rows, key, 3);
	printf("{sum_key: %s, total: %6.2f}\n", key, total);
	return(0);
}
