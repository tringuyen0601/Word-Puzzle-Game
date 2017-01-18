/* wordgen
This Program looks at a wordlist and create a puzzle and a solution to that puzzle of each words.
Name: Tri Nguyen 
*/
#include <stdio.h>
#include <stdlib.h>
#include <string.h>
char puzzle[24][24];
void puzzlefill (int sizein);
void wordinsert (char word[] , int direction,int cor[], int wordsize);
int wordcheck( char word[], int direction,int cor[], int wordsize, int size);
int main()
{
FILE *fp1, *fp2, *fp3;
int check, count,count1,count2,x,y, sizein,direction;
int cor[2];
char word[24] ,puzfile[17], listfile[23], solutionfile[22];
char puzname[5]=".txt", listname[11]="_words.txt", solutionname[10]="_soln.txt",name[13], dump[1]="A";


srand(2);

check =0;
for(count =0; count<13; count ++) /* initiate the name array to all '\0')*/
			name[count] = '\0';

while (check==0){ /*ask for puzzle size*/
	printf("Please enter a puzzle size:");
	scanf("%d", &sizein);
	printf("puzzle size:%d\n", sizein);
	if ((sizein>=8)&&(sizein<=24))
		check=1; /*valid number, exist loop*/
	else if ((sizein<8)||(sizein>24)) /* out of bound*/
		printf("Invalid number\n");
}

check=0;
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

strcpy(puzfile, name);       /*create name for the 3 files*/           
strcat(puzfile, puzname);

strcpy(listfile, name);
strcat(listfile, listname);

strcpy(solutionfile, name);
strcat(solutionfile, solutionname);

fp2= fopen(listfile,"r"); /*open the wordlist*/

if (fp2==NULL){ 
	printf("File does not exist\n"); /* if wordlist does not exist, exist program*/
	return EXIT_SUCCESS;
	}
/* wordlist exist, create puzzle file and solution file*/
fp1= fopen(puzfile,"w");
fp3= fopen(solutionfile,"w");


for (count = 0; count < sizein; count++){  /*intiate the puzzle to '\0'*/
	for (count1 = 0; count1 < sizein; count1++)
		puzzle[count1][count]='\0';
	}


while(fscanf(fp2, "%s", word) != EOF){
	x=strlen(word); 
	if(x>sizein){ /*word longer than puzzle, exist program*/
		printf("Error! Cannot fit %s in the puzzle\n", word);
		return EXIT_SUCCESS;
		}
	else{
		y=0;
		for (count = 0; count < sizein; count++){  /* check if a word can fit anywhere in the puzzle*/
			for (count1 = 0; count1 < sizein; count1++){/*check every element of the puzzle for all possible direction*/
				for(count2=1; count2<9; count2++) {
					if ((puzzle[count1][count] !='\0') && (puzzle[count1][count] != word[0]))
						y=y+0;/* if an element is already occupied by a different word*/
					else {
						cor[0]=count1;
						cor[1]=count;
						y= y + wordcheck(word, count2,cor,x, sizein);
						}
					}
				}
			}
		}

	if (y==0){/* word cannot fit into puzzle, exist program*/
		printf("Error! Cannot fit %s in puzzle\n", word);
		return EXIT_SUCCESS;
		}
	else {/* a word can fit into the puzzle, random until it get a coordinate and direction that can be used*/
		do {
		cor[0]= rand() % (sizein-1);			
		cor[1]= rand() % (sizein-1);	
		direction = 1+ rand() %8;
		}	
		while (wordcheck(word, direction,cor, x, sizein)==0); 
	wordinsert(word,direction,cor, x);/* write the word into the puzzle*/
		
	if (direction==1) fprintf(fp3,"%s (%d,%d) NW\n",word, cor[0],cor[1]);
	else if (direction==2) fprintf(fp3,"%s (%d,%d) N\n",word, cor[0],cor[1]); /*print the solution with direction*/
	else if (direction==3) fprintf(fp3,"%s (%d,%d) NE\n",word, cor[0],cor[1]);
	else if (direction==4) fprintf(fp3,"%s (%d,%d) E\n",word, cor[0],cor[1]);
	else if (direction==5) fprintf(fp3,"%s (%d,%d) SE\n",word, cor[0],cor[1]);
	else if (direction==6) fprintf(fp3,"%s (%d,%d) S\n",word, cor[0],cor[1]);
	else if (direction==7) fprintf(fp3,"%s (%d,%d) SW\n",word, cor[0],cor[1]);
	else if (direction==8) fprintf(fp3,"%s (%d,%d) W\n",word, cor[0],cor[1]);
	
		}

}


puzzlefill (sizein); /*fill the puzzle with random character*/
fprintf(fp1,"%d\n", sizein);
for (count = 0; count <sizein; count++){ 
	for (count1 = 0; count1 <sizein; count1++){
		fprintf(fp1, "%c ",puzzle[count1][count]); /*print out the puzzle into .txt file*/
	}
	fprintf(fp1,"\n");
	}
fclose(fp1);/*close file*/
fclose(fp2);
fclose(fp3);




return EXIT_SUCCESS;
}



