#include <stdio.h>
#include <stdlib.h>
#include <string.h>
int count_occurrences(const char* text, const char* word);
void replace_occurrences(char* text, char* word1, char* word2);
int main(){
	char *word1,*word2;
	char *text;
	word1=(char*)malloc(50*sizeof(char));
	word2=(char*)malloc(50*sizeof(char));
	text=(char*)malloc(500*sizeof(char));
	printf("Primul cuvant: ");
	scanf("%s%*c",word1);
	printf("Al doilea cuvant: ");
	scanf("%s%*c",word2);
	printf("Text: ");
	gets(text);
	replace_occurrences(text,word1,word2);
	puts(text);
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
void replace_occurrences(char* text, char* word1, char* word2){
	int i = 0;
	char s[500]="";
	while (i<strlen(text) && count_occurrences(text,word1)>0){
		if(count_occurrences(text,word1)>count_occurrences(text+i,word1)){
			strncpy(s,text,i-1);
			strcat(s,word2);
			strcat(s,text+i-1+strlen(word1));
			strcpy(text,s); 
		}
		++i;
	}
}









