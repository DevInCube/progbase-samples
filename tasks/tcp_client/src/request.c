#include <string.h>
#include <ctype.h>
#include <jansson.h>

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

void processRequest(Request * req, Response * res, CommandHandler * handlers, int len) {
	RequestHandler handler = getCommandRequestHandler(handlers, len, req->command);
	if (handler == NULL) {
		char tmp[100] = "";
		sprintf(tmp, "Command `%s` not found", req->command);
		Response_setError(res, tmp);
		return;
	}
	handler(req, res);
}

void Response_setError(Response * self, const char * error) {
	self->status = false;
	strcpy(self->error, error);
}

void Response_setItemsType(Response * self, int itemsType) {
	self->itemsType = itemsType;
}

void Response_addString(Response * self, const char * str) {
	void * item = malloc(strlen(str) + 1);
	strcpy(item, str);
	List_add(self->data, item);
}

void Response_addNumber(Response * self, int number) {
	int * item = malloc(sizeof(int));
	*item = number;
	List_add(self->data, item);
}

void Response_init(Response * self) {
	self->status = true;
	self->itemsType = RES_NUMBERS;
	self->data = List_new();
	strcpy(self->error, "");
}

void Response_cleanup(Response * self) {
	if (self->data != NULL) {
		for (int i = 0; i < List_count(self->data); i++) {
			free(List_get(self->data, i));
		}
		List_free(&self->data);
	}
}

void Response_toMessage(Response * res, NetMessage * message) {
	json_t * jobj = json_object();
	json_object_set(jobj, "status", json_boolean(res->status));
	if (!res->status) {
		json_object_set(jobj, "error", json_string(res->error));
	} else {
		json_t * jarray = json_array();
		for (int i = 0; i < List_count(res->data); i++) {
			void * value = List_get(res->data, i);
			json_t * jvalue = (res->itemsType == RES_NUMBERS) 
				? json_integer(*(int *)value)
				: json_string((char *)value);
			json_array_append_new(jarray, jvalue);
		}
		json_object_set_new(jobj, "data", jarray);
	}
	const char * strDump = json_dumps(jobj, JSON_COMPACT);
	NetMessage_setDataString(message, strDump);
	free((void *)strDump);
	json_decref(jobj);
}
