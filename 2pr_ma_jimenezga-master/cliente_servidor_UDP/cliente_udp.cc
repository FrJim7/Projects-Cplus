#include "stdio.h"
#include "string.h"
#include "winsock2.h"

int main() {
	WSADATA wsa;
	SOCKET sock;
	char buffer[1024];
	struct sockaddr_in ip, ip_s;
	int ip_size = sizeof(ip_s);
	int bytes = 0;

	memset(buffer, '\0', sizeof(buffer));
	WSAStartup(MAKEWORD(2, 0), &wsa);
	sock = socket(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
	ip.sin_family = AF_INET;
	ip.sin_addr.s_addr = inet_addr("127.0.0.1");
	ip.sin_port = htons(9999);

	while (1) {
		memset(buffer, '\0', sizeof(buffer));
		bytes = recvfrom(sock, buffer, sizeof(buffer), 0, (SOCKADDR*)&ip_s, &ip_size);
		printf("Servidor: %s\n", buffer);
		memset(buffer, '\0', sizeof(buffer));
		printf("Cliente:");
		gets(buffer);
		sendto(sock, buffer, strlen(buffer), 0, (SOCKADDR*)&ip, ip_size);
	}
	return 0;
}