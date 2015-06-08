//NWEN 243 lab 3 
//Program name: tcpserver-skel
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

void eatZombies(int n){
  // This function removes the zombie process state left
  // after the child exits. Learn about this in NWEN 301!
  wait3(NULL,WNOHANG,NULL); // Nom Nom 
}

int main(argc, argv) int argc; char *argv[];{
  int sock, length, msgsock, status;
  struct sockaddr_in server,client;
  char buf[bufsize];

  // for forking, and cleaning up zombie child state afterwards
  // You must not change this code. 

  pid_t id;       
  signal(SIGCHLD, &eatZombies);
 
  // OK, NWEN 243 code starts here. 

  // Create a socket (see Lab 2) - it is exactly the same for a server!
  // YOUR CODE HERE 
  sock=socket(AF_INET,SOCK_STREAM,0);// Create a socket and make the exception.
  if(sock < 0){
    printf("sock error");
    return -1;
  }

  // Next, create the socket addressing structure
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = htons(atoi(argv[1])); // this time 1st arg is port#

  // Next you need to BIND your socket.  
  // YOUR CODE HERE 
  if (bind(sock, (struct sockaddr *) &server, sizeof(server))) {//Bind assigns the address specified by addr to the socket referred to by the file descriptor sockfd. addrlen specifies the size, in bytes, of the address structure pointed to by addr.
    perror("bind error");
    exit(1);
  }
  
  // Right, now we are in the main server loop.
  // YOUR CODE HERE   
  listen(sock, 5);
  int cli = sizeof(client);
  // Start by listening

  while(1){
    // you need to accept the connection request
    msgsock=accept(sock,(struct sockaddr *)&client,&cli);
    
    if(msgsock<0){
      error("accept error");
    }
    // the next call makes a new child process that will actually handle the client.
    
    id = fork();
    
    // when id == 0, this is the child and needs to do the work for the server. 
    if(id == 0){
      // read client string 
      if(read(msgsock, buf, bufsize) < 0){
	printf("reading error");
	return -1;
      }
      // turn lower letter to upper letter
      int i;
      for(i = 0; i < sizeof(buf); i++){
	buf[i]=toupper(buf[i]);
      }
      // printout upper letter that recieve from client
      if(write(msgsock, buf, sizeof(buf)) < 0){
	printf("writeing error");
	return -1;
      }   
    }
    // when id > 0, this is the parent, and it should just loop around,
    if (id > 0){
      continue;
    }
    // when id < 0, we had an error.
    if (id < 0){
      printf("error");
    }
    close(msgsock);
    return;
    // Your code here for the child process, that will read from the connection socket, process the data 
    // write back to the socket, and then close and finally call exit(0) when done.

    // Note:  make sure the parent process (id > 0) does not execute this code, but immediately loops back
    // around (via the while) to get another connection request.
  }
}

