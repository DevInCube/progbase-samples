#pragma once

#include <progbase/net.h>

#define MAX_COMMAND_LEN 100

typedef struct {
	char command[MAX_COMMAND_LEN];
} Request;

Request parseRequest(const char * str);

typedef void (*RequestHandler)(Request * req, NetMessage * message);

typedef struct {
	char command[MAX_COMMAND_LEN];
	RequestHandler handler;
} CommandHandler;

void processRequest(Request * req, NetMessage * message, CommandHandler * handlers, int len);
