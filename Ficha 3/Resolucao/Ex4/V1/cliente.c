
#include <stdio.h>
#include <string.h>
#include <strings.h>
#include <stdlib.h>
#include <arpa/inet.h>
#include <sys/socket.h>
#include <unistd.h>
#include <stdio.h>
#include <netinet/in.h>
#include <netdb.h>

#define h_addr h_addr_list[0] /* for backward compatibility */

#define BUFLEN 512 // Tamanho do buffer
#define PORT 9876  // Porto para recepção das mensagens

void erro(char *s)
{
	perror(s);
	exit(1);
}

int main(int argc, char *argv[])
{
	struct sockaddr_in si_outra;
	struct hostent *hostPtr;
	char endServer[100];
	int s, recv_len;
	socklen_t slen = sizeof(si_outra);
	char buf[BUFLEN];

	if (argc != 4)
	{
		erro("cliente <endereço IP servidor> <porto> <palavra>\n");
		exit(-1);
	}

	strcpy(endServer, argv[1]);
	if ((hostPtr = gethostbyname(endServer)) == 0)
		erro("Não consegui obter endereço");

	// Preenchimento da socket address structure
	bzero((void *)&si_outra, sizeof(si_outra));
	si_outra.sin_family = AF_INET;
	si_outra.sin_addr.s_addr = ((struct in_addr *)(hostPtr->h_addr))->s_addr;
	si_outra.sin_port = htons((short)atoi(argv[2]));

	// Cria um socket para o envio de pacotes UDP
	if ((s = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP)) == -1)
	{
		erro("Erro na criação do socket");
	}

	// Enviar a mensagem ao  com sendto Servidor
	if (sendto(s, argv[3], 1 + strlen(argv[3]), 0, (struct sockaddr *)&si_outra, (socklen_t)slen) == -1)
	{
		erro("Erro no sendto");
	}

	// Aguarda a resposta do servidor
	if ((recv_len = recvfrom(s, buf, BUFLEN, 0, (struct sockaddr *)&si_outra, (socklen_t *)&slen)) == -1)
	{
		erro("Erro no recvfrom");
	}
	// Para ignorar o restante conteúdo (anterior do buffer)
	buf[recv_len] = '\0';

	printf("\"%s\"\n", buf);

	// Fecha socket e termina programa
	close(s);
	return 0;
}
