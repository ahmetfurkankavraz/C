#include <stdio.h>
//You cannot use the string library 

#define MAX_STRING_SIZE 20


void append(char* a, char* b)
{
  //fill the function body. Do not change the arguments and the return parameter
  int i = 0;
  int len_space = 1;
  char space = ' ';
  
  while (a[i] != '\0'){
	  i++;
  }
  int len_a = i;
  i = 0;
  while (b[i] != '\0'){
	  i++;
  }
  int len_b = i;
  
  int len_total = len_a + len_b + len_space;
  
  if (MAX_STRING_SIZE <= len_total){
	  printf("Error");
  }
  
  else {
	  a[len_a] = space;
	  
	  for (i = 0; i < len_b; i++){
		a[len_a + len_space + i] = b[i];
	  }
	  a[len_a + len_space + i] = '\0';
	  printf("%s", a);
  }
  
  
  return;
}

int main()
{
	char a[MAX_STRING_SIZE];
	char b[MAX_STRING_SIZE];
	scanf("%s",a);
	scanf("%s",b);
	append(a,b);
	return 0;
}
