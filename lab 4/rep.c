//NWEN 243 lab 4 - part 2B
//Program name: cryptanalyst - frequency analysis
//Author: Tianfu Yuan
//ID: 300228072

#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <signal.h> 
#include <string.h> 
#include <sys/wait.h> 

#define bufsize 10000

int main(){
  int i = 0, j, k = 0, m = 0, pos = 0, max, len1, len2;
  char s[bufsize], t[bufsize], a[200], s1[200], s2[200];
  FILE *fp, *fp1; //set file pointers
  
  printf("Please enter a file name: \n");
  gets(a);
  
  printf("Please enter a character that you want to replace: \n");
  gets(s1);
  
  printf("Please enter a replace character: \n");
  gets(s2);
  
  len1 = strlen(s1);
  len2 = strlen(s2);
  
  if((fp = fopen(a, "r")) == NULL){
    perror("Unable opening the file. \n");
    exit(EXIT_FAILURE);
  }
  
  s[i++] = fgetc(fp);
  while(!feof(fp)){
    s[i++] = fgetc(fp);
  }
  
  //replace the character
  max = i - 1;
  for(i = 0; i < max - len1; i++){
    for(j = 0;j < len1 && (s[i+j] == s1[j]); j++);
    if(j! = len1)
      continue;
    else{  
      for(k = 0; k < i - pos; k++)
        t[m++] = s[pos+k];
        pos = i + len1;
      for(k = 0; k < len2; k++)
        t[m++] = s2[k];
    }
  }
  
  for(k = pos; k < max; k++)
    t[m++] = s[k];
    max = m;
  
  //save the decode message to file
  fp1 = fopen("fileout.txt", "w");
  
  for(j = 0; j < max; j++){
    putchar(t[j]); 
    fputc(t[j],fp1); //print to file
  }
  
  fclose(fp1);
  fclose(fp);
  return 0;
}