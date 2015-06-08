//NWEN 243 lab 4 - part 1
//Program name: cryptographer-encode
//Author: Tianfu Yuan
//ID: 300228072

#include <sys/socket.h>
#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h> 
#include <string.h> 
#include <sys/wait.h> 

#define bufsize 1024

FILE *read_file;
FILE *write_file;

int main (){
  char str[bufsize];
  
  //allow user to enter UPPER CASE text to encode by caesar cypher
  printf("Enter text that you want to encode (UPPER CASE ONLY): ");
  scanf("%s", str);
  
  //save text to encode file
  write_file = fopen("encode.txt", "w");
  encode(str);//call encode method
  fprintf(write_file, "%s", str);//print to file and save it
  
  fclose(write_file);//close file
  return 0;
}

//encode caesar cipher method
void encode(char str[]){
  int i = 0;
  //the key is shift letter by 3
  //for example: A -> D, B -> E, C -> F, etc
  while (str[i] != '\0') {
    if ((str[i] + 3) >= 65 && (str[i] + 3) <= 90) {
      str[i] += (3);
    } else {
      str[i] += (3 - 25); 
    }
    i++;
  }
  printf("%s \n", str);
  printf("Encoded file saved to encode.txt. \n");
}