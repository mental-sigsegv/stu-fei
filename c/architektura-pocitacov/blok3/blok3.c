#include<stdio.h>
#include<string.h>	//strlen
#include<sys/socket.h>
#include<arpa/inet.h>	//inet_addr

const char* SERVER_ADRESS = "147.175.115.34";
const short unsigned int SERVER_PORT = 777;

int main()
{
	int socket_desc;
	struct sockaddr_in server;
	
	//Create socket
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if (socket_desc == -1)
	{
		printf("-> Could not create socket");
	}
		
	server.sin_addr.s_addr = inet_addr(SERVER_ADRESS);
	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);

	//Connect to remote server
	if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0)
	{
		puts("-> Connect error...");
		return 1;
	}
	
	puts("-> Connected...\n");


    // Receive a reply from the server
    char server_reply[4096];
	if( recv(socket_desc, server_reply , 4096 , 0) < 0)
	{
		puts("-> recv failed");
	}
	puts("-> Reply received:");
	puts(server_reply);

	//Send some data
    char *message;
	message = "115330\r\n\r\n\0";
	if( send(socket_desc , message , strlen(message) , 0) < 0)
	{
		puts("Send failed");
		return 1;
	}
	puts("Data was send...\n");

	// Receive a reply from the server
	char server_reply2[4096];
	if( recv(socket_desc, server_reply2 , 4096 , 0) < 0)
	{
		puts("-> recv failed");
	}
	puts("-> Reply received:");
	puts(server_reply2);
	return 0;
}