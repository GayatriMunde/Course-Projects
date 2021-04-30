// ChatRoom.h : Include file for standard system include files,
// or project specific include files.

#define WIN32_LEAN_AND_MEAN
#include <windows.h>
#include <winsock2.h>
#include <ws2tcpip.h>
#include <stdlib.h>
#include <stdio.h>
#include <iostream>
#include <string>

// Need to link with Ws2_32.lib
#pragma comment (lib, "Ws2_32.lib")

using namespace std;
#define DEFAULT_PORT 4000
#define DEFAULT_BUFLEN 512
#define MAX_CLIENTS 2
#define DEFAULT_PORT_C "4000"


char recvbuf[DEFAULT_BUFLEN] = "";
int len, receiveres, clients_connected = 0;
bool active = TRUE;

SOCKET server_socket = INVALID_SOCKET;
SOCKET client_fd;
sockaddr_in server;

struct _clients_b {
	bool connected;
	SOCKET ss;
};
_clients_b clients[MAX_CLIENTS];


void start_server();

void ChatServer() {
	cout << "Server starting..." << endl;
	start_server();

	printf("Accepting Clients.....\n");

	while (active) {
		len = sizeof(server);
		client_fd = accept(server_socket, (struct sockaddr*)&server, &len);

		if (client_fd != INVALID_SOCKET) {


			clients[clients_connected].ss = client_fd;
			clients[clients_connected].connected = TRUE;

			clients_connected++;
			cout << "New client: " << client_fd << endl;
		}
		
		Sleep(1);
		if (clients_connected > 0)
		{

			for (int cc = 0; cc < clients_connected; cc++) 
			{
				memset(&recvbuf, 0, sizeof(recvbuf));
				if (clients[cc].connected) {
					receiveres = recv(clients[cc].ss, recvbuf,DEFAULT_BUFLEN, 0);
					if (receiveres > 0){
						Sleep(10);
						cout << "Msg from Client["<<cc<<"] : "<<recvbuf<<endl;
						for (int i = 0; i < clients_connected; i++)
						{
							if (i != cc)
								send(clients[i].ss, recvbuf, strlen(recvbuf),0);
						} 
					}
					else if (receiveres == 0 || strcmp(recvbuf,"disconnect") == 0) {
						cout << "Client ["<<cc<<"disconnected." << endl;
						clients[cc].connected = FALSE;
						clients_connected--;
					}
				}
			}
		}
	}

	closesocket(server_socket);
	WSACleanup();
}

void start_server() {
	int wsaresult, i = 1;
	WSADATA wsaData;

	server.sin_family = AF_INET;
	server.sin_addr.s_addr = INADDR_ANY;
	server.sin_port = htons(DEFAULT_PORT);

	wsaresult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	
	if (wsaresult != 0) {
		printf("WSAStartup failed with error: %d\n", wsaresult);
	}
	printf("\nVersion:%d\nDescription:%s\nStatus:%s\n",wsaData.wVersion,wsaData.szDescription,wsaData.szSystemStatus);

	server_socket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	if (server_socket == INVALID_SOCKET) {
		printf("socket failed with error: %ld\n", WSAGetLastError());
		WSACleanup();
	}
	printf("Socket creation done Sucessfuly\n");

	wsaresult = bind(server_socket, (sockaddr*)&server, sizeof(server));
	if (wsaresult == SOCKET_ERROR) {
		printf("bind failed with error: %d\n", WSAGetLastError());
		closesocket(server_socket);
		WSACleanup();
	}
	printf("Binding Sucessful!!\n");
	
	wsaresult = listen(server_socket, MAX_CLIENTS);
	unsigned long b = 1;
	
	ioctlsocket(server_socket, FIONBIO, &b);

	if (wsaresult == SOCKET_ERROR) {
		printf("listen failed with error: %d\n", WSAGetLastError());
		closesocket(server_socket);
		WSACleanup();
	}
}

void ChatClient(){
	WSADATA wsaData;
	SOCKET ConnectSocket = INVALID_SOCKET;
	struct addrinfo* result = NULL,
		* ptr = NULL,
		hints;
	char sendbuf[DEFAULT_BUFLEN] = "";
	string sendbuf2;
	char recvbuf[DEFAULT_BUFLEN] = "";
	int iResult;
	int recvbuflen = DEFAULT_BUFLEN;

	iResult = WSAStartup(MAKEWORD(2, 2), &wsaData);
	if (iResult != 0) {
		printf("WSAStartup failed with error: %d\n", iResult);
	}
	printf("\nVersion:%d\nDescription:%s\nStatus:%s\n", wsaData.wVersion, wsaData.szDescription, wsaData.szSystemStatus);
	ZeroMemory(&hints, sizeof(hints));
	hints.ai_family = AF_UNSPEC;
	hints.ai_socktype = SOCK_STREAM;
	hints.ai_protocol = IPPROTO_TCP;

	iResult = getaddrinfo("localhost", DEFAULT_PORT_C, &hints, &result);
	if (iResult != 0) {
		printf("getaddrinfo failed with error: %d\n", iResult);
		WSACleanup();
	}

	for (ptr = result; ptr != NULL; ptr = ptr->ai_next){
		ConnectSocket = socket(ptr->ai_family, ptr->ai_socktype, ptr->ai_protocol);
		if (ConnectSocket == INVALID_SOCKET)
		{
			printf("socket failed with error: %ld\n", WSAGetLastError());
			WSACleanup();
		}

		iResult = connect(ConnectSocket, ptr->ai_addr, (int)ptr->ai_addrlen);
		if (iResult == SOCKET_ERROR)
		{
			closesocket(ConnectSocket);
			ConnectSocket = INVALID_SOCKET;

			continue;
		}
		break;
	}
	freeaddrinfo(result);
	if (ConnectSocket == INVALID_SOCKET)
	{
		printf("Unable to connect to server!\n");
		closesocket(ConnectSocket);
		WSACleanup();
	}
	else
	{
		printf("\nSuccessfully Connected to the server!\n");

		int loopthis = 1;
		while (loopthis == 1) {

			cout << "\nType to say: ";
			cin.ignore();
			getline(cin, sendbuf2);

			iResult = send(ConnectSocket, sendbuf2.c_str(), (int)strlen(sendbuf2.c_str()), 0);
			if (iResult == SOCKET_ERROR) {
				printf("send failed with error: %d\n", WSAGetLastError());
				closesocket(ConnectSocket);
				WSACleanup();
			}
			printf("Bytes Sent: %ld\n", iResult);
			if (strcmp(sendbuf2.c_str(), "exit") == 0) {
				cout << "exiting...\n";
				loopthis = 0;
				break;
			}
			memset(&recvbuf, 0, sizeof(recvbuf));

			iResult = recv(ConnectSocket, recvbuf, recvbuflen, 0);
			if (iResult > 0)
			{
				printf("\nMsg Received :%s\n", recvbuf);
			}
			else if (iResult == 0)
				printf("Connection closed\n");
			else
				printf("recv failed with error: %d\n", WSAGetLastError());
		}

		iResult = shutdown(ConnectSocket, SD_SEND);
		if (iResult == SOCKET_ERROR) {
			printf("shutdown failed with error: %d\n", WSAGetLastError());
			closesocket(ConnectSocket);
			WSACleanup();
		}

		closesocket(ConnectSocket);
		WSACleanup();
	}
	int ok;
	cin >> ok;
}
