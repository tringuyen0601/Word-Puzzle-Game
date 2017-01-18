/* wordfind 
This Program looks at a wordlist and a puzzlefile and create a solution to that puzzle of each words.
Name: Tri Nguyen 
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char puzzle[24][24];
int wordfinder( char word[], int size,int cor[], int wordsize);
int main()
{
FILE * fp1, *fp2, *fp3;
int check, count,count1, size,x;
int cor[3]={0};
char word[24] ,puzfile[17], listfile[23], solutionfile[22];
char puzname[5]=".txt", listname[11]="_words.txt", solutionname[10]="_soln.txt",name[13],dump[1]="A";

check =0;
for(count =0; count<13; count ++) /* initiate the name array to all '\0')*/
			name[count] = '\0';
while(check==0){
	printf("Please enter the puzzle name: \n");
	scanf ("%13s", name); /*read first 12 character*/
	
	
	if (name[12]!='\0'){
		while (dump[0] != '\n'){ /*if longer than 12, consume the rest of the string*/
		scanf("%c",&dump[0]);
		}
		for(count =0; count<13; count ++) 
			name[count] = '\0'; /* fill the array with '/0'*/
		printf("invalid name \n");
	}
	else if (name[12]=='\0')
		check =1; /* valid name, break loop*/
	
}
strcpy(puzfile, name);                  /*create name for the 3 files to be used in fopen*/
strcat(puzfile, puzname);

strcpy(listfile, name);
strcat(listfile, listname);

strcpy(solutionfile, name);
strcat(solutionfile, solutionname);

fp1= fopen(puzfile,"r"); /*open puzzle and wordlist to read*/
fp2= fopen(listfile,"r");

if ((fp1== NULL)|| (fp2==NULL)){ /*if file does not exist, end prgogram*/
	printf("File does not exist\n");
	return EXIT_SUCCESS;
	}


fp3= fopen(solutionfile,"w"); /*open solution file to write*/

fscanf(fp1, "%d\n", &size);
for (count = 0; count < size; count++){ /*copy the puzzle in to 2d array*/
	for (count1 = 0; count1 < size; count1++){
		fscanf(fp1, "%s",&puzzle[count1][count]);
	}
	}


while(fscanf(fp2, "%s", word) != EOF){ /*read words from word list*/
	x=strlen(word); /*calculate word length*/
	count = wordfinder(word,size,cor,x);
	if (count==0){ /* if word is not found exit*/
		printf("Error ! Cannot find: %s\n", word);
		return EXIT_SUCCESS;
	}
	else if (count==1) fprintf(fp3,"%s (%d,%d) NW\n",word, cor[0],cor[1]);
	else if (count==2) fprintf(fp3,"%s (%d,%d) N\n",word, cor[0],cor[1]); /*print the solution with direction*/
	else if (count==3) fprintf(fp3,"%s (%d,%d) NE\n",word, cor[0],cor[1]);
	else if (count==4) fprintf(fp3,"%s (%d,%d) E\n",word, cor[0],cor[1]);
	else if (count==5) fprintf(fp3,"%s (%d,%d) SE\n",word, cor[0],cor[1]);
	else if (count==6) fprintf(fp3,"%s (%d,%d) S\n",word, cor[0],cor[1]);
	else if (count==7) fprintf(fp3,"%s (%d,%d) SW\n",word, cor[0],cor[1]);
	else if (count==8) fprintf(fp3,"%s (%d,%d) W\n",word, cor[0],cor[1]);
	
	}
count = wordfinder(word,size,cor,x);	
fclose(fp1);/*close file*/
fclose(fp2);
fclose(fp3);






return EXIT_SUCCESS;
}


