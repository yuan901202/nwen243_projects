#include "udpinclude.h"

#define DATA "The sea is calm tonight,"

int main(argc, argv) int argc; char *argv[];{
    int sock;
    struct sockaddr_in server;
    struct hostent *hp, *gethostbyname();
    char buf[1024];

    char returnNum[1024];
    int c;
    int no;

    if(argc != 3){
      printf("usage:\nudpclient hostname port\n\n");
      exit(3);
    }

    /* Create socket on which to send. */
    sock = socket(AF_INET, SOCK_DGRAM, 0);
    if (sock < 0) { perror("opening datagram socket");  exit(1); }

    hp = gethostbyname(argv[1]);
    if (hp == 0) {
	fprintf(stderr, "%s: unknown host\n", argv[1]);  exit(2);
    }
    bcopy(hp->h_addr, &server.sin_addr, hp->h_length);
    server.sin_family = AF_INET;
    server.sin_port = htons(atoi(argv[2]));

    sprintf(returnNum, "%i", 0);
    c = 0;

    while (c < 10){
        /* Send message. */
        if (sendto(sock, returnNum, sizeof(returnNum), 0, (struct sockaddr*)&server, sizeof(server)) < 0)
        perror("sending datagram message");

         /* Read from the socket */
        if (recv(sock, buf, 1024, 0) < 0)
        perror("receiving datagram packet");
        printf("Client says: -->%s\n", buf);

        no = atoi(buf);
        no = no + 1;

        sprintf(returnNum, "%i", no);
        c = c + 1;
    }
    close(sock);
}
