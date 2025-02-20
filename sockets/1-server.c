#include <stdio.h>
#include <stdlib.h>
#include <unistd.h>

#include "sockets.h"

#define PORT 12345
#define QUEUE_LIMIT 5

/**
* main - entry point for program
*
* Return: n/a
*/

int main(void)
{
	int server_fd, new_client_fd;
	struct sockaddr_in serv_addr, client_addr;

	/* create socket */
	server_fd = socket(PF_INET, SOCK_STREAM, 0);
	if (server_fd < 0)
	{
		perror("socket error");
		exit(EXIT_FAILURE);
	}

	/* set up address struct and len */
	serv_addr.sin_family = PF_INET;
	serv_addr.sin_addr.s_addr = INADDR_ANY;
	serv_addr.sin_port = htons(PORT);

	if (bind(server_fd, (struct sockaddr *)&serv_addr, sizeof(serv_addr)) != 0)
	{
		perror("bind error");
		close(server_fd);
		exit(EXIT_FAILURE);
	}

	if (listen(server_fd, QUEUE_LIMIT) != 0)
	{
		perror("listen error");
		close(server_fd);
		exit(EXIT_FAILURE);
	}

	printf("Server listening on port %d\n", PORT);

	
	socklen_t client_addrlen = sizeof(client_addr);
	new_client_fd = accept(server_fd, (struct sockaddr *)&client_addr, &client_addrlen);
	if (new_client_fd < 0)
	{
		perror("accept error");
		close(new_client_fd);
		close(server_fd);
		exit(EXIT_FAILURE);

	}
	printf("Client connected: %s\n", inet_ntoa(client_addr.sin_addr));
	exit(EXIT_SUCCESS);
}

