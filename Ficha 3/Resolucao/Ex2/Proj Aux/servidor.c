/**********************************************************************
 * ./servidor <ip servidor> <porto servidor>
 **********************************************************************/


// BIBLIOTECAS
#include <sys/socket.h>
#include <netinet/in.h>
#include <unistd.h>
#include <stdlib.h>
#include <stdio.h>
#include <netdb.h>
#include <string.h>
#include <strings.h>
#include <sys/wait.h>
#include <arpa/inet.h>
#include <signal.h>



// CONSTANTES
#define h_addr h_addr_list[0] /* for backward compatibility */
#define BUFFER_SIZE 1024
#define BYEBYE "BYEBYE"
#define CMD_DADOS "DADOS"
#define CMD_SOMA "SOMA"
#define CMD_MEDIA "MEDIA"
#define CMD_SAIR "SAIR"
#define SIZE_ARRAY 10



// VARS GLOBAIS
struct sockaddr_in * endereco;
int fdSocket;
int numProcesso;


// PROTOTIPOS
void processCliente();
struct sockaddr_in * mallocEndereco();
void erroGrave (const char * quem, const char * onde, const char * msg, int termina);
void printInfo (const char * quem, const char * msg);
void terminar();
void sigintHandler(int signum);
int somatorio(const int array[], int size);
double media(const int array[], int size);
int getDados(const char * buffer, int array[], int sizeArray);



