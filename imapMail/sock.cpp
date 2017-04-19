#include "stdafx.h"
#include "sock.h"
using std::cerr;
using std::cin;
using std::cout;
using std::string;

Sock::Sock() {
  sock = socket(AF_INET, SOCK_STREAM, 0); //采用流方式
  if (sock == INVALID_SOCKET) {
    cerr << "Create socket failed...!\n";
    valid = FALSE;
  }
}

bool Sock::isValid() { return valid; }

bool Sock::ConnectC_S(const string ServerHostId, const unsigned short port) {
  sAddr.sin_family = AF_INET;
  sAddr.sin_port = htons(port);
  hp = gethostbyname(ServerHostId.c_str());
  if (hp == (struct hostent *)0) {
    cerr << "Get Server IP failed...!\n";
    return FALSE;
  }
  struct in_addr s_inaddr;
  memmove(&s_inaddr, (char *)hp->h_addr_list[0], hp->h_length);
  sAddr.sin_addr.S_un.S_addr = inet_addr(inet_ntoa(s_inaddr));
  if (SOCKET_ERROR == connect(sock, (LPSOCKADDR)&sAddr, sizeof(sAddr))) {
    cerr << "Connect Server failed...!\n";
    return FALSE;
  }
  return TRUE;
}

bool Sock::sendbuf(const string buf) {
  string sbuf = buf + "\r\n";
  int len = send(sock, sbuf.c_str(), sbuf.size(), 0);
  cout << "Sent " << len << "bytes\n";
  if (len != SOCKET_ERROR)
    return TRUE;
  else
    return FALSE;
}

void Sock::setUserName(const std::string name) { USERNAME = name; }

void Sock::setPassword(const std::string password) { PASSWORD = password; }

bool Sock::login() {
  std::string s1 =
      "A001 LOGIN " + USERNAME + " " + PASSWORD + "\r\n"; //末尾已自动补\0
  int len = send(sock, s1.c_str(), s1.size(), 0);
  cout << "Sent " << len << "bytes\n";
  if (len != SOCKET_ERROR)
    return TRUE;
  else
    return FALSE;
}

bool Sock::list() {
  std::string s1 = "A002 LIST \"\" *\r\n";
  // char *s1 = "A002 list \"\" *\r\n";
  int len = send(sock, s1.c_str(), s1.size(), 0);
  cout << "Sent " << len << "bytes\n";
  if (len != SOCKET_ERROR)
    return TRUE;
  else
    return FALSE;
  return false;
}

int Sock::recvbuf() {
  int recvTimeout = 100000; // 10s
  setsockopt(sock, SOL_SOCKET, SO_RCVTIMEO, (char *)&recvTimeout, sizeof(int));
  int len, sum;
  len = 0;
  sum = 0;
  string str;
  do {
    memset(rbuf, '\0', bufsize);
    if ((len = recv(sock, rbuf, bufsize, 0)) == SOCKET_ERROR) {
      int id = WSAGetLastError();
      switch (id) {
      case WSANOTINITIALISED:
        cout << "not initialized\n";
        break;
      case WSASYSNOTREADY:
        cout << "sub sys not ready\n";
        break;
      case WSAHOST_NOT_FOUND:
        cout << "name server not found\n";
        break;
      case WSATRY_AGAIN:
        cout << "server fail\n";
        break;
      case WSANO_RECOVERY:
        cout << "no recovery\n";
        break;
      case WSAEINPROGRESS:
        cout << "socket blocked by other prog\n";
        break;
      case WSANO_DATA:
        cout << "no data record\n";
        break;
      case WSAEINTR:
        cout << "blocking call canceled\n";
        break;
      case WSAEPROCLIM:
        cout << "limit exceeded\n";
        break;
      case WSAEFAULT:
        cout << "lpWSAData in startup not valid\n";
        break;
      default:
        cout << "unknown error id = " << id << "\n";
        break;
      };
      return SOCKET_ERROR;
    }
    rbuf[len] = '\0';
    str.append(rbuf);
    sum += len;
  } while (len == bufsize);
  RECVBUF = str;
  return sum;
}

const std::string Sock::getRecv() { return RECVBUF; }

Sock::~Sock() {
  if (valid)
    closesocket(sock); // Only close when socket has been constructed;
}
