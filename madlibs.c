//**************************************//
// Authors: Ipek Karaoglan		//
//	    Glenn			//
//	    Mariena			//
// Date: 12-11-24			//
// Purpose: Final			//
//**************************************//

#include <stdio.h>
#define LETTERS 20
#define INPUT_FILE "story1.txt"
#define OUTPUT_FILE "outputstory.txt"

void nouns(int counterNoun, char noun[5][LETTERS]);
void adjectives(int counterAdj, char adjective[3][LETTERS]);
void verbs(int counterVerb, char verb[2][LETTERS]);
void processTemplate(FILE* fin, FILE* fout, int counterNoun, char noun[5][LETTERS], int counterVerb, char verb[2][LETTERS], int counterAdj, char adjective[3][LETTERS]);
void printFinalStory(FILE* output);

int main(){

	FILE *finput, *foutput;
	int counterNoun=5, counterVerb=2, counterAdj=3;
	char adjective[3][LETTERS], noun[5][LETTERS], verb[2][LETTERS], userName[20];
	
	printf(" Please enter your name:\n");
	scanf("%s", &userName);
	
	printf("Hello %s, welcome to the mini madlibs game!\n\n", userName);

	nouns(counterNoun, noun);
	adjectives(counterAdj, adjective);
	verbs(counterVerb, verb);
	
	finput = fopen(INPUT_FILE, "r");
	if(finput == NULL){
		printf("Could not open input\n");
		return 1;
	}
	
	foutput = fopen(OUTPUT_FILE, "w");
	if(foutput == NULL){
		printf("Could not open output\n");
		return 1;
	}
	
	processTemplate(finput, foutput, counterNoun, noun, counterVerb, verb, counterAdj, adjective);

	fclose(finput);
	fclose(foutput);
	
	foutput = fopen(OUTPUT_FILE, "r");
	if(foutput == NULL){
		printf("could not open file\n");
		fclose(foutput);
		return 1;
	}
	
	printf("\n");
	
	printFinalStory(foutput);

	return 0;
}

void nouns(int counterNoun, char noun[5][LETTERS]){
	int i;
	for(i=0;i< counterNoun; i++){
		printf("Enter noun: %d \n", i+1);
		scanf("%s", noun[i]);
	}
}

void adjectives(int counterAdj, char adjective[3][LETTERS]){
	int i;
	for(i=0; i< counterAdj; i++){
		printf("\nEnter adjective: %d \n", i+1);
		scanf("%s", adjective[i]);
	}
}

void verbs(int counterVerb, char verb[2][LETTERS]){
	int i;
	for(i=0; i< counterVerb; i++){
		printf("\nEnter verb: %d \n", i+1);
		scanf("%s", verb[i]);
	}
}

void processTemplate(FILE* fin, FILE* fout, int counterNoun, char noun[5][LETTERS], int counterVerb, char verb[2][LETTERS], int counterAdj, char adjective[3][LETTERS]){
	char line[LETTERS];
	int nounIndex = 0, verbIndex = 0, adjIndex = 0, i;
	
	while(fgets(line, LETTERS, fin)){
		for(i=0;i<LETTERS && line[i] != '\0'; i++){
			if(line[i] == 'N'){
				fputs(noun[nounIndex], fout);
				nounIndex++;
				
				if(nounIndex >= counterNoun){
					nounIndex = 0;
				}
			}
			else if(line[i] == 'V'){
				fputs(verb[verbIndex], fout);
				verbIndex++;
				
				if(verbIndex >= counterVerb){
					verbIndex = 0;
				}
			}
			else if(line[i] == 'A'){
				fputs(adjective[adjIndex], fout);
				adjIndex++;
				
				if(adjIndex >= counterAdj){
					adjIndex = 0;
				}
			}
			else{
				fputc(line[i], fout);
			}
		}
	}
}

void printFinalStory(FILE* output){
	char line[LETTERS];
	
	while(fgets(line, LETTERS, output)){
		printf("%s", line);
	}
}
