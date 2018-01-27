#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<math.h>
void Set_Var(char* var, char* value, int(*Variable)[52], int number){
	//printf("number of variable is%d\n", number);
	int i;
	int val;
	int index;
	for(i=0; i<number; i++){
		val = value[i]-48;
		//printf("value is %d\n",val);
		if((var[i]-'a')<0){//uppercase
		//	printf("Upper variable is %c\n", var[i]);
			index = var[i]-'A';
			(*Variable)[index] = val;
			//printf("variable %c at index %d\n", var[i], index);
			//printf("variable %c is %d\n", var[i], (*Variable)[index]);
		}
		else{//lower case
		//	printf("Lower varibale is %c\n", var[i]);
			index = var[i]-'a'+26;
			(*Variable)[index] =val;
			//printf("variable %c at index %d\n", var[i], index);
			//printf("variable %c is %d\n", var[i], (*Variable)[index]);
		}
	}	
	return;
}
void Initial(int(*Variable)[52]){
	int i;
	for(i = 0; i<52; i++){
		(*Variable)[i] = 0;
	}
}


int Get_Var(char var, int(*Variable)[52]){
	int index;
	int value;
	if((var-'a')<0){ //uppercase or number
		if((var-'A')>=0){//uppercase
			index = var-'A';
			value = (*Variable)[index];
		}
		else{//number
			value = var-'0';
		}
	}
	else{
		index = var-'a'+26;
		value = (*Variable)[index];
	}
	//printf("get variable %c: %d\n", var, value);
	return value;
}

void gc_generator(long unsigned int* code, int num){
	int iteration = log(num)/log(2);
	int i;
	int j;
	int w;
	for(i =0; i<num; i++){
		code[i] = 0;
	}//initialize

	for(i = 0; i<iteration; i++){
		int t_num = pow(2, i+1);
		for( w=0; w<t_num/2; w++){
			code[t_num/2+w] = code[t_num/2-w-1];
		}//fold code
		for(j=t_num/2; j<t_num; j++){
			code[j]+= pow(2,i);
		}
	}
}

int gc_read(int effect, int* Index, long unsigned int* gray_code, int(*Variable)[52], char* var, int var_num){
	//printf("execute gc_read\n");
	int i;
	int j;
	int index;
	int code;
	int var_val[var_num];
	int value;
	char variable;
	int gray_value;
	int temp_val ;
	int final_val =0;
	for(i=0; i<var_num; i++){
		variable = var[i];
		if((variable-65)>=0){// meaning the variable is a letter
		value = Get_Var(variable, Variable);
		}
		else{// meaning the variable is a number
			value = variable-48;
		}
		var_val[i] = value;
		//printf("variable %c is %d\n", variable, value);
	}
	//printf("effect value is: %d\n", effect);
	for(i=0; i<effect; i++){
		temp_val =1;
		index = Index[i];//the index in the gray_code array
		code = gray_code[index];//the gray code in corresponding index, in which the input is 1
		for(j=0; j<var_num; j++){
			gray_value = (code>>(var_num-j-1))%2;
		//	printf("gray value is: %d, variable value is %d\n", gray_value, var_val[j]);
			if(gray_value==var_val[j]){//0,0 or 1,1
				temp_val*= 1;
			}
			else{
				temp_val*=0;
			}

		}
		final_val+= temp_val;
	}
	
		
	return final_val;
}

char itoa(int value){
	char Nvalue;
	Nvalue = value+48;
	return Nvalue;
}		
void trans_relation(char* string, int(*Variable)[52]){
	char* temp = malloc(100);
	strcpy(temp, string);
	char* token;
	token = strtok(temp, " ");//this is the relation
	//printf("relation is: %s\n", token);
	
		if(strcmp(token, "AND")==0){//AND
			int a;
			int b;
			int value;
			char cValue;
			token = strtok(NULL, " ");//first input
			a = Get_Var(*token, Variable);
			token = strtok(NULL, " ");//second input
			b = Get_Var(*token, Variable);
			//printf("and relation: %d, %d\n", a, b);
			value = a&b;
			token = strtok(NULL, " ");//temp variable
			cValue = itoa(value);
			Set_Var(token, &cValue, Variable, 1);
		}
		
		else if(strcmp(token, "OR")==0){
			int a, b;
			int value;
			char cValue;
			token = strtok(NULL, " ");//first input
			//printf("first input is %s\n", token);
			a = Get_Var(*token, Variable);
			token = strtok(NULL, " ");//second input
			//printf("second input is %s\n", token);
			b = Get_Var(*token, Variable);
			//printf("or relation: %d, %d\n", a, b);
			value = a|b;
			token = strtok(NULL, " ");//temp variable
			cValue = itoa(value);
			Set_Var(token, &cValue, Variable,1);
		}
		else if(strcmp(token, "NOT")==0){
			int a; 
			int value;
			char cValue;
			token = strtok(NULL, " ");
			a = Get_Var(*token, Variable);	
			value =  (a==0);
			token = strtok(NULL, " ");//the temp variable
			cValue = itoa(value);
			Set_Var(token, &cValue, Variable, 1);
		}
		else if(strcmp(token, "MULTIPLEXER")==0){
			int num;
			char* var = malloc(100);
			int value;
			char cValue;
			int index[100];
			int e_num=0; // number of "1"
			token = strtok(NULL, " ");
			num = atoi(token);
			long unsigned int gray_code[num];
			gc_generator(gray_code, num);
	/*		int i;
			for(i=0; i<num; i++){
				printf("%ld ", gray_code[i]);
			}
			printf("\n");
	*/

			int count;
			int boolean;
			for(count=0; count<num; count++){
				token = strtok(NULL, " ");
				//printf("token is: %s\n", token);
				if((token[0]-57)>0){//it is a char
					boolean = Get_Var(*token, Variable);
				}
				else{//it is a number
					boolean = atoi(token);
				}
				//	printf("boolean is: %d\n", boolean);
					if(boolean==1){
						index[e_num] = count;
						e_num++;
					}
				
			}
			int var_num = log(num)/log(2); // input variable number
			for(count = 0; count<var_num; count++){
				token = strtok(NULL, " ");
				strcat(var, token);
			}
				value = gc_read(e_num, index, gray_code, Variable, var, var_num);
				token = strtok(NULL, " ");//temp variable
				cValue = itoa(value);
				Set_Var(token, &cValue, Variable, 1);
		}

		else if(strcmp(token, "DECODER")==0){
			token = strtok(NULL, " ");//number of input
			int num = atoi(token);
		//	int input[num];
			int i;
			char* var = malloc(100);
			for(i=0; i<num; i++){
				token = strtok(NULL, " ");//input value
				strcat(var, token);
			}
			//printf("Input variable are: %s\n", var);
			int out_num = pow(2,num);
			long unsigned int gray_code[out_num];
			gc_generator(gray_code, out_num);
			int value;
			char cValue;
			for(i=0; i<out_num; i++){
				token = strtok(NULL, " ");//output variable
				value = gc_read(1, &i, gray_code, Variable, var, num);
				cValue = itoa(value);
				//printf("output variable %s is %d\n", token, value);
				Set_Var(token, &cValue, Variable, 1);
			}
			
		}

		else;
	return;
}
