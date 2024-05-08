#include "stdio.h"
#include "winsock2.h"

int main() {
	WSADATA wsa;
	char nombre[100];

	WSAStartup(MAKEWORD(2,0), &wsa);
	gethostname(nombre, sizeof(nombre));
	printf("Nombre: %s\n", nombre);
	while(1);	
	return 0;
}