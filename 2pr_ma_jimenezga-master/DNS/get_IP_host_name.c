#include "stdio.h"
#include "winsock2.h"
#include "ws2tcpip.h"

int main() {
	WSADATA wsa;
	char nombre[1024];
	WSAStartup(MAKEWORD(2, 0), &wsa);
	struct addrinfo *addr, *ptr;
	struct sockaddr_in *ip;
	memset(nombre, 0, sizeof(nombre));
	printf("Introduce dominio: ");
	gets(nombre);
	if(!getaddrinfo(nombre, NULL, NULL, &addr)) {
		for(ptr = addr; ptr != NULL; ptr = ptr->ai_next) {
			ip = (struct sockaddr_in*)ptr->ai_addr;
			printf("IP de %s: %s\n", nombre, inet_ntoa(ip->sin_addr));
		}
	} else {
		printf("El dominio %s no existe\n", nombre);
	}
	freeaddrinfo(addr);
	return 0;
}