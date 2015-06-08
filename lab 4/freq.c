//NWEN 243 lab 4 - part 2A
//Program name: cryptanalyst - frequency analysis
//Author: Tianfu Yuan
//ID: 300228072

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h> 
#include <string.h> 
#include <sys/wait.h> 

#define bufsize 1024

int main() {
  FILE *read_file; //set read_file pointer
  FILE *write_file; //set write_file pointer
  
  char file_name[30];
  int cout[30];
  int total[256] = {0}, print_cnt = 0, cnt = 0, ch = 0;
    
  //scan file name and open it
  printf("Please enter the name of file (*.txt): \n");
  gets(file_name);
 
  read_file = fopen(file_name, "r");
    
  //read file form *.txt
  if(read_file==NULL) {
    perror("Unable opening the file. \n");
    exit(EXIT_FAILURE);
  }
    
  //frequency calculation
  printf("The contents of %s file are :\n", file_name);
  while((ch = fgetc(read_file)) != EOF) {
    printf("%c", ch);
    ++total[ch];
    ++cnt;
  }
    
  //print out the count of each character
  //including the percentage of the character appear at file
  write_file = fopen("frequency.txt", "w"); //write result to file
  
  //print frequency result to "frequency.txt"
  fprintf(write_file, "Finish reading, the result is [percentage]: \n\n");
  for(ch = 0; ch < 255; ch++) {
    if(total[ch] > 0) {
      fprintf(write_file, "The count of character %c has:  %d [%0.2f]. \n", ch, total[ch], (total[ch] * 100) / (float)cnt);
      print_cnt += total[ch];
    }
  }
  fprintf(write_file, "\n Total number of characters: %d \n", cnt);
  
  fclose(write_file); //close file
  fclose(read_file); //close file
  return 0;
}