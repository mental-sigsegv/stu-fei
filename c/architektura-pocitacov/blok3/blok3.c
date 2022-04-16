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
#define RED "\e[0;31m"
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
	printf(RED "-> Message was send...\n" COLOR_RESET);
}

void format_print(char* message) {
    int sizeOfTerminal = w.ws_col;

    int letter=0;
    int lastLetter=-1;
    int spaceIndex=0;
    while (letter <= (int)strlen(message)) {
        for (int i=sizeOfTerminal/2 + letter; i >= letter; i--) {
            if ((message[i] == ' ') || (message[i] == '\n')) {
                spaceIndex = i;
                break;
            }
        }
        printf("%*.*s\n", sizeOfTerminal, spaceIndex-letter, message+letter);
        if (lastLetter == letter) {
            break;
        }
        lastLetter = letter;
		letter = spaceIndex;
    }
}

void recieveMessage() {
	// Receive a reply from the server
    char server_reply[BUFF_SIZE];
	if(recv(socket_desc, server_reply, BUFF_SIZE, 0) < 0) {
		printf("-> recv failed\n");
		return;
	}
	printf(GRN "%*s\n", w.ws_col+4, "-> Reply received:" COLOR_RESET);
	format_print(server_reply);
	// printf("%*s\n", w.ws_col, server_reply);
	
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

void decipher() {
	char server_reply[BUFF_SIZE];
	if(recv(socket_desc, server_reply, BUFF_SIZE, 0) < 0) {
		printf("-> recv failed\n");
		return;
	}
	for (int i=0; i<132; i++) {
		server_reply[i] = server_reply[i] ^ 55;
	}
	server_reply[132]='\n';
	server_reply[133]='\0';
	printf(GRN "%*s\n", w.ws_col+4, "-> Reply received:" COLOR_RESET);
	format_print(server_reply);
	// printf("%s\n", server_reply);
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
	sendMessage("753421");
	recieveMessage();

	// Compute code
	int code = compute_code(ID);
	sendMessage(itoa(code, 10));
	recieveMessage();

	sendMessage("333222111");
	recieveMessage();

	sendMessage("123");
	decipher();

	sendMessage("?");
	recieveMessage();

	sendMessage("48");
	recieveMessage();

	sendMessage("2");
	recieveMessage();

	sendMessage("E.T.");
	recieveMessage();

	sendMessage("PRIMENUMBER");
	recieveMessage();

	close(socket_desc);
	return 0;
}