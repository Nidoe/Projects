/*Luv Somani
  Project 4
  Phone Number to Words
  */



#include <stdio.h>
#include <string.h>
#include <stdlib.h>
#include <strings.h>

char letter(char number, int a);

typedef struct stuct{
		char word[10];
} WORD;

int main(void){
	/* Initial Variables */
	int i, j, k, l, m, n, o, p, count;
	char num[8];
	char wurd[8];
	char outfile[256];
	char buffer[256];
	char c[8];	
	char e;
	FILE* inputfile;
	FILE* outputfile;
	WORD list[500000];
	WORD list2[2200];
	
	/* User Input */
	printf("Enter a phone number: ");
	scanf("%s", c);
	sscanf(c, "%c%c%c%c%c%c%c%c", &num[0], &num[1], &num[2], &e, &num[3], &num[4], &num[5], &num[6]);
	num[7] = '\0';

	/* Create Output File */
	
	printf("Enter an output file name: ");
	scanf("%s", outfile);
	outputfile = fopen(outfile, "w");

	/* Check for bad input */
/*	for(i = 0; i < 7; i++) {
		if((num[i] - 48) < 2) {
			printf("Invalid Phone Number Input.\n");
			exit(0);
		}
	}
*/
	
	/* Traverse Dictionary into list */
	inputfile = fopen("/usr/share/dict/words", "r");
	
	i = 0;
	while(fgets(buffer, 256, inputfile) != NULL){
		strncpy(list[i].word, buffer, 7);
		i++;
	}
	count = 0;
	/* Create list of word combinations from phone number */
	for(i = 1; i <= 3; i++){
		/* Call Function to determine letter based on number */
		e = letter(num[0], i);
		wurd[0] = e;
		for(j = 1; j <= 3; j++){
			e = letter(num[1], j);
			wurd[1] = e;
			for(k = 1; k<= 3; k++){
				e = letter(num[2], k);
				wurd[2] = e;
				for(l = 1; l<= 3; l++){
					e = letter(num[3], l);
					wurd[3] = e;
					for(m = 1; m <= 3; m++){
						e = letter(num[4], m);
						wurd[4] = e;
						for(n = 1; n <= 3; n++){
							e = letter(num[5], n);
							wurd[5] = e;
							for(o = 1; o<= 3; o++){
								e = letter(num[6], o);
								wurd[6] = e;
								wurd[7] = '\0';
								/* Copy word into second list */
								strcpy(list2[count].word, wurd);
								count++;
							}
						}
					}
				}
			}
		}
	}
	/* Compare Dictionary List to List created from phone number */
	for(p = 0; p < 500000; p++){
		for(i = 0; i < 2200; i++){
			if(strcasecmp(list[p].word, list2[i].word) == 0){
				if(list2[i].word != NULL){
				fprintf(outputfile, "%s\n", list2[i].word);
				}
			}
		}
	}
	/* Close open files */
	fclose(inputfile);
	fclose(outputfile);
	
	return 0;
}

/* Function that returns letter based on two inputs */
char letter(char number, int a){
	switch(number){
	case '2':
		if(a == 1){
			return 'a';
		}
		if(a == 2){
			return 'b';
			}
		if(a == 3){
			return 'c';
			}
	case '3':
		if(a == 1){
			return 'd';
		}
		if(a == 2){
			return 'e';
			}
		if(a == 3){
			return 'f';
			}
	case '4':
		if(a == 1){
			return 'g';
		}
		if(a == 2){
			return 'h';
			}
		if(a == 3){
			return 'i';
			}
	case '5':
		if(a == 1){
			return 'j';
		}
		if(a == 2){
			return 'k';
			}
		if(a == 3){
			return 'l';
			}
	case '6':
		if(a == 1){
			return 'm';
		}
		if(a == 2){
			return 'n';
			}
		if(a == 3){
			return 'o';
			}
	case '7':
		if(a == 1){
			return 'p';
		}
		if(a == 2){
			return 'r';
			}
		if(a == 3){
			return 's';
			}
	case '8':
		if(a == 1){
			return 't';
		}
		if(a == 2){
			return 'u';
			}
		if(a == 3){
			return 'v';
			}
	case '9':
		if(a == 1){
			return 'w';
		}
		if(a == 2){
			return 'x';
			}
		if(a == 3){
			return 'y';
			}
	default:
		return '\0';
		break;
	}
}
