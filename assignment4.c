#include <stdio.h>
#include <stdlib.h>
#include <string.h>


#define MAX_LINE 10000
#define MAX_CHAR_LINE 200

struct instruction_s {
	int step; 
	int index;
};

//FUNCTION PROTOTYPES
char* get_word(char* s, int n);
void get_sentence(char** lines, struct instruction_s* instructions, int n_instructions, char* sentence);

int main(int argc, char* argv[])
{
	//WE NEED 3 COMMAND LINE ARGUMENTS NAME/TEXT/INSTRUCTION
	//ERROR CHECK FOR NUMBER OF ARGUMENTS?
	
	//GET NAME OF THE FILES
	char* book_name = argv[1];
	char* instructions_name = argv[2];
	
	FILE *fp_instructions_test = NULL;
	FILE *fp_instructions = NULL;
	FILE *fp_book = NULL;
	
	//TO FIND HOW MANY INSTRUCTIONS ARE THERE
	int line_index_test= 0;
	int word_index_test = 0;
	int number_of_instructions = 0;
	
	fp_instructions_test = fopen(instructions_name,"r");
	//TO FIND HOW MANY INSTRUCTIONS THERE ARE
	while(!feof(fp_instructions_test)){
		fscanf(fp_instructions_test,"%d %d",&line_index_test,&word_index_test); //just for one line
		if(!feof(fp_instructions_test)){
			number_of_instructions++;
		}
	}
	fclose(fp_instructions_test);
	
	fp_instructions = fopen(instructions_name,"r");
	//TO PRINT DATAS INTO STRUCT*
	struct instruction_s* sptr_instructions = (struct instruction_s*)malloc(sizeof(struct instruction_s)*number_of_instructions);
	for(int i = 0 ; i < number_of_instructions; i++){
		fscanf(fp_instructions,"%d %d",&(sptr_instructions[i].step),&(sptr_instructions[i].index));
	}
	fclose(fp_instructions);
	
	//TO PRINT LINES INTO CHAR**
	fp_book = fopen(book_name,"r");
	char** all_of_book = (char**)malloc(sizeof(char*) * MAX_LINE); //MEMORY ALLOCATION FOR BOOK
	for(int i = 0; i < MAX_LINE; i++){
		all_of_book[i] = (char*)malloc(sizeof(char) * MAX_CHAR_LINE); //MEMORY ALLOCATION FOR EACH LINE
	}
	for(int i = 0; i < MAX_LINE; i++){
		fgets(all_of_book[i],MAX_CHAR_LINE,fp_book);
	}
	fclose(fp_book);
	
	char* sentence = (char*)malloc(sizeof(char) * MAX_CHAR_LINE);//MEMORY ALLOCATION FOR SENTENCE
	get_sentence(all_of_book, sptr_instructions, number_of_instructions, sentence);
	
	//FREE
	for(int i = 0; i < MAX_LINE; i++){
		free(all_of_book[i]);
	}
	free(all_of_book);
	free(sptr_instructions);
	free(sentence);
	
	return EXIT_SUCCESS;
}


/*
A function get_word that takes a line s and an index n, and returns the selected
word. This function should have the following signature:
*/
char* get_word(char* s, int n)
{
	int counted_space = 0;
	int i = 0;
	int len_sword = 0; //LENGTH OF THE WORD
	while(s[i] == ' ')
	{
		s++;
	}//NOW WE IGNORE THE SPACES AT THE BEGINING
	
	//FOR SPACES BETWEEN WORDS
	while(counted_space != (n-1))
	{
		if(s[i] == ' ')
		{
			if(s[i-1] != ' '){
				counted_space++;
			}
		}
		i++;
	}
	
	//CHECK FOR PUNCTUATION AT BEGINING
	//LETTERS HAVE DECIMAL VALUES 65<=C<=90 AND 97<=C<=122
	if(s[i] < 65){
		i++;
	}
	else if(s[i] > 90 && s[i] < 97){
		i++;
	}
	else if(s[i] > 122){
		i++;
	}
	//now s[i] is begining of my word
	int begin_of_sword = i;
	

	//printf("First letter of secret word is %c\n",s[i]);
	
	//CHECK FOR UPPERCASE LETTERS AND CHANGE THEM TO THEIR LOWERCASE FORMATS
	int dif_decimal = 32; //The difference between decimal value of lowercase letter and uppercase letter is 32 acording to ascII table
	if(s[begin_of_sword] >= 65 && s[begin_of_sword] <= 90){
		s[begin_of_sword] = s[begin_of_sword] + dif_decimal;
	}
	
	char secret_word[MAX_CHAR_LINE];
	int j = 0;
	while(s[i]!= ' '){
		if(s[i] >= 65 && s[i] <= 90){
			s[i] = s[i] + dif_decimal;
			secret_word[j] = s[i];
			len_sword++;
			i++;
			j++;
		}
		else if(s[i]!= '\r' && s[i]!= '\n'){
			if(s[i] >= 97 && s[i] <= 122){
				secret_word[j] = s[i];
				len_sword++;
				i++;	
				j++;
			}
			//CHECK FOR PUNCTUATIONS WHICH ARE USED BETWEEN WORDS
			else{
				i++;
			}
		}
		else{
			break;
		}
	}

	secret_word[len_sword] = '\0';
	//NOW SWPTR POINTS TO BEGINING OF THE MY WORD
	char* swptr = &secret_word[0];
	
	return swptr;
}


/*
A function that takes the lines of a book, a sequence of instructions, the number
of instructions n_instructions, and an empty sentence where to store the
extracted sentence. This function should have the signature:
*/
void get_sentence(char** lines, struct instruction_s* instructions, int n_instructions, char* sentence)
{
	int line[n_instructions];
	int word[n_instructions];
	line[0] = instructions[0].step;
	word[0] = instructions[0].index;
	for(int i = 1; i < n_instructions; i++){
		line[i] = line[i-1] + instructions[i].step;
		word[i] = instructions[i].index;
	}
	//line adresses and word adresses are now stored in different arrays
	
	strcpy(sentence , "\n*");
	for(int i = 0; i < (n_instructions - 1); i++){
		char* single_word;
		single_word = get_word(lines[line[i] - 1],word[i]);
		strcat(sentence, single_word);
		strcat(sentence, " ");
	}
	
	char *last_word = get_word(lines[line[n_instructions - 1] - 1],word[n_instructions - 1]);
	strcat(sentence, last_word);
	strcat(sentence, "*\n");
	
	printf("%s",sentence);
}
