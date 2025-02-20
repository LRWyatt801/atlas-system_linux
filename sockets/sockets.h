#ifndef SOCKETS_H
#define SOCKETS_H

/***** LIBRARIES *****/

#include <sys/socket.h>
#include <netinet/in.h>
#include <sys/un.h>
#include <arpa/inet.h>
#include <netdb.h>

/***** STRUCTS *****/

/**
 * struct ConnectionInfo_s - will contain all need info for connection
 * @server_fd: server fd for server socket
 * @client_fd: client fd for client socket connection
 * @server_addr: address for the server
 * @client_addr: address for the client connection
 * @client_addr_len: sizeof(client_addr);
 */

typedef struct ConnectionInfo_s
{
	int server_fd;
	int client_fd;
	struct sockaddr_in server_addr;
	struct sockaddr_in client_addr;
	socklen_t client_addr_len;
} ConnectionInfo_t;

/***** PROTOTYPES *****/

int init_server(ConnectionInfo_t *);

#endif /* SOCKETS_H */
