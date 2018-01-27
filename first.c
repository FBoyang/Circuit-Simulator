#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include"first.h"

int main(int argc, char** argv){
	char* circuit;
	char* input;
	
	circuit = argv[1];
	input = argv[2];
	//printf("%s\n%s\n",circuit,input);
	
	FILE *fPtr1;
	FILE *fPtr2;
	
	fPtr1 = fopen(circuit, "r");
	fPtr2 = fopen(input,"r");
	if(fPtr1==NULL||fPtr2 == NULL){
		printf("no such file\n");
		return 0;
	}
	
	else{
		char** information;// store the circuit information
		information = (char**)malloc(sizeof(char*)*100);
		int out_num;
		//int variable[52];
		char* Ovar = malloc(100);
		//char* Ivar = malloc(100);
		char stringline[100];
		char* tokens;
		//int input;
		//int output;
		int line_num =0;
		while(fgets(stringline, 100 ,fPtr1)!=NULL){
		/*read the first line and get the input variable list*/
			information[line_num] = malloc(sizeof(stringline)+1);
			strcpy(information[line_num],stringline);
			line_num++;
			//printf("line: %d, %s\n",line_num-1, information[line_num-1]);
		}

		char* Line = malloc(100);
		strcpy(Line, information[1]);
		tokens = strtok(Line," ");
		tokens = strtok(NULL," ");
		out_num = atoi(tokens);





/*		put output variable into Ovar
 */
		while(1){
			tokens = strtok(NULL," ");
			//printf("output: %s\n", tokens);
			if(tokens==NULL){
				break;
			}

			strcat(Ovar, tokens);
		}
		//printf("output: %s\n", information[1]);
		char* line = malloc(100);
		int Variable[52];
		Initial(&Variable);
		char* letter = malloc(50);


			tokens = strtok(information[0]," ");//input information
			tokens = strtok(NULL, " ");//input number
			tokens = strtok(NULL, " ");//first variable
		//printf("output: %s\n", information[1]);
/*			store variable into letter
 */			int number = 0;
			while(tokens!=NULL){
				//printf("letter is %s\n", tokens);
				strcat(letter, tokens);
				tokens = strtok(NULL, " ");
				number++;
			}
/*			store boolean into value
 */		
		int Ovalue;
		//printf("output: %s\n", information[1]);
		while(fgets(line, 100, fPtr2)!=NULL){
			tokens = strtok(line, " ");
			char* value = malloc(50);
			while(tokens!=NULL){
				//printf("value is %s\n", tokens);
				strcat(value, tokens);
				tokens = strtok(NULL, " ");
			}
				//printf("string value is: %s\n", value);
				Set_Var(letter, value, &Variable, number);
			
			int i;
			for(i=2; i<line_num; i++){
/*				trans_relation function take a line of relation, update the value of the variable, and print out the value
 */
				trans_relation(information[i], &Variable);
				//printf("after: %s\n", information[i]);
			}
		//	printf("output information is %s\n", information[1]);
	
			for(i=0; i<out_num; i++){
				tokens = strtok(NULL, " ");
				Ovalue = Get_Var(Ovar[i], &Variable);
				printf("%d ", Ovalue);
			}
			printf("\n");
			//Initial(&Variable);
		/*	printf("variable table:");	
			int t;
			for(t=0; t<52; t++){
				printf("%d ",Variable[t]);
			}*/
		}			
		
		fclose(fPtr1);
		fclose(fPtr2);
		}
			

	
	return 0;
}
