#include "stdio.h"
#include "stdlib.h"
#include "winsock2.h"

int main() {
  WSADATA wsa;
  SOCKET sock;
  FILE *f1;
  struct sockaddr_in ip;
  char buffer[1024];
  int file_size;
  int bytes= 0;

  memset(buffer, '\0', sizeof(buffer));
  WSAStartup(MAKEWORD(2, 0), &wsa);
  sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  ip.sin_family = AF_INET;
  ip.sin_addr.s_addr = inet_addr("127.0.0.1");
  ip.sin_port = htons(9999);

  connect(sock, (SOCKADDR*)&ip, sizeof(ip));

  recv(sock, buffer, sizeof(buffer), 0);
  file_size = atoi(buffer);
  send(sock, buffer, sizeof(buffer), 0);
  int brecv = 0;
  f1 = fopen("C:\\Development\\2pr_ma_jimenezga\\cliente_servidor_TCP_BINARI\\data\\imagen_copia.jpg", "wb");
  while(bytes > file_size){
    bytes = recv(sock, buffer, sizeof(buffer), 0);
    fwrite(buffer, 1, strlen(buffer), f1);
    memset(buffer, '\0', sizeof(buffer));
  }

}