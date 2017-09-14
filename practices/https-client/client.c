#include <stdlib.h>
#include <stdio.h>
#include <errno.h>

#include <progbase.h>
#include <progbase/net.h>
#include <progbase/console.h>

#define BUFFER_LEN 1000

int main(void) {
    // create TCP client
	TcpClient * tcpClient = TcpClient_init(&(TcpClient){});
    const char * serverHostname = "country.register.gov.uk";
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

    // initialize SSL
    Ssl * ssl = Ssl_init(&(Ssl){});
    // create secure connection
    if (!TcpClient_connectSecure(tcpClient, serverAddress, ssl)) {
        perror("tcp connect");
        return 1;
    }
    printf(">> Connected to server (%s:%i)\n",
        IpAddress_address(serverAddress),
        IpAddress_port(serverAddress));
    //
    // create secure connection
    // Ssl * sslClient = Ssl_init(&(Ssl){});
    // if(!Ssl_connect(sslClient, tcpClient)) {
    //     perror("sslClient connect");
    //     return 1;
    // }

    //
    // setup message object
    const char * path = "/records.json";
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

    if(!TcpClient_send(tcpClient, message)) {
        perror("send");
		return 1;
    }
    //
    // receive response from server
    // use loop to receive big data buffers
    // the end of message if determined by 0 data length
    while (1) {
        if(!TcpClient_receive(tcpClient, message)) {
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
    // close connection
    TcpClient_close(tcpClient);
    //
    // cleanup SSL
    Ssl_cleanup(ssl);
	return 0;
}
