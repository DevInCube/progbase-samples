/** @file
    @brief sample web module
*/

#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <stddef.h>  // ptrdiff_t
#include <signal.h>
#include <errno.h>
#include <unistd.h>
#include <assert.h>

#include <stdio.h>
#include <stdlib.h>
#include <socket.h>
#include <http.h>
#include <web.h>

#define CRLF "\r\n"

const char * METHODS[] = {"GET", "POST", "PUT", "DELETE"};
typedef enum {
    HTTP_GET, HTTP_POST, HTTP_PUT, HTTP_DELETE
} HTTP_METHOD;

socket_t * g_serverSock;

static void inthandler(int sig);
static void cleanup_server(void);

void Web_runServer(Web_requestHandler handler) {
	assert(handler != NULL);

	int sPort = 5000;

    atexit(cleanup_server);
    signal(SIGINT, inthandler);

    g_serverSock = socket_new();
    while (1) {
        if (socket_bind(g_serverSock, sPort) == SOCKET_ERR) {
            printf("Port %i can't be binded\n", sPort);
            sPort++;
            //exit(1);
        } else {
            printf("Binded on port %i\n", sPort);
            break;
        }
    }
    socket_listen(g_serverSock);

    char buf[10000];
    socket_t * client = NULL;
    while (1) {
        printf("Accepting clients...\n");
        client = socket_accept(g_serverSock);
        if (NULL == client) {
            printf("NULL client\n");
            exit(1);
        }
        int readStatus = socket_read(client, buf, sizeof(buf));
        if (0 >= readStatus) {
            printf("Skipping empty request.\n");
            socket_close(client);
            socket_free(client);
            continue;
        }
        printf(">> Got request (read %i):\n`%s`\n", readStatus, buf);

        http_request_t request = http_request_parse(buf);

		char buffer[1000] = "";
		char * body = handler(buffer, request.uri);
		char httpResponse[1024] = "";
		sprintf(httpResponse,
			"HTTP/1.1 200 OK\n"
			"Content-Type: text/html\n"
			"Content-Length: %zu\n"
			"\n%s", strlen(body), body);
		
		socket_write_string(client, httpResponse);
		socket_close(client);

        socket_free(client);
    }
    socket_free(g_serverSock);
}

void inthandler(int sig) {
    exit(0);  // call to cleanup_server at exit
}

void cleanup_server(void) {
    printf("Cleanup server.\n");
    socket_close(g_serverSock);
    socket_free(g_serverSock);
}