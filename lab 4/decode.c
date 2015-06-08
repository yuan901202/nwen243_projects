//NWEN 243 lab 4 - part 1
//Program name: cryptographer-decode
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
  
  //allow user to enter UPPER CASE text to decode by caesar cypher
  printf("Enter caesar text that you want to decode (UPPER CASE ONLY): ");
  scanf("%s", str);
  
  //save text to decode file
  write_file = fopen("decode.txt", "w");
  decode(str);//call decode method
  fprintf(write_file, "%s", str);//print to file and save it

  fclose(write_file);//close file
  return 0;
}

//decode caesar cipher method
void decode(char str[]){
  int i = 0;
  //the key is shift letter by -3
  //for example: D -> A, E -> B, F -> C, etc
  while (str[i] != '\0') {
    if ((str[i] - 3) >= 65 && (str[i] - 3) <= 90) {
      str[i] += (-3);
    } else {
      str[i] += (-3 - 25); 
    }
    i++;
  }
  printf("%s \n", str);
  printf("Decoded file saved to decode.txt. \n");
}