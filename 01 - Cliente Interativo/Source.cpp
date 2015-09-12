#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define MAX_ERROR_MSG 200
#define MAX_MSG_SIZE 2

#include <WinSock2.h>
#include <iostream>

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
		sprintf_s(error_message, MAX_ERROR_MSG, "Ocorreu um erro na inicialização do WinSock: %d", WSAGetLastError());
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

	r = connect(meuSocket, (SOCKADDR *) &enderecoServidor, sizeof(enderecoServidor));

	char buffer[] = { 'a', '\0' };

	send(meuSocket, buffer, MAX_MSG_SIZE, NULL);

	closesocket(meuSocket);

	WSACleanup();

	return 0;
}