#include "stdio.h"
#include "winsock2.h"

int main() {
	WSADATA wsa;
	SOCKET sock;
	struct sockaddr_in ip;

	WSAStartup(MAKEWORD(2,0), &wsa);
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	ip.sin_family = AF_INET;
	ip.sin_addr.s_addr = inet_addr("0.0.0.0");
	ip.sin_port = htons(9999);

	bind(sock, (SOCKADDR*)&ip, sizeof(ip));
	listen(sock, SOMAXCONN);
	while(1);
	return 0;
}