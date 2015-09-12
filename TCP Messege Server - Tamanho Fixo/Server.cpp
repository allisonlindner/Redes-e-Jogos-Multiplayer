#define _WINSOCK_DEPRECATED_NO_WARNINGS
#define MAX_ERROR_MSG 200
#define MAX_MSG_SIZE 512

#include <WinSock2.h>
#include <iostream>

void show_error(char* message) {
	std::cout << message << std::endl;
	system("pause");
}

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
	int tamanho;

	do {
		SOCKET clienteSocket = accept(principalSocket, (SOCKADDR *)&enderecoCliente, &enderecoClienteTam);

		std::cout << "-------------------------------------------" << std::endl << "Clente: "
			<< inet_ntoa(enderecoCliente.sin_addr)
			<< ":" << htons(enderecoCliente.sin_port)
			<< std::endl;
		
		do {
			r = recv(clienteSocket, (char*)&tamanho, sizeof(int), NULL);

			if (tamanho == 0)
				break;

			int totalRecebido = 0;

			do {

				r = recv(clienteSocket, buffer + totalRecebido, MAX_MSG_SIZE, NULL);
				totalRecebido += r;

			} while (totalRecebido < tamanho);

			buffer[totalRecebido] = '\0';
			std::cout << "Mensagem: " << buffer << std::endl;
			totalRecebido = 0;
			tamanho = 0;
		} while (true);

		std::cout << std::endl << "Conexao finalizada" << std::endl;
	} while (true);

	WSACleanup();

	return 0;
}