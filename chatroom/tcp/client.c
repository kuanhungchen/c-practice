#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX_SIZE 2048
#define ADDRESS_SIZE 20
#define MY_ERROR(s) printf(s); system("PAUSE"); exit(1);
#define DISCONNECT(p) printf(" Good bye!\n"); close(p); return 0;

int main(int argc , char *argv[]) {
	int serverSocket = 0;
	struct sockaddr_in serverAddress;
	int bytesRead;
	char buf[MAX_SIZE];
	char serverAddressStr[ADDRESS_SIZE];
	int serverPort;
	if (argc == 3) {
		strcpy(serverAddressStr, argv[1]);
		serverPort = atoi(argv[2]);
	}

	char specialMsg[] = "X\0";

	memset(&serverAddress, 0, sizeof(serverAddress));
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = inet_addr(serverAddressStr);
	serverAddress.sin_port = htons(serverPort);
	
	serverSocket = socket(AF_INET, SOCK_STREAM, 0);
	if (connect(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
		MY_ERROR("Connect Error\n");
	}
	printf("Successfully connected, server IP is: %s \n", inet_ntoa(serverAddress.sin_addr));

	while (1) {		
		buf[0] = '\0';
		while (buf[0] != 'X') bytesRead = recv(serverSocket, buf, sizeof(buf), 0);

		// PRINT_MENU;
		scanf("%s", buf);
		while ((buf[0] != 'r' && buf[0] != 'w' && buf[0] != 'c' && buf[0] != 'q') || buf[1] != '\0') {
			// PRINT_INVALID_CHOICE;
			scanf("%s", buf);
		}
		if (buf[0] == 'q') {
			DISCONNECT(serverPort);
		}
		buf[1] = '\0';
		send(serverSocket, buf, sizeof(buf), 0);
		
		if (buf[0] == 'r') {
			usleep(500);
			send(serverSocket, specialMsg, sizeof(specialMsg), 0);
			printf("|-------------------------------------------|\n");
			printf(" All messages:\n");
			
			bytesRead = recv(serverSocket, buf, sizeof(buf), 0);
			int i = 1;
			while (buf[0] != 'X') {
				printf(" %d.%s\n", i, buf);
				bytesRead = recv(serverSocket, buf, sizeof(buf), 0);
				i += 1;
			}
			if (i == 1) printf(" No existing messages.\n");
			printf("\n");
		}
		else if (buf[0] == 'w') {
			buf[0] = '\0';
			while (buf[0] != 'X') recv(serverSocket, buf, sizeof(buf), 0);

			// PRINT_NEW_MSG_HINT;
			scanf("%s", buf);
			send(serverSocket, buf, sizeof(buf), 0);

			buf[0] = '\0';
			while (buf[0] != 'X') recv(serverSocket, buf, sizeof(buf), 0);

			// PRINT_NEW_MSG_SUC;
		}
		else if (buf[0] == 'c') {
			buf[0] = '\0';
			while (buf[0] != 'X') bytesRead = recv(serverSocket, buf, sizeof(buf), 0);
			// PRINT_CLEAR_ALL_SUC;
		}
	}
	DISCONNECT(serverPort);
}
