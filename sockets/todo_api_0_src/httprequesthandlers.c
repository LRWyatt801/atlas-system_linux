#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "api.h"

/**
* recv_data - recieves and prints data sent by client
* @conn: needed connection info
*
* Return: n/a
*/

void recv_data(ConnectionInfo_t conn)
{
	int datarecv;
	const char *okresponse =
		"HTTP/1.1 200 OK\r\n\r\n";


	datarecv = recv(conn.client_fd, &conn.buff, BUFF_SIZE - 1, 0);
	if (datarecv < 0)
	{
		perror("recv error");
		exit(EXIT_FAILURE);
	}
	else if (datarecv == 0)
		printf("0 data sent\n");

	conn.buff[datarecv] = '\0';
	printf("Raw request: \"%s\"\n", conn.buff);

	parse_data(conn.buff);

	send(conn.client_fd, okresponse, strlen(okresponse), 0);
}

/**
* parse_data - parses the data/msg into different components
* @buff: buffer to parse
*
* Return: n/a
*/

void parse_data(char *buff)
{
	char method[16], path[64], version[64];

	if (sscanf(buff, "%s %s %s", method, path, version) < 3)
	{
		perror("sscanf error");
		return;
	}

	printf("Method: %s\n", method);
	printf("Path: %s\n", path);
	printf("Version: %s\n", version);
}
