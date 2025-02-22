#include "sockets.h"
#include <netdb.h>
#include <netinet/in.h>
#include <sys/socket.h>

/**
* main - entry point for client program
* @argc: number of input argument
* @argv: vector of inputs
*
* Return: 0 on success, -1 on failure
*/

int main(int argc, char **argv)
{
	ConnectionInfo_t conn;
	struct hostent *server_host_info;

	if (argc != 3)
	{
		printf("Usage: %s <host> <port>\n", argv[0]);
		exit(EXIT_FAILURE);
	}

	/* set server address */
	conn.server_addr.sin_family = AF_INET;
	conn.server_addr.sin_port = htons(atoi(argv[2]));
	server_host_info = gethostbyname(argv[1]);
	conn.server_addr.sin_addr.s_addr = *(in_addr_t *)server_host_info->h_addr;

	/* create client socket */
	conn.client_fd = socket(AF_INET, SOCK_STREAM, 0);
	if (conn.client_fd < 0)
	{
		perror("Client Socket Fail");
		exit(EXIT_FAILURE);
	}

	if (connect(conn.client_fd,
		   (struct sockaddr *)&conn.server_addr,
		   sizeof(conn.server_addr)) != 0)
	{
		perror("Connect Fail");
		exit(EXIT_FAILURE);
	}

	printf("Connected to %s:%s\n", argv[1], argv[2]);

	close(conn.client_fd);
	exit(EXIT_SUCCESS);
}