/*this function find a given word in the puzzle, return an interger corespond with the direction and change variable x and y to the coordinate of that word*/
int wordfinder( char word[], int size,int cor[], int wordsize){
int count, count1,step,result;
step=0;
for (count = 0; count < size; count++){ /*check every element of the puzzle*/
	for (count1= 0; count1 < size; count1++){
		result=0;

		if (puzzle[count1][count] == word[0]){ /* if found any occurence of the first letter, check for 8 possible directions*/
			if (puzzle[count1-(step+1)][count-(step+1)] == word[step+1]){
				while ((puzzle[count1-(step+1)][count-(step+1)] == word[step+1])&&(step<(wordsize-1))){ /*NW*/
					step++;
					cor[0]=count1;/* write coordinate of the starting location into an array*/
					cor[1]=count;
					}
				if (step== (wordsize-1)){ /* found a word, return an interger coresponding to a direction*/
					result=1;
					return result;
					}
				step=0;
				}		

			if (puzzle[count1][count-(step+1)] ==word[step+1]){
				while ((puzzle[count1][count-(step+1)] ==word[step+1])&&(step<(wordsize-1))){ /*N*/
					step++;
					cor[0]=count1;/* write coordinate of the starting location into an array*/
					cor[1]=count;
					}
				if (step== (wordsize-1)){/* found a word, return an interger coresponding to a direction*/
					result=2;
					return result;
					}

				step=0;
				}

			if (puzzle[count1+(step+1)][count-(step+1)] == word[step+1]){
				while ((puzzle[count1+(step+1)][count-(step+1)] == word[step+1])&&(step<(wordsize-1))){ /*NE*/
					step++;
					cor[0]=count1;/* write coordinate of the starting location into an array*/
					cor[1]=count;
					}
				if (step== (wordsize-1)){/* found a word, return an interger coresponding to a direction*/
					result=3;
					return result;
					}

				step=0;
				}

			if (puzzle[count1+(step+1)][count] == word[step+1]){
				while ((puzzle[count1+(step+1)][count] == word[step+1])&&(step<(wordsize-1))){ /*E*/
					step++;
					cor[0]=count1;/* write coordinate of the starting location into an array*/
					cor[1]=count;
					}
				if (step== (wordsize-1)){/* found a word, return an interger coresponding to a direction*/
					result=4;
					return result;
					}

				step=0;
				}

			if (puzzle[count1+(step+1)][count+(step+1)] ==word[step+1]){
				while ((puzzle[count1+(step+1)][count+(step+1)] ==word[step+1])&&(step<(wordsize-1))){ /*SE*/
					step++;
					cor[0]=count1;/* write coordinate of the starting location into an array*/
					cor[1]=count;
					}
				result=10;
				if (step== (wordsize-1)){/* found a word, return an interger coresponding to a direction*/
					result=5;
					return result;
					}

				step=0;
				}

			if (puzzle[count1][count+(step+1)] == word[step+1]){
				while ((puzzle[count1][count+(step+1)] == word[step+1])&&(step<(wordsize-1))){ /*S*/
					step++;
					cor[0]=count1;/* write coordinate of the starting location into an array*/
					cor[1]=count;
					}
				if (step== (wordsize -1)){/* found a word, return an interger coresponding to a direction*/
					result=6;
					return result;
					}

				step=0;
				}

			if (puzzle[count1-(step+1)][count+(step+1)] == word[step+1]){
				while ((puzzle[count1-(step+1)][count+(step+1)] == word[step+1])&&(step<(wordsize-1))){ /*SW*/
					step++;
					cor[0]=count1;/* write coordinate of the starting location into an array*/
					cor[1]=count;
					}
				if (step== (wordsize-1)){/* found a word, return an interger coresponding to a direction*/
					result=7;
					return result;
					}

				step=0;
				}

			if (puzzle[count1-(step+1)][count] == word[step+1]){
				while ((puzzle[count1-(step+1)][count] == word[step+1])&&(step<(wordsize-1))){ /*W*/
					step++;
					cor[0]=count1; /* write coordinate of the starting location into an array*/
					cor[1]=count;
					}
				if (step== (wordsize-1)){/* found a word, return an interger coresponding to a direction*/
					result=8;
					return result;
					}

				step=0;
				}
		}
	}
}
return result;
}










