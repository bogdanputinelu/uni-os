#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int count_occurrences(const char* text, const char* word);
int main(){
	char *word="salut";
	char *text="Un salut a fost Salut in timp ce saluta salutul salut bines ceau servus";
	printf("%d",count_occurrences(text,word));
	return 0;
}
int count_occurrences(const char* text, const char* word){
	char s[500];
	strcpy(s,text);
	char *p=strtok(s," ");
	int occurrence=0;
	while(p){
		if(strcmp(p,word)==0)
			occurrence++;
		p=strtok(NULL," ");
	}
	return occurrence;
}
