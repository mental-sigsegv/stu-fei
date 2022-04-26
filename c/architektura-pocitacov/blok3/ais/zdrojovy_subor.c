// Include
#include <stdlib.h>
#include <stdio.h>
#include <string.h>
#include <sys/socket.h>
#include <sys/types.h>
#include <sys/ioctl.h>  // For terminal
#include <netinet/in.h>
#include <arpa/inet.h>
#include <unistd.h>
#include <math.h>
#include <locale.h>
#include "hlavickovy_subor.h"


// Define
#define BUFF_SIZE 4096
#define GRN "\e[0;32m"
#define RED "\e[0;31m"
#define COLOR_RESET "\e[0m"

// Global var
const char* SERVER_ADRESS = "147.175.115.34";
const short unsigned int SERVER_PORT = 777;

static int socket_desc;
struct winsize w;
char server_reply[BUFF_SIZE];
FILE *log_file;

// Link for source
// https://www.binarytides.com/socket-programming-c-linux-tutorial/


void sendMessage(char *message) {
	//Send some data
	if(send(socket_desc , message, strlen(message), 0) < 0) {
		printf("-> Send failed\n");
		exit(1);
	}

	printf(RED "-> \"%s\" was send...", message, COLOR_RESET);
	fprintf(log_file, "USER\n%s\n", message);
}

void format_print(char* message) {
    int sizeOfTerminal = w.ws_col;

    int letter=0;
    int lastLetter=-1;
    int spaceIndex=0;

	printf(GRN "\n%*s\n", w.ws_col+4, "-> Reply received:" COLOR_RESET);

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
	if(recv(socket_desc, server_reply, BUFF_SIZE, 0) < 0) {
		printf("-> recv failed\n");
		exit(1);
	}
	format_print(server_reply);
	fprintf(log_file, "\nSERVER\n%s\n", server_reply);
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

int is_prime(int num) {
    if ((num == 2) || (num == 3)) {
        return 1;
    } else if ((num%2 == 0) || (num == 1)) {
        return 0;
    }
    for (int i = 3; i <= (int)sqrt(num)+1; i=i+2) {
        if (num%i == 0) {
            return 0;
        }
    }
    return 1;
}

void decipher_by_primes() {
	char* text = server_reply;
	int new_index = 0;
    for (int i = 0; i <= (int)strlen(text); i++) {
        if (is_prime(i) == 1) {
            // printf("%c", text[i-1]);
			server_reply[new_index] = text[i-1];
			new_index++;
        }
    }
	server_reply[new_index] = '\0';
}

void decipher() {
	if(recv(socket_desc, server_reply, BUFF_SIZE, 0) < 0) {
		printf("-> recv failed\n");
		exit(1);
	}
	for (int i=0; i<132; i++) {
		server_reply[i] = server_reply[i] ^ 55;
	}
	server_reply[132]='\0';
	
	format_print(server_reply);
	fprintf(log_file, "\nSERVER\n%s\n", server_reply);
}

void decipher_by_caesar(char* cipher, int rotate) {
    char letter;
    for (int l=0; l<(int)strlen(cipher); l++) {
        letter = cipher[l];
        if (('a' <= letter) && (letter <= 'z')) {
            server_reply[l] = ((letter + rotate)%'a')%26+'a';
        } else if (('A' <= letter) && (letter <= 'Z')) {
            server_reply[l] = ((letter + rotate)%'A')%26+'A';
        } else {
            server_reply[l] = cipher[l];
        }
    }
	server_reply[(int)strlen(cipher)] = '\0';
}

int main() {
    system("LANG=C.UTF-8;"); 
    // system("locale");
   	log_file = fopen("./log.txt", "w+");

	// For terminal
    ioctl(STDOUT_FILENO, TIOCGWINSZ, &w);

	// Create socket
	struct sockaddr_in server;
	socket_desc = socket(AF_INET , SOCK_STREAM , 0);
	if (socket_desc == -1) {
		printf("-> Could not create socket\n");
		exit(1);
	}
	
	// Setting up server (ip, port, type of connection)
	server.sin_addr.s_addr = inet_addr(SERVER_ADRESS);
	server.sin_family = AF_INET;
	server.sin_port = htons(SERVER_PORT);

	// Connect to remote server
	if (connect(socket_desc , (struct sockaddr *)&server , sizeof(server)) < 0)	{
		printf("-> Connect error!\n");
		exit(1);
	}

	printf(GRN "-> Connected!\n" COLOR_RESET);
	fprintf(log_file, "STATUS\nconnected\n\n");

	// Recieve Morfeus msg
	sendMessage("?");  // TODO FIX
    recieveMessage();

	// Recieve my name
	char* ID = "115330";
	sendMessage(ID);
	recieveMessage();

	// Set UTF-8
	sendMessage("?");
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

	decipher_by_primes();
	sendMessage(server_reply);
	recieveMessage();

	sendMessage("Trinity");
	recieveMessage();

	sendMessage("polyadicke");
	recieveMessage();

	sendMessage("half-duplex");
	recieveMessage();

	for (int i = 1; i < 26; i++) {
		decipher_by_caesar("OBVMHKR", i);
		sendMessage(server_reply);
		recieveMessage();

		if (strcmp(server_reply, "Incorrect answer, try again...\n") != 0) {
			break;
		}
	}
	

	fprintf(log_file, "STATUS\ndisconnected\n");
	fclose(log_file);
	close(socket_desc);

	return 0;
}