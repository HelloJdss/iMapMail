#ifndef __SOCK_H__
#define __SOCK_H__

#include "stdafx.h"
#define bufsize 255

class Sock
{
public:
	Sock();//creat a new socket
	bool isValid();//whether the Socket initialized successful.
	bool ConnectC_S(const std::string ServerHostId, const unsigned short port);//Server host id and port
	bool sendbuf(const std::string buf);
	void setUserName(const std::string name);
	void setPassword(const std::string password);
	bool login();
	bool list();
	int recvbuf();
	const std::string getRecv();
	~Sock();

private:
	SOCKET sock;
	bool valid;
	sockaddr_in sAddr, cAddr;
	char rbuf[bufsize+1];
	struct hostent *hp;
	FD_SET rfds, wfds;
	std::string USERNAME;
	std::string PASSWORD;
	std::string RECVBUF;
};

#endif // !__SOCK_H__
