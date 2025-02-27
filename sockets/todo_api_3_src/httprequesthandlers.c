#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "api.h"

/**
* recv_data - recieves and prints data sent by client
* @conn: needed connection info
* @request_data: struct containing HTTP request data
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

	print_stuff(request_data);
	send(conn.client_fd, okresponse, strlen(okresponse), 0);
}

/**
* parse_data - parses the HTTP request into its different components
* @buff: buffer to parse
* @request_data: struct that holds data about a request
*
* Return: n/a
*/

void parse_data(char *buff, HttpRequest_t *request_data)
{
	char *request_tok = NULL;
	char *headerbrk;

	request_data->header_list = NULL;

	/* get first line containing method, path, and version */
	request_tok = strtok(buff, "\r\n");
	if (sscanf(request_tok, "%s %s %s",
		   request_data->method,
		   request_data->fullpath,
		   request_data->version) < 3)
	{
		perror("sscanf error");
		return;
	}
	parse_path(request_data);

	while ((request_tok = strtok(NULL, "\r\n")) != NULL)
	{
		headerbrk = strchr(request_tok, ':');
		/* use this check to determine if header */
		if (!headerbrk)
		{
			strcpy(request_data->allquery, request_tok);
			parse_query(request_data);
		}
		else
		{
			*headerbrk = '\0';
			parse_header(request_data,
				     request_tok,
				     headerbrk + (headerbrk[1] == ' ' ? 2 : 1));
		}
	}
}

/**
 * print_stuff - function to print stuff about request
 * @request_data: struct that contains info about request
 *
 * Return: n/a
 */

void print_stuff(HttpRequest_t *request_data)
{
	HttpKeyValuePair_t *tmp = NULL;

	printf("Path: %s\n", request_data->path);
	/*printf("Method: %s\n", request_data->method); Uncomment for method print */
	while (request_data->query_list)
	{
		tmp = request_data->query_list;
		printf("Body: \"%s\" -> \"%s\"\n", tmp->key, tmp->value);
		request_data->query_list = tmp->next;
		free(tmp);
	}
}

