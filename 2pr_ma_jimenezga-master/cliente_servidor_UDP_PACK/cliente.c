#include "stdio.h"
#include "stdlib.h"
#include "winsock2.h"

struct P_Pack {
  int id_;
  int price_;
  char name_[50];
};

struct C_Pack {
  int id_;
  char name_[50];
};

struct Pack {
  int id_;
  union(P_Pack p_p, C_Pack c_p);
};
  
int main() {
  WSADATA wsa;
  SOCKET sock;
  struct sockaddr_in ip, ipc;

  char buffer[512];
  memset(buffer, '\0', sizeof(buffer));

  WSAStartup(MAKEWORD(2, 0), &wsa);
  ip.sin_family(AF_INET, SOCK_DGRAM, IPPROTO_UDP);
  ip.sin_addr.s_addr = inet_addr("127.0.0.1");
  ip.sin_port = htons(9999);

  while(1) {
    
  }
}