// FUNCOES
int main(int argc, char *argv[]) {
    int fdCliente;
    struct sockaddr_in * enderecoCliente;
    int enderecoSize = sizeof(struct sockaddr_in);
    char printEndereco[INET_ADDRSTRLEN];
    char buffer[BUFFER_SIZE];
    struct hostent * ptrIp;
    int countProcessos;

    endereco = NULL;
    fdSocket = -1;
    numProcesso = 0;
    countProcessos = 0;

    signal(SIGINT, sigintHandler);  // Register signal handler

    if (argc != 3)
        erroGrave("SERVIDOR", "main", "./servidor <ip servidor> <porto servidor>", 1);

    if ((ptrIp = gethostbyname(argv[1])) == 0)
        erroGrave("SERVIDOR", "main", "Impossivel obter endereco", 1);

    endereco = mallocEndereco();
    endereco->sin_family = AF_INET;
    endereco->sin_addr.s_addr = ((struct in_addr *)(ptrIp->h_addr))->s_addr;
    endereco->sin_port = htons((short) strtol(argv[2], NULL, 10));

    if ((fdSocket = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        erroGrave("SERVIDOR", "main", "Socket", 1);

    if (bind(fdSocket, (struct sockaddr*) endereco, sizeof(struct sockaddr_in)) < 0)
        erroGrave("SERVIDOR", "main", "Bind", 1);

    if(listen(fdSocket, 5) < 0)
        erroGrave("SERVIDOR", "main", "Listen", 1);

    inet_ntop(AF_INET, &(endereco->sin_addr.s_addr), printEndereco, INET_ADDRSTRLEN);
    sprintf(buffer, "Servidor Ativo e a Escuta em %s:%d", printEndereco, ntohs(endereco->sin_port));
    printInfo("SERVIDOR", buffer);

    while (1) {
        //clean finished child processes, avoiding zombies
        //must use WNOHANG or would block whenever a child process was working
        while(waitpid(-1,NULL,WNOHANG)>0);

        enderecoCliente = mallocEndereco();

        fdCliente = accept(fdSocket, (struct sockaddr *) enderecoCliente, (socklen_t *) &enderecoSize); //wait for new connection

        if (fdCliente > 0) {
            countProcessos++;

            if (fork() == 0) {
                // FILHO
                signal(SIGINT, SIG_IGN);    // ignorar signal
                close(fdSocket);
                free(endereco);
                endereco = enderecoCliente;
                fdSocket = fdCliente;
                numProcesso = countProcessos;

                processCliente();

                exit(0);
            }
            // PAI CONTINUA...
            close(fdCliente);
        }
        free(enderecoCliente);
    }
}



void processCliente() {
    int nRead;
    char buffer[BUFFER_SIZE];
    char printEndereco[INET_ADDRSTRLEN];
    int fatorWhile, fatorDados, fatorErroDados;
    int array[SIZE_ARRAY];

    inet_ntop(AF_INET, &(endereco->sin_addr.s_addr), printEndereco, INET_ADDRSTRLEN);
    sprintf(buffer, "Recebido Nova Conexão do Cliente %s:%d", printEndereco, ntohs(endereco->sin_port));
    printInfo("SERVIDOR", buffer);

    fatorDados = 0;
    fatorWhile = 1;
    while(fatorWhile) {
        nRead = (int) read(fdSocket, buffer, BUFFER_SIZE-1);
        buffer[nRead] = '\0';

        if (strcmp(CMD_SAIR, buffer) == 0) {
            printInfo("SERVIDOR", "Cliente enviou: CMD_SAIR");
            fatorWhile = 0;
            sprintf(buffer, BYEBYE);
            write(fdSocket, buffer, 1 + strlen(buffer));

        } else if (strcmp(CMD_DADOS, buffer) == 0) {
            printInfo("SERVIDOR", "Cliente enviou: CMD_DADOS");
            sprintf(buffer, "Insira os 10 numeros separados por espacos simples:");
            write(fdSocket, buffer, 1 + strlen(buffer));

            nRead = (int) read(fdSocket, buffer, BUFFER_SIZE-1);
            buffer[nRead] = '\0';

            fatorErroDados = getDados(buffer, array, SIZE_ARRAY);

            if (fatorErroDados) {
                printInfo("SERVIDOR", "Cliente enviou dados corretamente!");
                fatorDados = 1;
                sprintf(buffer, "Numeros Recebidos e Validos!");
                write(fdSocket, buffer, 1 + strlen(buffer));

            } else {
                printInfo("SERVIDOR", "Cliente enviou dados incorretamente!");
                fatorDados = 0;
                sprintf(buffer, "Erro: numeros invalidos!");
                write(fdSocket, buffer, 1 + strlen(buffer));
            }

        } else if (strcmp(CMD_MEDIA, buffer) == 0) {
            printInfo("SERVIDOR", "Cliente enviou: CMD_MEDIA");
            if (fatorDados) {    // == 1
                sprintf(buffer, "Media = %.2f", media(array, SIZE_ARRAY));
                write(fdSocket, buffer, 1 + strlen(buffer));

            } else {    // == 0
                sprintf(buffer, "Erro: Numeros ainda nao recebidos!");
                write(fdSocket, buffer, 1 + strlen(buffer));
            }

        } else if (strcmp(CMD_SOMA, buffer) == 0) {
            printInfo("SERVIDOR", "Cliente enviou: CMD_SOMA");
            if (fatorDados) {    // == 1
                sprintf(buffer, "Soma = %d", somatorio(array, SIZE_ARRAY));
                write(fdSocket, buffer, 1 + strlen(buffer));

            } else {    // == 0
                sprintf(buffer, "Erro: Numeros ainda nao recebidos!");
                write(fdSocket, buffer, 1 + strlen(buffer));
            }

        } else {
            printInfo("SERVIDOR", "Cliente enviou: CMD_DESCONHECIDO");
            sprintf(buffer, "Erro: Comando nao existe!");
            write(fdSocket, buffer, 1 + strlen(buffer));
        }
    }

    terminar();
    printInfo("SERVIDOR", "Programa Terminado!");
}


int somatorio(const int array[], int size) {
    int i, acumula;

    for (acumula = 0, i=0; i <size ; i++)
        acumula = acumula + array[i];

    return acumula;
}


double media(const int array[], int size) {
    return (double) somatorio(array, size) / (double) size;
}


struct sockaddr_in * mallocEndereco() {
    struct sockaddr_in * enderecoTemp = (struct sockaddr_in *) malloc(sizeof(struct sockaddr_in));

    if (enderecoTemp == NULL)
        erroGrave("SERVIDOR", "mallocEndereco", "endereco == NULL", 1);

    bzero((void *) enderecoTemp, sizeof(struct sockaddr_in));
    return enderecoTemp;
}


void erroGrave (const char * quem, const char * onde, const char * msg, int termina) {
    printf("### ERRO ###  [%s - %d]  %s():\"%s\"\n", quem, numProcesso, onde, msg);
    fflush(stdout);
    if (termina)
        terminar();
    printInfo("SERVIDOR", "Programa Terminado!");
    exit(-1);
}


void printInfo (const char * quem, const char * msg) {
    printf("[%s - %d]  %s\n", quem, numProcesso, msg);
    fflush(stdout);
}


void terminar() {
    if (fdSocket > 0)
        close(fdSocket);
    if (endereco != NULL)
        free(endereco);

    printInfo("SERVIDOR", "File descriptor fechado e memoria alocada dinamicamente libertada com sucesso!");
}


void sigintHandler(int signum) {
    signal(SIGINT, SIG_IGN);    // ignorar signal
    printInfo("SERVIDOR", "SIGINT Recebido!");
    terminar();
    printInfo("SERVIDOR", "Programa Principal Terminado! Em espera que os processos-filhos terminem normalmente...");
    while(waitpid(-1,NULL,0)>0); // block
    exit(0);
}


int getDados(const char * buffer, int array[], int sizeArray) {
    const char * inicioStr;
    char * fimStr;
    int i;
    int fatorErro;

    for (fatorErro=1, i=0, inicioStr = buffer ; i < sizeArray && fatorErro && (*inicioStr != '\0'); i++, inicioStr = fimStr) {
        array[i] = (int) strtol(inicioStr, &fimStr, 10);
        if (inicioStr == fimStr)
            fatorErro = 0;
    }

    if (fatorErro == 0 || i != sizeArray)
        return 0;
    else if (*inicioStr != '\0') {
        i = (int) strtol(inicioStr, &fimStr, 10);
        if (inicioStr != fimStr)
            return 0;
    }

    return 1;
}
