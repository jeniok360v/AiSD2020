#include <stdio.h>
#include <string.h>
#include <ctype.h>

#define MAX_SIZE 101

void bst_insert_convert(char x[]){
	int length = (int)strlen(x);
    if(length>1){
    	if(!isalpha(x[length-1])){
    		x[length-1]='\0';
    	}
    	if(!isalpha(x[0])){
    		memmove(x, x+1, strlen(x));
    	}
    }
    else if(length==1){
    	if(!isalpha(x[0])){
    		x[0]='\0';
    	}
    }
    return;
}

int main(){

	char c[MAX_SIZE];
	strcpy(c, "5");
	printf("%s\n", c);
	printf("%li\n", strlen(c));
	bst_insert_convert(c);
	printf("%s\n", c);
	printf("%li\n", strlen(c));
	
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
	    else // res>0
	    {
	        printf("First string is lexicographically greater than second.(%i)\n", res);
	    }
	return 0;
	}
}