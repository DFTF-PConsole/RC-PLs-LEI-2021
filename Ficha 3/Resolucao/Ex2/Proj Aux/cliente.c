/**********************************************************************
 * ./cliente <ip servidor> <porto servidor>
 **********************************************************************/


// BIBLIOTECAS
#include <stdio.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <stdlib.h>
#include <string.h>
#include <strings.h>
#include <unistd.h>
#include <netdb.h>


// CONSTANTES
#define h_addr h_addr_list[0] /* for backward compatibility */
#define BUFFER_SIZE 1024
#define BYEBYE "BYEBYE"


// VARS GLOBAIS
struct sockaddr_in * enderecoServidor;
int fdServidor;


// PROTOTIPOS
struct sockaddr_in * mallocEndereco();
void erroGrave (const char * quem, const char * onde, const char * msg, int termina);
void printInfo (const char * quem, const char * msg);
void terminar();
void getStringStdin(char string[], int n);



// FUNCOES
int main(int argc, char *argv[]) {
    char buffer[BUFFER_SIZE];
    struct hostent * ptrIpServidor;
    int nRead;
    int fatorWhile;

    enderecoServidor = NULL;
    fdServidor = -1;

    if (argc != 3)
        erroGrave("CLIENTE", "main", "./cliente <ip servidor> <porto servidor>", 1);

    if ((ptrIpServidor = gethostbyname(argv[1])) == 0)
        erroGrave("CLIENTE", "main", "Impossivel obter endereco", 1);

    enderecoServidor = mallocEndereco();

    enderecoServidor->sin_family = AF_INET;
    enderecoServidor->sin_addr.s_addr = ((struct in_addr *)(ptrIpServidor->h_addr))->s_addr;
    enderecoServidor->sin_port = htons((short) strtol(argv[2], NULL, 10));

    if ((fdServidor = socket(AF_INET, SOCK_STREAM, 0)) < 0)
        erroGrave("CLIENTE", "main", "Socket", 1);

    if(connect(fdServidor, (struct sockaddr*) enderecoServidor, sizeof(struct sockaddr_in)) < 0)
        erroGrave("CLIENTE", "main", "Connect", 1);

    printInfo("CLIENTE", "Cliente conectado com sucesso!");
    printInfo("CLIENTE", "AJUDA - Existem 4 comandos: 'SOMA', 'DADOS', 'MEDIA' e 'SAIR'. Caso insira 'DADOS', deverá em seguida inserir 10 números separados por um espaçamento simples.");

    fatorWhile = 1;
    while (fatorWhile) {
        printInfo("CLIENTE", "Insira aqui os comandos ou dados:");
        printf ("> ");
        getStringStdin(buffer, BUFFER_SIZE);

        write(fdServidor, buffer, 1 + strlen(buffer));

        nRead = (int) read(fdServidor, buffer, BUFFER_SIZE-1);
        buffer[nRead] = '\0';
        if (strcmp(BYEBYE, buffer) == 0)
            fatorWhile = 0;
        printInfo("SERVIDOR", buffer);
    }

    terminar();
    printInfo("CLIENTE", "Programa Terminado!");
    exit(0);
}



struct sockaddr_in * mallocEndereco() {
    struct sockaddr_in * endereco = (struct sockaddr_in *) malloc(sizeof(struct sockaddr_in));

    if (endereco == NULL)
        erroGrave("CLIENTE", "mallocEndereco", "endereco == NULL", 1);

    bzero((void *) endereco, sizeof(struct sockaddr_in));
    return endereco;
}


void erroGrave (const char * quem, const char * onde, const char * msg, int termina) {
    printf("### ERRO ###  [%s]  %s():\"%s\"\n", quem, onde, msg);
    fflush(stdout);
    if (termina)
        terminar();
    printInfo("CLIENTE", "Programa Terminado!");
    exit(-1);
}


void printInfo (const char * quem, const char * msg) {
    printf("[%s]  %s\n", quem, msg);
    fflush(stdout);
}


void terminar() {
    if (fdServidor > 0)
        close(fdServidor);
    if (enderecoServidor != NULL)
        free(enderecoServidor);

    printInfo("CLIENTE", "File descriptor fechado e memoria alocada dinamicamente libertada com sucesso!");
}


void getStringStdin(char string[], int n) {
    /* DESCRICAO: Funcao personalizada para ler, guardar e tratar dados no STDIN, limpando o restante.
     * INPUT: string: local onde é guardada os chars recolhidos | n: tamanho máximo suportado por string
     * OUTPUT: --- */

    int i = 0, c;

    // ler stdin ate atingir o final do stdin ou da memoria disponivel
    while (i < (n - 1) && ((string[i] = (char)getchar()) != '\n' && string[i] != EOF))
        i++;

    // (If) Sobrou dados no stdin > Limpar stdin
    if (string[i] != '\n' && string[i] != EOF)
        while ((c = getchar()) != '\n' && c != EOF);

    // Colocar terminador '\0' no fim
    string[i] = '\0';
}

