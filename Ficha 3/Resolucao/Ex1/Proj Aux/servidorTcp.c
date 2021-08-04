/*******************************************************************************
 * ./clienteTcp  <ip>  <porto>
 *******************************************************************************/

#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <netdb.h>
#include <string.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <strings.h>


#define h_addr h_addr_list[0] /* for backward compatibility */
#define BUFFER_SIZE 1024

int count;

void processCliente(int fdSocketCliente, struct sockaddr_in * endereco);
struct sockaddr_in * mallocEndereco();


int main(int argc, char *argv[]) {
    int fdServidor, fdCliente;
    struct sockaddr_in * enderecoCliente;
    struct sockaddr_in * enderecoServidor;
    struct hostent * ptrIpServidor;
    int enderecoSize = sizeof(struct sockaddr_in);

    if (argc != 3) {
        printf("./clienteTcp  <ip>  <porto>\n");
        exit(-1);
    }

    count = 0;

    if ((ptrIpServidor = gethostbyname(argv[1])) == 0) {
        printf("Erro\n");
        exit(-1);
    }

    enderecoServidor = mallocEndereco();

    enderecoServidor->sin_family = AF_INET;
    enderecoServidor->sin_addr.s_addr = ((struct in_addr *)(ptrIpServidor->h_addr))->s_addr;
    enderecoServidor->sin_port = htons((short) strtol(argv[2], NULL, 10));

    if ((fdServidor = socket(AF_INET, SOCK_STREAM, 0)) < 0){
        printf("Erro Socket\n");
        exit(-1);
    }
    if (bind(fdServidor,(struct sockaddr*) enderecoServidor,sizeof(struct sockaddr_in)) < 0){
        printf("Erro Bind\n");
        exit(-1);
    }
    if(listen(fdServidor, 5) < 0){
        printf("Erro Listen\n");
        exit(-1);
    }

    while (1) {
        //clean finished child processes, avoiding zombies
        //must use WNOHANG or would block whenever a child process was working
        while(waitpid(-1,NULL,WNOHANG)>0);

        enderecoCliente = mallocEndereco();

        //wait for new connection
        fdCliente = accept(fdServidor,(struct sockaddr *) enderecoCliente,(socklen_t *) &enderecoSize);

        if (fdCliente > 0) {
            count++;

            if (fork() == 0) {
                // FILHO
                close(fdServidor);
                processCliente(fdCliente, enderecoCliente);
                close(fdCliente);
                free(enderecoCliente);
                exit(0);
            }
            // CONTINUA PAI...
            close(fdCliente);
            free(enderecoCliente);
        }
    }
}



void processCliente(int fdSocketCliente, struct sockaddr_in * endereco) {
    int nread;
    char buffer[BUFFER_SIZE];
    char printEndereco[INET_ADDRSTRLEN];

    nread = (int) read(fdSocketCliente, buffer, BUFFER_SIZE-1);
    buffer[nread] = '\0';

    inet_ntop(AF_INET, &(endereco->sin_addr.s_addr), printEndereco, INET_ADDRSTRLEN);

    printf("** New message received **\n");
    printf("Client %d connecting from (IP:port) %s:%d says \"%s\"\n", count, printEndereco, endereco->sin_port, buffer);
    fflush(stdout);

    sprintf(buffer, "Server received connection from (IP:port) %s:%d; already received %d connections!", printEndereco, endereco->sin_port, count);

    write(fdSocketCliente, buffer, 1 + strlen(buffer));
}


struct sockaddr_in * mallocEndereco() {
    struct sockaddr_in * endereco = (struct sockaddr_in *) malloc(sizeof(struct sockaddr_in));

    if (endereco == NULL) {
        printf("Erro mallocEndereco\n");
        exit(-1);
    }

    bzero((void *) endereco, sizeof(struct sockaddr_in));
    return endereco;
}
