#pragma once

#include <progbase/net.h>
#include <progbase/list.h>

#define MAX_COMMAND_LEN 100
#define MAX_ERROR_LEN 256

typedef struct {
	char command[MAX_COMMAND_LEN];
} Request;

Request parseRequest(const char * str);

typedef struct {
	bool status;
	enum {
		RES_NUMBERS,
		RES_STRINGS
	} itemsType;
	List * data;
	char error[MAX_ERROR_LEN];
} Response;

void Response_cleanup(Response * self);
void Response_init(Response * self);
void Response_addNumber(Response * self, int number);
void Response_addString(Response * self, const char * str);
void Response_setError(Response * self, const char * error);
void Response_setItemsType(Response * self, int itemsType);
void Response_toMessage(Response * res, NetMessage * message);

typedef void (*RequestHandler)(Request * req, Response * res);

typedef struct {
	char command[MAX_COMMAND_LEN];
	RequestHandler handler;
} CommandHandler;

void processRequest(Request * req, Response * res, CommandHandler * handlers, int len);
