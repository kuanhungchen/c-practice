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

	int clients[3];
	int numOfClients = 0;
	
	for (int i=0; i<2; i++) {
		clientAddressLen = sizeof(clientAddress);
		clientSocket = accept(serverSocket, (struct sockaddr*)&clientAddress, &clientAddressLen);
		clients[i] = clientSocket;
		numOfClients += 1;
		printf("The %d client is conencted, from IP: %s\n", i, inet_ntoa(clientAddress.sin_addr));
	}
	

	while (1) {
		
		usleep(500);
		
		// receive from client
		int i=0;
		while (i<numOfClients) {
			bytesRead = recv(clients[i], buf, sizeof(buf), 0);
			printf("Received from client %d: %s", i, buf);
			usleep(500);
		}
		
		// send back to client
		send(clientSocket, buf, sizeof(buf), 0);
		printf("Sent to client: %s", buf);

		// if (buf[0] == 'r') {
		// 	buf[0] = '\0';
		// 	while (buf[0] != 'X') recv(clientSocket, buf, sizeof(buf), 0);
			
		// 	for (int i = 0; i < numberOfExistedMsgs; i++) {
		// 		send(clientSocket, existedMsgs[i], sizeof(existedMsgs[i]), 0);
		// 	}
		// 	// PRINT_READ_SUC;

		// 	usleep(500);
		// 	send(clientSocket, specialMsg, sizeof(specialMsg), 0);
		// }
		// else if (buf[0] == 'w') {
		// 	usleep(500);
		// 	send(clientSocket, specialMsg, sizeof(specialMsg), 0);

		// 	bytesRead = recv(clientSocket, buf, sizeof(buf), 0);
		// 	strcpy(existedMsgs[numberOfExistedMsgs], buf);
		// 	numberOfExistedMsgs += 1;
		// 	// PRINT_UPDATE_SUC;

		// 	usleep(500);
		// 	send(clientSocket, specialMsg, sizeof(specialMsg), 0);
		// }
		// else if (buf[0] == 'c') {
		// 	numberOfExistedMsgs = 0;
		// 	// PRINT_CLEAR_ALL_SUC;

		// 	usleep(500);
		// 	send(clientSocket, specialMsg, sizeof(specialMsg), 0);
		// }
	}
	close(clientSocket);
  	return 0;
}
