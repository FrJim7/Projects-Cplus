#include "stdio.h"
#include "string.h"
#include "winsock2.h"

int main() {
	WSADATA wsa;
	SOCKET sock, sock_c[5];
	struct sockaddr_in ip, ipc[5];
	char buffer[1024];
	int i = 0;

	memset(buffer, '\0' , sizeof(buffer));
	WSAStartup(MAKEWORD (2,0),&wsa);
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	ip.sin_family = AF_INET;
	ip.sin_addr.s_addr = inet_addr("0.0.0.0");
	ip.sin_port = htons(9999);

	bind(sock, (SOCKADDR*)&ip, sizeof(ip));
	listen(sock, 5);

	do {
		sock_c[i] = accept(sock, NULL, NULL);
		++i;
	} while(i < 5);

	while(strcmp(buffer, "exit") != 0) {
		printf("Escriba una cadena:\n");
		gets(buffer);
		for (int i = 0; i < 5; ++i)
		{
			send(sock_c[i], buffer, sizeof(buffer), 0);
		}
		memset(buffer, '\0', sizeof(buffer));
	};

	WSACleanup();
	return 0;
}