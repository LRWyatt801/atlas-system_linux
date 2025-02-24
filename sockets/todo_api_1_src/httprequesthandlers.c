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

void recv_data(ConnectionInfo_t conn, HttpRequest_t *request_data)
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

	parse_data(conn.buff, request_data);

	send(conn.client_fd, okresponse, strlen(okresponse), 0);
}


