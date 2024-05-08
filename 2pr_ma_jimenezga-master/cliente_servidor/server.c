#include "stdio.h"
#include "winsock2.h"

struct comandos {
	int id;
	char nombre[50];
	char cmd[50];
};

int main() {
	WSADATA wsa;
	SOCKET sock, sock_c;
	struct sockaddr_in ip, ipc;
	struct comandos cmd;
	char buffer[1024];
	int size_ip = sizeof(ipc);

	WSAStartup(MAKEWORD	(2,0),&wsa);
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	ip.sin_family = AF_INET;
	ip.sin_addr.s_addr = inet_addr("0.0.0.0");
	ip.sin_port = htons(7979);

	bind(sock, (SOCKADDR*)&ip, sizeof(ip));
	listen(sock, SOMAXCONN);

	sock_c = accept(sock, NULL, NULL);

	send(sock_c, (char*)&com, sizeof(com), 0);

	while(1);
}