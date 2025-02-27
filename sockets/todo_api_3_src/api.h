#ifndef API_H
#define API_H

/***** BERKELEY SOCKETS HEADERS *****/

#include <netinet/in.h>

/***** GLIBC HEADERS *****/

/***** MACROS *****/

#define BUFF_SIZE 1024
#define PORT 8080

/***** STRUCTS *****/

/**
 * struct ConnectionInfo_s - will contain all need info for connection
 * @server_fd: server fd for server socket
 * @client_fd: client fd for client socket connection
 * @buff: buffer for msg
 * @server_addr: address for the server
 * @client_addr: address for the client connection
 * @client_addr_len: sizeof(client_addr);
 */

typedef struct ConnectionInfo_s
{
	int server_fd;
	int client_fd;
	char buff[BUFF_SIZE];
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	socklen_t client_addr_len;
} ConnectionInfo_t;

/**
 * struct HttpKeyValuePair_s - a singly linked list of HTTP queries
 * @origquery: original query, contains key/value pair
 * @key: key in query
 * @value: value in query
 * @next: pointer to next query
 */

typedef struct HttpKeyValuePair_s
{
	char *origquery;
	char *key;
	char *value;
	struct HttpKeyValuePair_s *next;
} HttpKeyValuePair_t;

/**
 * struct HttpRequest_s - stuct to hold parsed http request
 * @method: method of HTTP request
 * @fullpath: full path given with request, include path and queries
 * @version: version of HTTP request
 * @path: path only, does NOT include queries
 * @allquery: string of all given queries
 * @query_list: linked list of parsed key/value queries
 * @header_list: linked list of parsed header/value pairs
 */

typedef struct HttpRequest_s
{
	char method[8];
	char fullpath[BUFF_SIZE];
	char version[BUFF_SIZE];
	char path[BUFF_SIZE];
	char allquery[BUFF_SIZE];
	struct HttpKeyValuePair_s *query_list;
	struct HttpKeyValuePair_s *header_list;
} HttpRequest_t;

/***** PROTOTYPES *****/

void init_server(ConnectionInfo_t *);
void server_connect(ConnectionInfo_t *);
void recv_data(ConnectionInfo_t, HttpRequest_t *);
void parse_data(char *, HttpRequest_t *);
void parse_path(HttpRequest_t *);
void parse_query(HttpRequest_t *);
void parse_header(HttpRequest_t *, char *, char *);

void print_stuff(HttpRequest_t *);

#endif /* API_H */
