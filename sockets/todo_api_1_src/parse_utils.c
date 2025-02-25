#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "api.h"


/**
* parse_data - parses the data/msg into different components
* @buff: buffer to parse
*
* Return: n/a
*/

void parse_data(char *buff, HttpRequest_t *request_data)
{
	HttpQuery_t *tmp;

	if (sscanf(buff, "%s %s %s", request_data->method, request_data->fullpath, request_data->version) < 3)
	{
		perror("sscanf error");
		return;
	}

	parse_path(request_data);

	printf("Method: %s\n", request_data->method);
	printf("Path: %s\n", request_data->path);
	while (request_data->query_list)
	{
		tmp = request_data->query_list;
		printf("Query: \"%s\" -> \"%s\"\n", tmp->key, tmp->value);
		request_data->query_list = tmp->next;
		free(tmp);
	}
}

/**
* parse_queries - parses the http queries in to key and value
* @queries: linked list to store query pairs in
*
* Return: n/a
*/

void parse_path(HttpRequest_t *request_data)
{
	request_data->query_list = NULL;
	char *querymark = strchr(request_data->fullpath, '?');

	if (querymark)
	{
		*querymark = '\0';
		strcpy(request_data->path, request_data->fullpath);
		strcpy(request_data->allquery, querymark + 1);
	}
	else
		strcpy(request_data->path, request_data->fullpath);
}
