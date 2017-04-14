#include <stdlib.h>
#include <stdio.h>
#include <errno.h>
#include <ctype.h>
#include <string.h>
#include <progbase/net.h>

/**

Сервер містить фіксований масив строк. При старті сервера строки у масиві порожні.

Клієнт може присилати запити серверу на зміну строки по певному індексу в масиві:
	* push <index> <char> - додати символ у кінець строки
	* pop <index> - забрати символ з кінця строки
	* clear <index> - очистити строку
	* get <index> - отримати строку за індексом
	* count - отримати кількість строк у масиві (розмір масиву)
	* getall - отримати масив всіх строк

У відповідь на правильні запити сервер відправляє клієнту строку або масив строк, 
кожна строка у відповіді записується у окремому рядку

*/

#define BUFFER_LEN 1024
#define ARRAY_LEN 3
#define STRING_LEN 10

typedef struct ClientRequest {
	char action[100];
	int index;
	char character;
} ClientRequest;

ClientRequest parseRequest(const char * msgStr) {
	ClientRequest request = {
		.action = "",
		.index = 0,
		.character = '\0'
	};
	int chIndex = 0;
	while (isalpha(msgStr[chIndex])) {
		chIndex ++;
	}
	strncpy(request.action, msgStr, chIndex);
	char * next = NULL;
	request.index = strtol(msgStr + chIndex, &next, 10);
	if (msgStr + chIndex != next) {
		if (*next == ' ') {
			request.character = *(next + 1);
		}
	}
	return request;
}

void printRequest(ClientRequest request) {
	printf("Client request is: `%s` `%i` `%c`\n", 
		request.action,
		request.index,
		request.character);
}

int main(void) {
	char strings[ARRAY_LEN][STRING_LEN] = {
		"Hi",
		"I'm",
		"Server!!!"
	};

	//
    // create UDP server
    UdpClient * server = UdpClient_init(&(UdpClient){});
    IpAddress * address = IpAddress_initAny(&(IpAddress){}, 9998);
    if (!UdpClient_bind(server, address)) {
        perror("Can't start server");
        return 1;
    }
    printf("Udp server started on port %d\n", 
        IpAddress_port(UdpClient_address(server)));
    
    NetMessage * message = NetMessage_init(
        &(NetMessage){},  // value on stack
        (char[BUFFER_LEN]){},  // array on stack 
        BUFFER_LEN);

    IpAddress clientAddress;
    while (1) {
        puts("Waiting for data...");
        //
        // blocking call to receive data
        // if someone send it
        if(!UdpClient_receiveFrom(server, message, &clientAddress)) {
			perror("recv");
			return 1;
		}

		ClientRequest req = parseRequest(NetMessage_data(message));
		printRequest(req);
		if (req.index < 0 || req.index >= ARRAY_LEN) {
			NetMessage_setDataString(message, "Error: index out of bounds");
		} else {
			if (0 == strcmp(req.action, "count")) {
				char tmp[10];
				sprintf(tmp, "%i", ARRAY_LEN);
				NetMessage_setDataString(message, tmp);
			} else if (0 == strcmp(req.action, "get")) {
				NetMessage_setDataString(message, strings[req.index]);
			} else if (0 == strcmp(req.action, "clear")) {
				strings[req.index][0] = '\0';
				NetMessage_setDataString(message, strings[req.index]);
			} else if (0 == strcmp(req.action, "push")) {
				char * str = strings[req.index];
				if (strlen(str) >= STRING_LEN - 1) {
					NetMessage_setDataString(message, "Error: String is full'");
				} else {
					str[strlen(str)] = req.character;
					str[strlen(str) + 1] = '\0';
					NetMessage_setDataString(message, strings[req.index]);
				}
			} else if (0 == strcmp(req.action, "pop")) {
				char * str = strings[req.index];
				if (strlen(str) == 0) {
					NetMessage_setDataString(message, "Error: Can't pop empty string'");
				} else {
					str[strlen(str) - 1] = '\0';
					NetMessage_setDataString(message, strings[req.index]);
				}
			} else {
				NetMessage_setDataString(message, "Error: Unknown request");
			}
		}
        //
        // send echo response
        if (!UdpClient_sendTo(server, message, &clientAddress)) {
			perror("send");
			return 1;
		}
    }
    //
    // close server
    UdpClient_close(server);
	return 0;
}
