#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/ioctl.h>  // For terminal
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>


const char* SERVER_ADRESS = "147.175.115.34";
const short unsigned int SERVER_PORT = 777;

#define BUFF_SIZE 4096
#define GRN "\e[0;32m"
#define COLOR_RESET "\e[0m"

// const char* SERVER_ADRESS = "142.251.36.68";
// const short unsigned int SERVER_PORT = 80;

static int socket_desc;

struct winsize w;

void connectToServer(struct sockaddr_in server) {
	//Connect to remote server
	if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0)	{
		printf("-> Connect error...\n");
		return;
	}
	printf("-> Connected...\n");
}

void sendMessage(char *message) {
	//Send some data
	if(send(socket_desc , message, strlen(message), 0) < 0) {
		printf("-> Send failed\n");
		return;
	}
	printf("-> Message was send...\n");
}

void recieveMessage() {
	// Receive a reply from the server
    char server_reply[BUFF_SIZE];
	if(recv(socket_desc, server_reply, BUFF_SIZE, 0) < 0) {
		printf("-> recv failed\n");
		return;
	}
	printf(GRN "%*s\n", w.ws_col, "-> Reply received:" COLOR_RESET);
	printf("%*s\n", w.ws_col, server_reply);
	
}

int compute_code(char* num) {
	int sum=0, j=10000, n;
	for (int i=0; i < 5; i++, j=j/10) {
        n = (num[i]-48)*j;
		sum += n;
	}
	return (num[4] == '0') ? sum%9 : sum%(num[4]-48);
}

char* itoa(int val, int base) {
	static char buf[32] = {0};
	int i = 30;
	for(; val && i ; --i, val /= base)
		buf[i] = "0123456789abcdef"[val % base];
	return &buf[i+1];
}

int main() {
	// For terminal
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

	// Create socket
	struct sockaddr_in server;
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if (socket_desc == -1) {
		printf("-> Could not create socket\n");
		return 1;
	}
		
	server.sin_addr.s_addr = inet_addr(SERVER_ADRESS);
	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);

	// Connect to remote server
	if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0)	{
		printf("-> Connect error!\n");
		return 1;
	}
	printf("-> Connected!\n");

	// Recieve Morfeus msg
	sendMessage("NONE");
    recieveMessage();

	// Recieve my name
	char* ID = "115330";
	sendMessage(ID);
	recieveMessage();

	// Set UTF-8
	sendMessage("7545477");
	recieveMessage();

	sendMessage("7545477");
	recieveMessage();

	// Send code, recieve, write in green
	printf(GRN);
	sendMessage("753421");
	recieveMessage();
	printf(COLOR_RESET);

	// Compute code
	int code = compute_code(ID);
	// printf("%s", itoa(code, 10));
	sendMessage(itoa(code, 10));
	recieveMessage();

	close(socket_desc);
	return 0;
}