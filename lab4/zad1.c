#include <stdio.h>
#include <string.h>

#define MAX_SIZE 101

int main(){

	char c[MAX_SIZE];
	strcpy(c, "hellow\nh\n");
	printf("%s\n", c);

    char str1[MAX_SIZE], str2[MAX_SIZE];
    int res;

    for(;;){
	    /* Reads two strings from user */
	    printf("Enter first string: ");
	    fgets(str1, sizeof str1, stdin);
	    printf("Enter second string: ");
	    fgets(str2, sizeof str2, stdin);


	    /* Call strcmp() to compare both strings and stores result in res */
	    res = strcmp(str1, str2);

	    if(res == 0)
	    {
	        printf("Both strings are equal.\n");
	    }
	    else if(res < 0)
	    {
	        printf("First string is lexicographically smaller than second.(%i)\n", res);
	    }
	    else
	    {
	        printf("First string is lexicographically greater than second.(%i)\n", res);
	    }
	return 0;
	}
}