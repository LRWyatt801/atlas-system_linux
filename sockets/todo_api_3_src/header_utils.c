#include <stdio.h>
#include <stdlib.h>
#include <string.h>

#include "api.h"

/**
* parse_header - parses HTTP header/value pairs
* @request_data: struct containing data on HTTP request
* @hdr_name: str with header name
* @hdr_value: str with header value
*
* Return: n/a
*/

void parse_header(HttpRequest_t *request_data, char *hdr_name, char *hdr_value)
{
	HttpKeyValuePair_t *new_hdr, *last_hdr;

	new_hdr = malloc(sizeof(HttpKeyValuePair_t));
	if (!new_hdr)
	{
		perror("parse_data: malloc fail");
		return;
	}
	new_hdr->key = strdup(hdr_name);
	new_hdr->value = strdup(hdr_value);
	new_hdr->next = NULL;
	if (!request_data->header_list)
		request_data->header_list = new_hdr;
	else
	{
		last_hdr = request_data->header_list;
		while (last_hdr->next)
			last_hdr = last_hdr->next;
		last_hdr->next = new_hdr;
	}
}

