#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define MAX_ERROR_MSG 200
#define MAX_MSG_SIZE 512

#include <iostream>
#include <WinSock2.h>
#include <conio.h>
#include <stdio.h>

void show_error(char* message) {
	std::cout << message << std::endl;
	system("pause");
}

int main() {
	int r = 0;
	char* error_message = new char[MAX_ERROR_MSG];

	WSADATA wsaData;

	r = WSAStartup(MAKEWORD(2, 2), &wsaData);

	if (r != 0) {
		sprintf_s(error_message, MAX_ERROR_MSG, "Ocorreu um erro na inicializaÁ„o do WinSock: %d", WSAGetLastError());
		show_error(error_message);
		return 1;
	}

	SOCKET meuSocket = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (meuSocket == INVALID_SOCKET) {
		sprintf_s(error_message, MAX_ERROR_MSG, "Ocorreu um erro ao criar o socket: %d", WSAGetLastError());
		show_error(error_message);
		return 1;
	}

	sockaddr_in enderecoServidor;
	enderecoServidor.sin_addr.s_addr = inet_addr("127.0.0.1");
	enderecoServidor.sin_family = AF_INET;
	enderecoServidor.sin_port = htons(9999);

	r = connect(meuSocket, (SOCKADDR *)&enderecoServidor, sizeof(enderecoServidor));

	char buffer[MAX_MSG_SIZE];
	int tamanho = 0;
	do {
		gets_s(buffer, MAX_MSG_SIZE);
		tamanho = strlen(buffer);

		if (tamanho > 0) {
			send(meuSocket, (char*)&tamanho, sizeof(int), NULL);

			send(meuSocket, buffer, tamanho, NULL);
		}
		else {
			break;
		}

	} while (true);

	closesocket(meuSocket);

	WSACleanup();

	return 0;
}