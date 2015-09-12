#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define MAX_ERROR_MSG 200
#define MAX_MSG_SIZE 200

#include <iostream>
#include <WinSock2.h>

int main() {
	WSAData wsaData;
	WSAStartup(MAKEWORD(2, 2), &wsaData);

	SOCKET principalSocket;
	principalSocket = socket(AF_INET,
							 SOCK_STREAM,
							 IPPROTO_TCP);

	sockaddr_in enderecoServidor;
	enderecoServidor.sin_addr.s_addr = inet_addr("0.0.0.0");
	enderecoServidor.sin_family = AF_INET;
	enderecoServidor.sin_port = htons(9999);

	bind(principalSocket, (SOCKADDR*)&enderecoServidor, sizeof(enderecoServidor));

	listen(principalSocket, SOMAXCONN);

	sockaddr_in enderecoCliente;
	int enderecoClienteTam = sizeof(enderecoCliente);

	int r = 0;
	char buffer[MAX_MSG_SIZE];
	do {
		SOCKET clienteSocket = accept(principalSocket, (SOCKADDR*)&enderecoCliente, &enderecoClienteTam);
		std::cout << "-------------------------------------------" << std::endl << "Clente: "
			<< inet_ntoa(enderecoCliente.sin_addr)
			<< ":" << htons(enderecoCliente.sin_port)
			<< std::endl;
		std::cout << "Mensagem: ";

		do {
			r = recv(clienteSocket, buffer, 1, NULL);
			buffer[1] = '\0';

			std::cout << buffer;

			if (buffer[0] == 13)
				break;
		} while (r != SOCKET_ERROR || r == 0);

		std::cout << std::endl << "Conexao finalizada" << std::endl;

	} while (true);

	WSACleanup();

	return 0;
}