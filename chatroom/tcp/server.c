#include <stdio.h>
#include <stdlib.h>
#include <string.h>
#include <unistd.h>
#include <sys/types.h>
#include <sys/socket.h>
#include <netinet/in.h>
#include <arpa/inet.h>

#define MAX_SIZE 2048
#define MY_ERROR(s) printf(s); system("PAUSE"); exit(1);
#define PRINT_READ_SUC printf("All messages sent.\n");
#define PRINT_UPDATE_SUC printf("A new message updated.\n");
#define PRINT_CLEAR_ALL_SUC printf("All messages cleared.\n");

int main(int argc , char *argv[]) {
	int serverSocket = 0, clientSocket = 0;
	struct sockaddr_in serverAddress, clientAddress;
	int bytesRead;
	char buf[MAX_SIZE];
	unsigned clientAddressLen;
	int serverPort;
	if (argc == 2) {
		serverPort = atoi(argv[1]);
	}

	char specialMsg[] = "X\0";

	char existedMsgs[100][MAX_SIZE];
	char tmp[] = "This is message X";
	int numberOfExistedMsgs = 5;
	for (int i = 0; i < numberOfExistedMsgs; i++) {
		tmp[16] = i + 1 + '0';
		tmp[17] = '\0';
		strcpy(existedMsgs[i], tmp);
	}

	serverSocket = socket(PF_INET , SOCK_STREAM , 0);
	serverAddress.sin_family = AF_INET;
	serverAddress.sin_addr.s_addr = INADDR_ANY;
	serverAddress.sin_port = htons(serverPort);
	if (bind(serverSocket, (struct sockaddr*)&serverAddress, sizeof(serverAddress)) < 0) {
		MY_ERROR("Bind Error\n");
	}

	if (listen(serverSocket, 3) < 0) {
		MY_ERROR("Listen Error\n");
	}
	
	printf("Waiting for connection...\n");
	clientAddressLen = sizeof(clientAddress);
	clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddressLen);
	
	printf("Successfully connected, client IP is: %s\n", inet_ntoa(clientAddress.sin_addr));

	while (1) {
		
		usleep(500);
		send(clientSocket, specialMsg, sizeof(specialMsg), 0);
		bytesRead = recv(clientSocket, buf, sizeof(buf), 0);		
		if (buf[0] == 'r') {
			buf[0] = '\0';
			while (buf[0] != 'X') recv(clientSocket, buf, sizeof(buf), 0);
			
			for (int i = 0; i < numberOfExistedMsgs; i++) {
				send(clientSocket, existedMsgs[i], sizeof(existedMsgs[i]), 0);
			}
			PRINT_READ_SUC;

			usleep(500);
			send(clientSocket, specialMsg, sizeof(specialMsg), 0);
		}
		else if (buf[0] == 'w') {
			usleep(500);
			send(clientSocket, specialMsg, sizeof(specialMsg), 0);

			bytesRead = recv(clientSocket, buf, sizeof(buf), 0);
			strcpy(existedMsgs[numberOfExistedMsgs], buf);
			numberOfExistedMsgs += 1;
			PRINT_UPDATE_SUC;

			usleep(500);
			send(clientSocket, specialMsg, sizeof(specialMsg), 0);
		}
		else if (buf[0] == 'c') {
			numberOfExistedMsgs = 0;
			PRINT_CLEAR_ALL_SUC;

			usleep(500);
			send(clientSocket, specialMsg, sizeof(specialMsg), 0);
		}
	}
	close(clientSocket);
  	return 0;
}
