#include <stdio.h>
#include <string.h>

int main(void)
{    
  char input[1024];
  char *string[256];            // 1) 3 is dangerously small,256 can hold a while;-) 
                                // You may want to dynamically allocate the pointers
                                // in a general, robust case. 
  char delimit[]=" ,.;:!?-()[]{}<>\'\""; // 2) POSIX whitespace characters
  int i = 0, j = 0;

  if(fgets(input, sizeof input, stdin)) // 3) fgets() returns NULL on error.
                                        // 4) Better practice to use sizeof 
                                        //    input rather hard-coding size 
  {                                        
    string[i]=strtok(input,delimit);    // 5) Make use of i to be explicit 
    while(string[i]!=NULL)                    
    {
      printf("string [%d]=%s\n",i,string[i]);
      i++;
      string[i]=strtok(NULL,delimit);
    }

    for (j=0;j<i;j++)
    printf("%s", string[j]);
  }

  return 0;
}