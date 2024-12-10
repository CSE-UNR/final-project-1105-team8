//**************************************//
// Authors: Ipek Karaoglan		//
//	    Glenn Webb-Lopez		//
//	    Mariena Segers		//
// Date: 12-10-24			//
// Purpose: Final			//
//**************************************//

#include <stdio.h>
#define LETTERS 20
#define COUNT 10
#define INPUT_FILE "madlib1.txt"
#define OUTPUT_FILE "outputstory.txt"

void words(int *counterNoun, int *counterAdj, int *counterVerb, char noun[COUNT][LETTERS], char adjective[COUNT][LETTERS], char verb[COUNT][LETTERS]);
void processTemplate(FILE* fin, FILE* fout, int counterNoun, char noun[COUNT][LETTERS], int counterVerb, char verb[COUNT][LETTERS], int counterAdj, char adjective[COUNT][LETTERS]);
void printFinalStory(FILE* output);
void input(int checks, char letters[COUNT][LETTERS]);

int main(){


//set our counters equal to what we're finding GOAL
	FILE *finput, *foutput;
	int checks=0, counterNoun=0, counterVerb=0, counterAdj=0;
	char letters[COUNT][LETTERS], adjective[COUNT][LETTERS], noun[COUNT][LETTERS], verb[COUNT][LETTERS], userName[20];
	
	printf("Please enter your name:\n");
	scanf("%s", &userName);
	
	printf("Hello %s, welcome to the mini madlibs game!\n\n", userName);
	
	input(checks, letters);
	
	words(&counterNoun, &counterAdj, &counterVerb, noun, adjective, verb);
	
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
	
	//counterNoun++;
	
	
	
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

void words(int *counterNoun, int *counterAdj, int *counterVerb, char noun[COUNT][LETTERS], char adjective[COUNT][LETTERS], char verb[COUNT][LETTERS]){
	int i;
	for(i=0;i< *counterNoun; i++){
		printf("\nEnter noun: %d \n", i+1);
		scanf("%s", noun[i]);
	}
	for(i=0; i< *counterAdj; i++){
		printf("\nEnter adjective: %d \n", i+1);
		scanf("%s", adjective[i]);
	}
	for(i=0; i< *counterVerb; i++){
		printf("\nEnter verb: %d \n", i+1);
		scanf("%s", verb[i]);
	}
}

void input(int checks, char letters[][LETTERS]){
	char detect;

	for(int i=0; i+1< checks; i++){

		detect = letters[COUNT][LETTERS];
		
		if(detect == 'A'){
			printf("Enter in an adjective: ");
		}
		else if(detect == 'N'){
		counterNoun++;
			printf("Enter in a noun: ");
		}
		else if (detect == 'V'){
			printf("Enter in a verb: ");
		}
	}
}

void processTemplate(FILE* fin, FILE* fout, int counterNoun, char noun[COUNT][LETTERS], int counterVerb, char verb[COUNT][LETTERS], int counterAdj, char adjective[COUNT][LETTERS]){
	char line[LETTERS];
	int nounIndex = 0, verbIndex = 0, adjIndex = 0, i;
	
	while(fgets(line, LETTERS, fin)){
		for(i=0;i<LETTERS && line[i] != '\0'; i++){
			switch(line[i]){
				case 'N':
					
					fputs(noun[nounIndex], fout);
					nounIndex++;
					
					if(nounIndex >= counterNoun){
						
						nounIndex = 0;
						
					}
					break;
				case 'V':
					fputs(verb[verbIndex], fout);
					verbIndex++;
					
					if(verbIndex >= counterVerb){
						verbIndex = 0;
					}
					break;
				case 'A':
					fputs(adjective[adjIndex], fout);
					adjIndex++;
					
					if(adjIndex >= counterAdj){
						adjIndex = 0;
					}
					break;
				default:
					fputc(line[i], fout);
					break;
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
