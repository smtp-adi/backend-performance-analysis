#include<stdio.h>
#include<stdlib.h>
#include<string.h>
#include<unistd.h>
#include<sys/socket.h>
#include<netinet/in.h>


//max application buffer, used as input for an array. That determines amount of memory in bytes where we place data we receive from network.
//We will put that data in specific area that we reserve in the memory
//1024 bytes 1KB represents a req size(not prod ready as req size can be more than 1KB)
#define APP_MAX_BUFFER 1024

#define PORT 8080

int main() {
    //define the server and client file descriptors
    int server_fd, client_fd;

    //define the socket address
    struct sockaddr_in address;
    int address_len =sizeof(address);

    //define the application buffer where we receive requests
    //data will be moved from received buffer to here.
    //We copy data here frpm OS receive kernel that is per connection. For every single connection we get from client
    //When we call read on that connection( which is the client file descriptor). We will be copying data received from client whatever be the size it is, we want to only copy max buffer worth of size down to my buffer
    //We move data from receive buffer to buffer ie our application defined below.
    char buffer[APP_MAX_BUFFER]={0};


    //Create socket
    if((server_fd = socket(AF_INET /**IPV4 and AF_INET6 for IPV6*/, SOCK_STREAM /**Streaming protocol or UDP message based protocol not exactly asks for TCP*/, 0/**kerenel selects TCP as streaming protocol*/)) == 0) {
        perror("Socket creation failed");
        //Socket creation can fail due to memory issues or  may be there is no network.
        exit(EXIT_FAILURE);
    }

    //lets start binding

    //Bind the socket
    address.sin_family = AF_INET; //IPV4
    address.sin_addr.s_addr = INADDR_ANY; //listen 0.0.0.0, listens on all interfaces(Wifi,ethernet,5G). Not recommended. Exposing an application to an interface which is not needed. Done coz dont want to create an actual IP.
    address.sin_port = htons(PORT); // PORT is int.  Byte order of int is host specific. Anything on internet has the bits in network order. Therefore we do htons

    if(bind(server_fd, (struct sockaddr *)&address, sizeof(address)) <0) {
        perror("Bind failed");// port already listening, can be overridden by a flag by allowing multiple processes to listen from same port ie SO_REUSEPORT
        exit(EXIT_FAILURE);
    }

    //This still wont listen. The kernel did not create the necessary data structure to start accepting all stuff.
    //As of now only a record is created that says this server_fd pointing to this socket(addr)
    //It has not started listenign or accepting or actually responding to send requests from TCP connections

    //Create queue

    return 0;
}
