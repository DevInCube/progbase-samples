#include <string.h>
#include <ctype.h>

#include <request.h>

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

RequestHandler getCommandRequestHandler(CommandHandler * handlers, int len, const char * command) {
	for (int i = 0; i < len; i++) {
		CommandHandler handler = handlers[i];
		if (0 == strcmp(handler.command, command)) {
			return handler.handler;
		}
	}
	return NULL;
}

void processRequest(Request * req, NetMessage * message, CommandHandler * handlers, int len) {
	RequestHandler handler = getCommandRequestHandler(handlers, len, req->command);
	if (handler == NULL) {
		NetMessage_setDataString(message, "Command not found");
		return;
	}
	handler(req, message);
}
