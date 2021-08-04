/**********************************************************************
 * ./clienteTcp  <ip servidor>  <porto servidor>  <msg>
 **********************************************************************/

#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <netdb.h>
#include <strings.h>

#define h_addr h_addr_list[0] /* for backward compatibility */

#define BUFFER_SIZE 1024


int main(int argc, char *argv[]) {
    char buffer[BUFFER_SIZE];
    int fdSocket;
    struct sockaddr_in endereco;
    struct hostent * ptrIp;
    int nRead;

    if (argc != 4) {
        printf("./clienteTcp  <ip servidor>  <porto servidor>  <msg>\n");
        exit(-1);
    }

    bzero((void *) &endereco, sizeof(endereco));

    if ((ptrIp = gethostbyname(argv[1])) == 0) {
        printf("Erro\n");
        exit(-1);
    }

    endereco.sin_family = AF_INET;
    endereco.sin_addr.s_addr = ((struct in_addr *)(ptrIp->h_addr))->s_addr;
    endereco.sin_port = htons((short) strtol(argv[2], NULL, 10));

    if ((fdSocket = socket(AF_INET,SOCK_STREAM,0)) == -1) {
        printf("Erro Socket\n");
        exit(-1);
    }

    if (connect(fdSocket,(struct sockaddr *)&endereco,sizeof (endereco)) < 0) {
        printf("Erro Connect\n");
        exit(-1);
    }

    write(fdSocket, argv[3], 1 + strlen(argv[3]));

    nRead = (int) read(fdSocket, buffer, BUFFER_SIZE-1);
    buffer[nRead] = '\0';
    printf("Received from server:\n");
    printf("%s\n", buffer);

    close(fdSocket);
    exit(0);
}
