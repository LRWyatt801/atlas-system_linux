#include <netinet/in.h>
#include <stdio.h>
#include <stdlib.h>
#include <sys/socket.h>
#include <unistd.h>

#define PORT 12345
#define QUEUE_LIMIT 5

/**
* main - entry point for program
*
* Return: n/a
*/

int main(void)
{
	int servSoc;
	struct sockaddr_in addrport;

	/* create socket */
	servSoc = socket(PF_INET, SOCK_STREAM, 0);
	if (servSoc < 0)
	{
		perror("socket error");
		exit(EXIT_FAILURE);
	}

	/* set up address struct and len */
	addrport.sin_family = PF_INET;
	addrport.sin_addr.s_addr = INADDR_ANY;
	addrport.sin_port = htons(PORT);

	if (bind(servSoc, (struct sockaddr *)&addrport, sizeof(addrport)) != 0)
	{
		perror("bind error");
		close(servSoc);
		exit(EXIT_FAILURE);
	}

	if (listen(servSoc, QUEUE_LIMIT) != 0)
	{
		perror("listen error");
		close(servSoc);
		exit(EXIT_FAILURE);
	}

	printf("Server listening on port %d\n", PORT);

	for (;;)
	{}
}

