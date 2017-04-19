#include "stdafx.h"
#include "WSA.h"
using std::cerr;
using std::cin;
using std::cout;

Wsa::Wsa()
{
	nRC = WSAStartup(0x0101, &wsaData);
	if (nRC) {
		cerr << "Initialize winsock error!\n";
		valid = FALSE;
	}
	if (wsaData.wVersion != 0x0101) {
		cerr << "Winsock version error!\n";
		WSACleanup();
		valid = FALSE;
	}
}

bool Wsa::isValid()
{
	return valid;
}

Wsa::~Wsa()
{
	if(valid) WSACleanup();
}