/*This function take a word, a directer(interger), an array of x y coordiate, the size of that words,and write that word into the puzzle according to the direction*/
void wordinsert(char word[], int direction,int cor[], int wordsize){
int count;

if (direction==1){ /*NW*/
	for (count =0; count<wordsize; count++)
		puzzle[cor[0]-count][cor[1]-count]=word[count];	
		
}
else if (direction==2){/*N*/
	for (count =0; count<wordsize; count++)
		puzzle[cor[0]][cor[1]-count]=word[count];
	
}
else if (direction==3){/*NE*/
	for (count =0; count<wordsize; count++)
		puzzle[cor[0]+count][cor[1]-count]=word[count];
		
}
else if (direction==4){/*E*/
	for (count =0; count<wordsize; count++)
		puzzle[cor[0]+count][cor[1]] = word[count]; 
		
}
else if (direction==5){/*SE*/
	for (count =0; count<wordsize; count++)
		puzzle[cor[0]+count][cor[1]+count] = word[count];
		
}
else if (direction==6){/*S*/
	for (count =0; count<wordsize; count++)
		strcpy(&puzzle[cor[0]][cor[1]+count],&word[count]);
		
}
else if (direction==7){/*SW*/
	for (count =0; count<=wordsize; count++)
		puzzle[cor[0]-count][cor[1]+count]=word[count];
		
}
else if (direction==8){/*S*/
	for (count =0; count<wordsize; count++)
		puzzle[cor[0]-count][cor[1]] = word[count];
		
}
}

/*This function take a interger as a puzzle size and fill that puzzle with random lower case letter*/
void puzzlefill (int sizein){
int count, count1;
for (count = 0; count <sizein; count++){ 
	for (count1 = 0; count1 <sizein; count1++){
		if (puzzle[count1][count] =='\0') /* if element is empty, fill it with a character*/
			puzzle[count1][count]= 97 + rand() % (26);
	}
}
}



/*This function take a word, a directer(interger), an array of x y coordiate, the size of that words, size of the puzzle,and and check if that word can be written into the puzzle with the input direction
return 0 if cannot 
return1 if can*/
int wordcheck( char word[], int direction,int cor[], int wordsize, int size){
int result,count;
result=0;
if (direction==1){/*NW*/
	if (((cor[0]-wordsize)<0)||((cor[1]-wordsize)<0))/*check if word can fit into the puzle*/
		return 0;
	for (count =0; count<wordsize; count++){/*check if an element is already occupied by a different word*/
		if ((puzzle[cor[0]-count][cor[1]-count]!= word[count])&&(puzzle[cor[0]-count][cor[1]-count]!='\0'))
			return 0;
		else 
			result=1;	
		}	
} 

else if (direction==2){/*N*/
	if ((cor[1]-wordsize)<0)/*check if word can fit into the puzle*/
		return 0;
	for (count =0; count<wordsize; count++){/*check if an element is already occupied by a different word*/
		if ((puzzle[cor[0]][cor[1]-count]!= word[count])&&(puzzle[cor[0]][cor[1]-count]!='\0'))
			return 0;
		else 
			result=1;	
		}	
	
}  

else if (direction==3){/*NE*/
	if (((cor[0]+wordsize)>size)||((cor[1]-wordsize)<0))/*check if word can fit into the puzle*/
		return 0;
	for (count =0; count<wordsize; count++){/*check if an element is already occupied by a different word*/
		if ((puzzle[cor[0]+count][cor[1]-count]!= word[count])&&(puzzle[cor[0]+count][cor[1]-count]!='\0'))
			return 0;
		else 
			result=1;	
		}	
}

else if (direction==4){/*E*/
	if ((cor[0]+wordsize)>size)/*check if word can fit into the puzle*/
		return 0;
	for (count =0; count<wordsize; count++){/*check if an element is already occupied by a different word*/
		if ((puzzle[cor[0]+count][cor[1]]!= word[count])&&(puzzle[cor[0]+count][cor[1]]!='\0'))
			return 0;
		else 
			result=1;	
		}	
}

else if (direction==5){/*SE*/
	if (((cor[0]+wordsize)>size)||((cor[1]+wordsize)>size))/*check if word can fit into the puzle*/
		return 0;
	for (count =0; count<wordsize; count++){
		if ((puzzle[cor[0]+count][cor[1]+count]!= word[count])&&(puzzle[cor[0]+count][cor[1]+count]!='\0'))
			return 0;
		else 
			result=1;	
		}
}

else if(direction ==6){/*S*/
	if ((cor[1]+wordsize)>size)/*check if word can fit into the puzle*/
		return 0;
	for (count =0; count<wordsize; count++){/*check if an element is already occupied by a different word*/
		if ((puzzle[cor[0]][cor[1]+count]!= word[count])&&(puzzle[cor[0]][cor[1]+count]!='\0'))
			return 0;
		else 
			result=1;	
		}
}

else if (direction==7){/*SW*/
	if (((cor[0]-wordsize)<0)||((cor[1]+wordsize)>size))/*check if word can fit into the puzle*/
		return 0;
	for (count =0; count<wordsize; count++){/*check if an element is already occupied by a different word*/
		if ((puzzle[cor[0]-count][cor[1]+count]!= word[count])&&(puzzle[cor[0]-count][cor[1]+count]!='\0'))
			return 0;
		else 
			result=1;	
		}
}

else if(direction ==8){/*W*/
	if ((cor[0]-wordsize)<0)/*check if word can fit into the puzle*/
		return 0;
	for (count =0; count<wordsize; count++){/*check if an element is already occupied by a different word*/
		if ((puzzle[cor[0]-count][cor[1]]!= word[count])&&(puzzle[cor[0]-count][cor[1]]!='\0'))
			return 0;
		else 
			result=1;	
		}
}

return result;
}
		






