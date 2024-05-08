#include "stdio.h"
#include "winsock2.h"

struct comandos {
	int id;
	char nombre[50];
	char cmd[50];
};

int main() {
	WSADATA wsa;
	SOCKET sock;
	struct sockaddr_in ip;
	char buffer[1024];
	memset(buffer, 0, 1024);

	Comandos com;
	//---//
	WSAStartup(MAKEWORD(2,0),&wsa);
	sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
	ip.sin_family = AF_INET;
	ip.sin_addr.s_addr = inet_addr("127.0.0.1");
	ip.sin_port = htons(7979);
	connect(sock, (SOCKADDR*)&ip, sizeof(ip));
	//---//
	recv(sock, (char*)&com, sizeof(com), 0);
	
	while(1);
	return 0;
}