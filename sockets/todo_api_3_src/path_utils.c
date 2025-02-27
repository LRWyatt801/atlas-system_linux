#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "api.h"

/**
* parse_path - parses the http request path into path and queries
* @request_data: struct holding data of HTTP request
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
		parse_query(request_data);
	}
	else
		strcpy(request_data->path, request_data->fullpath);
}

/**
* parse_query - parses queries into a linked list
* @request_data: struct holding data of HTTP request
*
* Return: n/a
*/

void parse_query(HttpRequest_t *request_data)
{
	HttpKeyValuePair_t *new_query = NULL, *last = NULL;
	char *keyvaluebrk, *query_str, *token;

	/* init new query */
	query_str = strdup(request_data->allquery);
	if (!query_str)
		return;

	token = strtok(query_str, "&");
	
	while (token)
	{
		keyvaluebrk = strchr(token, '=');
		if (!keyvaluebrk)
		{
			perror("parse_query: key/value error\n");
			free(query_str);
			return;
		}
		*keyvaluebrk = '\0';
		new_query = malloc(sizeof(HttpKeyValuePair_t));
		if (!new_query)
		{
			perror("Malloc failed");
			free(query_str);
			return;
		}
		new_query->key = strdup(token);
		new_query->value = strdup(keyvaluebrk + 1);
		new_query->next = NULL;

		if (!request_data->query_list)
			request_data->query_list = new_query;
		else
		{
			last = request_data->query_list;
			while (last->next)
				last = last->next;
			last->next = new_query;
		}

		token = strtok(NULL, "&");
		if (!token)
			break;
	}
	free(query_str);
}

