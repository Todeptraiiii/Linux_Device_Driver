#include <stdio.h>
#include <stdlib.h>

int main(){
	FILE *file;
	char ch;
	// mo tap tin de doc
	file = fopen ("example.txt","r");
	if(file == NULL)
	{
	perror("Error opening file ^^");
	return -1;
	}
	
	// doc tung ky tu tu tap tin va in ra man hinh
	
	while((ch = fgetc(file)) != EOF )
	{
		putchar(ch);
	}
	
	
	// dong tap tin
	
	fclose(file);
	
	return 0;
	
}
