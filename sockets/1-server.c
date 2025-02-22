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
	ConnectionInfo_t conn;

	/* create socket */
	init_server(&conn);
	server_connect(&conn);
	exit(EXIT_SUCCESS);
}

/**
* init_server - initializes a socket for a server
* @conn: a struct containing info needed for socket connections
*
* Return: n/a
*/

void init_server(ConnectionInfo_t *conn)
{
	conn->server_fd = socket(PF_INET, SOCK_STREAM, 0);
	if (conn->server_fd < 0)
	{
		perror("socket error");
		exit(EXIT_FAILURE);
	}

	/* set up address struct and len */
	conn->server_addr.sin_family = PF_INET;
	conn->server_addr.sin_addr.s_addr = INADDR_ANY;
	conn->server_addr.sin_port = htons(PORT);

	if (bind(conn->server_fd,
	   (struct sockaddr *)&conn->server_addr,
	   sizeof(conn->server_addr)) != 0)
	{
		perror("bind error");
		close(conn->server_fd);
		exit(EXIT_FAILURE);
	}
}

/**
* server_connect - set the server to listen and connect
* @conn: a struct containing needed info for socket connections
*
* Return: n/a
*/

void server_connect(ConnectionInfo_t *conn)
{
	if (listen(conn->server_fd, QUEUE_LIMIT) != 0)
	{
		perror("listen error");
		close(conn->server_fd);
		exit(EXIT_FAILURE);
	}

	printf("Server listening on port %d\n", PORT);

	conn->client_addr_len = sizeof(conn->client_addr);
	conn->client_fd = accept(conn->server_fd,
			       (struct sockaddr *)&conn->client_addr,
			       &conn->client_addr_len);
	if (conn->client_fd < 0)
	{
		perror("accept error");
		close(conn->client_fd);
		close(conn->server_fd);
		exit(EXIT_FAILURE);

	}
	printf("Client connected: %s\n", inet_ntoa(conn->client_addr.sin_addr));
}
