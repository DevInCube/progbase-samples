#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include <openssl/ssl.h>

#include <progbase.h>
#include <progbase/net.h>
#include <progbase/console.h>

#define BUFFER_LEN 10000

// install: sudo apt-get install libssl-dev

// TLS Protocol

typedef struct Tls Tls;
struct Tls {
    SSL_CTX * ssl_ctx;
    SSL * conn;
};

Tls * Tls_init(Tls * self);
bool Tls_connect(Tls * self, TcpClient * client);
bool Tls_send(Tls * self, NetMessage * message);
bool Tls_receive(Tls * self, NetMessage * message);
void Tls_close(Tls * self);

int main(void) {
	TcpClient * client = TcpClient_init(&(TcpClient){});
    const char * serverHostname = "api.sunrise-sunset.org";
    char ipv4[20] = "";
    if (!Ip_resolveHostname(ipv4, serverHostname)) {
        perror("resolve address");
        return 1;
    }
    IpAddress * serverAddress = IpAddress_init(
        &(IpAddress){}, 
        ipv4, 
        443);  // default port for web servers
    NetMessage * message = NetMessage_init(
        &(NetMessage){},  // value on stack
        (char[BUFFER_LEN]){},  // array on stack 
        BUFFER_LEN); 
    
    if (!TcpClient_connect(client, serverAddress)) {
        perror("tcp connect");
        return 1;
    }
    //
    // create secure connection
    Tls * tls = Tls_init(&(Tls){});
    if(!Tls_connect(tls, client)) {
        perror("tls connect");
        return 1;
    }

    //
    // setup message object
    const char * path = "/json?lat=36.7201600&lng=-4.4203400";
    const char * httpVersion = "1.0";  // response differs in 1.1
    char httpWebRequest[256] = "";
    sprintf(httpWebRequest, 
        "GET %s HTTP/%s\r\n"
        "Host: %s\r\n"
        "\r\n", path, httpVersion, serverHostname);
    NetMessage_setDataString(message, httpWebRequest);
    //
    // send string to server
    printf(">> Send message to server %s:%d (%s):\r\n%s\r\n",
        IpAddress_address(serverAddress),
        IpAddress_port(serverAddress),
        serverHostname,
        message->buffer);

    if(!Tls_send(tls, message)) {
		perror("send");
		return 1;
	}
    //
    // receive response from server
    // use loop to receive big data buffers
    // the end of message if determined by 0 data length
    while (1) {
        if(!Tls_receive(tls, message)) {
            perror("recv");
            return 1;
        }
        if (NetMessage_dataLength(message) == 0) {
            // no more data to receive from server
            break;
        }
        printf(">> Response received from server (%d bytes):\r\n%s\r\n", 
            message->dataLength,
            message->buffer);
        // break;  // @todo why?
    }
    //
    // close secure connection
    Tls_close(tls);
    TcpClient_close(client);
	return 0;
}


// TLS Protocol

Tls * Tls_init(Tls * self) {
    self->conn = NULL;
    SSL_load_error_strings();
    SSL_library_init();
    SSL_CTX *ssl_ctx = SSL_CTX_new(SSLv23_client_method());
    self->ssl_ctx = ssl_ctx;
    return self;
}

bool Tls_connect(Tls * self, TcpClient * client) {
    //
    // create an SSL connection and attach it to the socket
    self->conn = SSL_new(self->ssl_ctx);
    SSL_set_fd(self->conn, client->socket);
    //
    // perform the SSL/TLS handshake with the server - when on the
    // server side, this would use SSL_accept()
    return SSL_connect(self->conn);
}

bool Tls_send(Tls * self, NetMessage * message) {
    // now proceed with HTTP traffic, using SSL_read instead of recv() and
    // SSL_write instead of send(), and SSL_shutdown/SSL_free before close()
    int bytes = SSL_write(self->conn, (void *)message->buffer, message->dataLength);
    message->sentDataLength = bytes;
    return bytes >= 0;
}

bool Tls_receive(Tls * self, NetMessage * message) {
    // SSL_read
    int bytes = SSL_read(self->conn, message->buffer, message->bufferLength);
    if (bytes < message->bufferLength) {
        message->buffer[bytes] = '\0';  // nul-terminate string
    }
    message->dataLength = bytes;
    return bytes >= 0;
}

void Tls_close(Tls * self) {
    SSL_shutdown(self->conn);
    SSL_free(self->conn);
}
