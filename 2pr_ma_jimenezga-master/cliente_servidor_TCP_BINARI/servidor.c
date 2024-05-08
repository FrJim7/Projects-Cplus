#include "stdio.h"
#include "stdlib.h"
#include "string.h"
#include "winsock2.h"

int main(){
  WSADATA wsa;
  SOCKET sock, sock_c;
  FILE *f1;
  struct sockaddr_in ip, ipc;
  
  char buffer[1024];
  int file_size;

  memset(buffer, '\0', sizeof(buffer));
  WSAStartup(MAKEWORD(2, 0), &wsa);
  sock = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);
  ip.sin_family = AF_INET;
  ip.sin_addr.s_addr = inet_addr("0.0.0.0");
  ip.sin_port = htons(9999);

  bind(sock, (SOCKADDR*)&ip, sizeof(ip));
  listen(sock, 1);
  sock_c = accept(sock, NULL, NULL);
  f1 = fopen("C:\\Development\\2pr_ma_jimenezga\\cliente_servidor_TCP_BINARI\\data\\imagen.jpg", "rb");
  if(1){
    fseek(f1, 0, SEEK_END);
    rewind(f1);
    file_size = ftell(f1);
    itoa(file_size, buffer, 10);
    send(sock, buffer, strlen(buffer), 0);
    recv(sock, buffer, sizeof(buffer), 0);
    while(feof(f1)) {
      memset(buffer, '\0', sizeof(buffer));
      fread(buffer, 1, sizeof(buffer), f1);
      send(sock, buffer, strlen(buffer), 0);
    }
    fclose(f1);
  }
}