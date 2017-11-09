#include<stdio.h>
#include<stdlib.h>
#include"lambda.h"
char *getstr()
{
	char *s = malloc(sizeof(char)*4);
	strcpy(s,"123");
	return s;
}
int main()
{
	//printf("%d",int_func("4")(7));
	char *s = getstr();
	printf("%s",s);
	return 0;
}
