#include <stdio.h>
#include <sys/socket.h>
#include <arpa/inet.h>
#include <stdio.h>
#include <stdlib.h>

#define HSTATIC_EPOLL_EVENTS 64
#define HSTATIC_PORT 8080
#define HSTATIC_TCP_BACKLOG 4

/**
 * Encapsulates the properties of the server.
 */
typedef struct server {
	// file descriptor of the socket in passive
	// mode to wait for connections.
	int listen_fd;
} server_t;

/**
 * Creates a socket for the server and makes it passive such that
 * we can wait for connections on it later.
 */
int server_listen(server_t* server) {
	int err = 0;
	struct sockaddr_in server_addr = { 0 };

	// `sockaddr_in` provides ways of representing a full address
	// composed of an IP address and a port.
	//
	// SIN_FAMILY   address family          AF_INET refers to the
	//                                      address family related to
	//                                      internet addresses
	//
	// S_ADDR       address (ip) in network byte order (big endian)
	// SIN_PORT     port in network byte order (big endian)
	server_addr.sin_family      = AF_INET;
	server_addr.sin_addr.s_addr = htonl(INADDR_ANY);
	server_addr.sin_port        = htons(HSTATIC_PORT);

	// The `socket(2)` syscall creates an endpoint for communication
	// and returns a file descriptor that refers to that endpoint.
	//
	// It takes three arguments (the last being just to provide
	// greater specificity):
	// -    domain (communication domain)
	//      AF_INET              IPv4 Internet protocols
	//
	// -    type (communication semantics)
	//      SOCK_STREAM          Provides sequenced, reliable,
	//                           two-way, connection-based byte
	//                           streams.
    err = (server->listen_fd = socket(AF_INET, SOCK_STREAM, 0));
	if (err == -1) {
		perror("socket");
		printf("Failed to create socket endpoint\n");
		return err;
	}

    // bind() assigns the address specified to the socket referred 
    // to by the file descriptor (`listen_fd`).
    //
    // Here we cast `sockaddr_in` to `sockaddr` and specify the
    // length such that `bind` can pick the values from the
    // right offsets when interpreting the structure pointed to.
	err = bind(server->listen_fd, (struct sockaddr*)&server_addr, sizeof(server_addr));
	if (err == -1) {
		perror("bind");
		printf("Failed to bind socket to address\n");
		return err;
	}
	// Makes the server socket non-blocking such that calls that
	// would block return a -1 with EAGAIN or EWOULDBLOCK and
	// return immediately.

	return 0;
}


/**
 * Accepts new connections and then prints `Hello World` to
 * them.
 */
int server_accept(server_t* server);


/**
 * Main server routine.
 *
 *      -       instantiates a new server structure that holds the
 *              properties of our server;
 *      -       creates a socket and makes it passive with
 *              `server_listen`;
 *      -       accepts new connections on the server socket.
 *
 */
int main() {
	int err = 0;
	server_t server = { 0 };

    int PORT = 5000;
	err = server_listen(&server);
	if (err) {
		printf(
            "Failed to listen on address 0.0.0.0:%d\n",
            PORT
        );
		return err;
	} else {
		printf(
            "Success to listen on address 0.0.0.0:%d\n",
            PORT
        );
    }



	/* for (;;) { */
	/* 	err = server_accept(&server); */
	/* 	if (err) { */
	/* 		printf("Failed accepting connection\n"); */
	/* 		return err; */
	/* 	} */
	/* } */

	return 0;
}
