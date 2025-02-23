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

/***** PROTOTYPES *****/

void init_server(ConnectionInfo_t *);
void server_connect(ConnectionInfo_t *);
void recv_data(ConnectionInfo_t);
void parse_data(char *);

#endif /* API_H */
