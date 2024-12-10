//**************************************//
// Authors: Ipek Karaoglan 		//
// 	    Glenn Webb-Lopez 		//
// 	    Mariena Segers 		//
// Date: 12-10-24 			//
// Purpose: Final 			//
//**************************************//

#include <stdio.h>
#define LETTERS 20
#define COUNT 10
#define INPUT_FILE "madlib2.txt"
#define OUTPUT_FILE "outputstory.txt"

void words(int *counterNoun, int *counterAdj, int *counterVerb, char noun[COUNT][LETTERS], char adjective[COUNT][LETTERS], char verb[COUNT][LETTERS]);
void processTemplate(FILE* fin, FILE* fout, int counterNoun, char noun[COUNT][LETTERS], int counterVerb, char verb[COUNT][LETTERS], int counterAdj, char adjective[COUNT][LETTERS]);
void printFinalStory(FILE* output);
void input(int checks, char letters[COUNT][LETTERS]);
int countNouns(char *fileName);
int countAdj(char *fileName);
int countVerb(char *fileName);

int main(){

	FILE *finput, *foutput;

	int checks, counterNoun, counterVerb, counterAdj;
	char letters[COUNT][LETTERS], adjective[COUNT][LETTERS], noun[COUNT][LETTERS], verb[COUNT][LETTERS], userName[20];

	printf("Please enter your name:\n");
	scanf("%s", &userName);

	printf("Hello %s, welcome to the mini madlibs game!\n\n", userName);

	// opens the arbitrary text file
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

	// counts Nouns
	counterNoun = countNouns(INPUT_FILE);
	if (counterNoun == 0){
		printf("NO NOUNS\n");
		fclose(finput);
		return 1;
	}

	//counts Verbs
	counterVerb = countVerb(INPUT_FILE);
	if (counterVerb == 0){
		printf("NO V\n");
		fclose(finput);
		return 1;
	}
	// counts Adj
	counterAdj = countAdj(INPUT_FILE);
	if (counterAdj == 0){
		printf("NO A\n");
		fclose(finput);
		return 1;
	}

	words(&counterNoun, &counterAdj, &counterVerb, noun, adjective, verb);
	// reads nouns, adj, verbs

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
	fclose(foutput);
	
	printf("\n");

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

int countNouns(char *fileName){
	FILE *file = fopen(INPUT_FILE, "r");
	if(file == NULL){
		printf("damn it");
		return 0;
	}
	int Ncount = 0;
	char line[LETTERS];
	while (fgets(line, LETTERS, file)){
		for (int i = 0; line[i] != '\0'; i++){
			if(line[i]== 'N'){
				Ncount++;
			}
		}
	}
	fclose(file);
	return Ncount;
}


int countAdj(char *fileName){
	FILE *file = fopen(INPUT_FILE, "r");
	if(file == NULL){
		printf("damn it");
		return 0;
	}
	int Acount = 0;

	char line[LETTERS];
	while (fgets(line, LETTERS, file)){
		for (int i = 0; line[i] != '\0'; i++){
			if(line[i]== 'A'){
				Acount++;
			}
		}
	}
	fclose(file);
	return Acount;
}

int countVerb(char *fileName){
	FILE *file = fopen(INPUT_FILE, "r");
	if(file == NULL){
		printf("damn it");
		return 0;
	}
	int Vcount = 0;

	char line[LETTERS];
	while (fgets(line, LETTERS, file)){
		for (int i = 0; line[i] != '\0'; i++){
			if(line[i]== 'V'){
				Vcount++;
			}
		}
	}
	fclose(file);
	return Vcount;
}

void processTemplate(FILE* fin, FILE* fout, int counterNoun, char noun[COUNT][LETTERS], int counterVerb, char verb[COUNT][LETTERS], int counterAdj, char adjective[COUNT][LETTERS]){
	char line[LETTERS];
	int nounIndex = 0, verbIndex = 0, adjIndex = 0, i;

	while(fgets(line, LETTERS, fin)){
		for(i=0;i<LETTERS && line[i] != '\0'; i++){
			if (line[i] == '\n'){
                		continue;
           		}
           		if(line[i] == 'N' || line[i] == 'V' || line[i] == 'A'){
           			if ((i == 0 || (line[i - 1] < 'A' || line[i - 1] > 'Z') && (line[i - 1] < 'a' || line[i - 1] > 'z')) && (line[i + 1] == '\0' || (line[i + 1] < 'A' || line[i + 1] > 'Z') && (line[i + 1] < 'a' || line[i + 1] > 'z'))){
           				fputc(' ', fout);
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
					fputc(' ', fout);
					continue;
				}
			}
			fputc(line[i], fout);
		}
	}
}

void printFinalStory(FILE* output){
	char line[LETTERS];

	while(fgets(line, LETTERS, output)){
		printf("%s", line);
	}
}
