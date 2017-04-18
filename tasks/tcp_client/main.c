#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <string.h>
#include <ctype.h>
#include <time.h>
#include <progbase/net.h>

#include <request.h>

#define BUFFER_LEN 10240

void numbersHandler(Request * req, Response * res);
void bitsHandler(Request * req, Response * res);
void stringsHandler(Request * req, Response * res);
void strNumHandler(Request * req, Response * res);

static CommandHandler handlers[] = {
	{ "numbers", numbersHandler},
	{ "bits", bitsHandler},
	{ "strings", stringsHandler},
    { "strnums", strNumHandler},
};

int main(int argc, char * argv[]) {
	if (argc < 2) {
		puts("Please, specify server port in command line arguments");
		return 1;
	}
	srand(time(0));
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
        puts(">> Waiting for connection...");
		//
        // wait for someone to connect to server
        TcpListener_accept(server, &client);
        // wait for data from client
        if(!TcpClient_receive(&client, message)) {
			perror("recv");
			return 1;
		}
        IpAddress * clientAddress = TcpClient_address(&client);
        printf(">> Received message from %s:%d (%d bytes): `%s`\n",
            IpAddress_address(clientAddress),  // client IP-address
            IpAddress_port(clientAddress),  // client port
            NetMessage_dataLength(message),
            NetMessage_data(message));

		Request req = parseRequest(NetMessage_data(message));
        Response res;
        Response_init(&res);
		processRequest(&req, &res, handlers, sizeof(handlers) / sizeof(handlers[0]));
        Response_toMessage(&res, message);
		Response_cleanup(&res);
        // send data back
        if(!TcpClient_send(&client, message)) {
			perror("send");
			return 1;
		}
        printf(">> String sent to client:\r\n%s\r\n", NetMessage_data(message));
        // close tcp connection
        TcpClient_close(&client);
    }
    // close listener
    TcpListener_close(server);
	return 0;
}
