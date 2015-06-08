#include  "udpinclude.h"

#define DATA "the tide is full, the moon lies fair"

int main(){
  int sock, length;
  struct sockaddr_in server, client;
  char buf[1024];
 int c;
 char returnNum[1024];
 int number;
  /* Create socket from which to read. */

  sock = socket(AF_INET, SOCK_DGRAM, 0);
  if (sock < 0) {
    perror("opening datagram socket");
    exit(1);
  }
  /* Create server with wildcards. */
  server.sin_family = AF_INET;
  server.sin_addr.s_addr = INADDR_ANY;
  server.sin_port = 0;

  if (bind(sock, (struct sockaddr*)&server, sizeof(server))) {
    perror("binding datagram socket");
    exit(1);
  }

  /* Find assigned port value and print it out. */
  length = sizeof(client);
  if (getsockname(sock, (struct sockaddr*)&server, &length)) {
    perror("getting socket server");
    exit(1);
  }

  fprintf(stderr,"Socket has port #%d\n", ntohs(server.sin_port));

  sprintf(returnNum, "%i", 0);
    c = 0;

  /* Read from the socket */
  while(1){
  if (recvfrom(sock, buf, 1024, 0, (struct sockaddr*)&client, &length) < 0)
    perror("receiving datagram packet");
    printf("Client says: -->%s\n", buf);
    number = atoi(buf);
    number = number +1;

    sprintf(returnNum, "%i", number);

   if (sendto(sock, returnNum, sizeof(returnNum), 0, (struct sockaddr*)&client, sizeof(client)) < 0)
        perror("sending datagram message");
}
  close(sock);
}
