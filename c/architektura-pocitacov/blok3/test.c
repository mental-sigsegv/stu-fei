#include<stdio.h>
#include<sys/socket.h> 

const char* SERVER_ADRESS = "147.175.115.34";
const char* SERVER_PORT = "777";
struct sockaddr_in server;

int main(int argc , char *argv[]) {
	int socket_desc;
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	
	if (socket_desc == -1){
		printf("Could not create socket");
	}
	
    // IPv4 AF_INET sockets:
    struct sockaddr_in {
        short            sin_family;   // e.g. AF_INET, AF_INET6
        unsigned short   sin_port;     // e.g. htons(3490)
        struct in_addr   sin_addr;     // see struct in_addr, below
        char             sin_zero[8];  // zero this if you want to
    };

    struct in_addr {
        unsigned long s_addr;          // load with inet_pton()
    };

    struct sockaddr {
        unsigned short    sa_family;    // address family, AF_xxx
        char              sa_data[14];  // 14 bytes of protocol address
    };

    server.sin_addr.s_addr = inet_addr(SERVER_ADRESS);

	return 0;
}