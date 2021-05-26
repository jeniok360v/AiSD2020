#include <stdio.h>
#include <stdlib.h>


int main (int argc, char* argv[]){

	int status = system("shuf aspell_wordlist.txt >sp2.txt");    
    return 0;
}