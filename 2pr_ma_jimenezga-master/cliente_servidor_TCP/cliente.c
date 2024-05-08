#include "stdio.h"
#include "string.h"
#include "winsock2.h"

int main() {
	WSADATA wsa;
	SOCKET sock;
	struct sockaddr_in ip;
	char buffer[1024];
	int ip_size = sizeof(ip);

	memset(buffer, '\0' , sizeof(buffer));
	WSAStartup(MAKEWORD (2,0),&wsa);
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	ip.sin_family = AF_INET;
	ip.sin_addr.s_addr = inet_addr("127.0.0.1");
	ip.sin_port = htons(9999);

	connect(sock, (SOCKADDR*)&ip, sizeof(ip));

	while(strcmp(buffer, "exit") != 0) {
		recv(sock, buffer, sizeof(buffer), 0);
		printf("%s\n", buffer);
		memset(buffer, '\0', sizeof(buffer));
	};

	WSACleanup();
	return 0;
}