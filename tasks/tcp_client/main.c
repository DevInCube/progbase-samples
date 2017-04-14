#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>
#include <progbase/net.h>

#define BUFFER_LEN 1024
#define MAX_COMMAND_LEN 100
typedef struct {
	char command[MAX_COMMAND_LEN];
} Request;

void processRequest(Request * req, NetMessage * message);
Request parseRequest(const char * str);

int main(int argc, char * argv[]) {
	if (argc < 2) {
		puts("Please, specify server port in command line arguments");
		return 1;
	}
	const int port = atoi(argv[1]);

	TcpListener * server = TcpListener_init(&(TcpListener){});
    IpAddress * address = IpAddress_initAny(&(IpAddress){}, port);
    if(!TcpListener_bind(server, address)) {
        perror("tcp bind");
        return 1;
    }
    if (!TcpListener_start(server)) {
        perror("tcp server start");
        return 1;
    }
    printf("TCP Server is listening on port %d\n", 
        IpAddress_port(TcpListener_address(server)));
    
    NetMessage * message = NetMessage_init(
        &(NetMessage){},  // value on stack
        (char[BUFFER_LEN]){},  // array on stack 
        BUFFER_LEN);
	//
    // to store information about current client
    TcpClient client;
    while (1) {
		//
        // wait for someone to connect to server
        TcpListener_accept(server, &client);
        // wait for data from client
        if(!TcpClient_receive(&client, message)) {
			perror("recv");
			return 1;
		}
        IpAddress * clientAddress = TcpClient_address(&client);
        printf("Received message from %s:%d (%d bytes): `%s`\n",
            IpAddress_address(clientAddress),  // client IP-address
            IpAddress_port(clientAddress),  // client port
            NetMessage_dataLength(message),
            NetMessage_data(message));

		Request req = parseRequest(NetMessage_data(message));
		processRequest(&req, message);
		
        // send data back
        if(!TcpClient_send(&client, message)) {
			perror("send");
			return 1;
		}
        // close tcp connection
        TcpClient_close(&client);
    }
    // close listener
    TcpListener_close(server);
	return 0;
}

typedef void (*RequestHandler)(Request * req, NetMessage * message);
typedef struct {
	char command[MAX_COMMAND_LEN];
	RequestHandler handler;
} CommandHandler;

void numbersHandler(Request * req, NetMessage * message);
void bitsHandler(Request * req, NetMessage * message);
void stringsHandler(Request * req, NetMessage * message);

static CommandHandler handlers[] = {
	{ "numbers", numbersHandler},
	{ "bits", bitsHandler},
	{ "strings", stringsHandler},
};

RequestHandler getCommandRequestHandler(const char * command) {
	for (int i = 0; i < sizeof(handlers) / sizeof(handlers[0]); i++) {
		CommandHandler handler = handlers[i];
		if (0 == strcmp(handler.command, command)) {
			return handler.handler;
		}
	}
	return NULL;
}

void processRequest(Request * req, NetMessage * message) {
	RequestHandler handler = getCommandRequestHandler(req->command);
	if (handler == NULL) {
		NetMessage_setDataString(message, "Command not found");
		return;
	}
	handler(req, message);
}

Request parseRequest(const char * str) {
	Request req = {
		.command = ""
	};
	int commandEnd = 0;
	while (isalpha(str[commandEnd])) commandEnd++;
	if (commandEnd >= MAX_COMMAND_LEN) commandEnd = MAX_COMMAND_LEN - 1;
	strncpy(req.command, str, commandEnd);
	req.command[commandEnd] = 0;
	return req;
}
