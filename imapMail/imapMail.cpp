// imapMail.cpp : 定义控制台应用程序的入口点。
//

#include "stdafx.h"
#include "WSA.h"
#include "sock.h"


using std::cout;
using std::cin;
using std::string;

int main()
{
	Wsa wsa;
	if (wsa.isValid() == FALSE) {
		return -1;
	}
	Sock sock;
	if (sock.isValid() == FALSE) {
		return -2;
	}
	string host_id("imap.qq.com");
	if (sock.ConnectC_S(host_id, 143) == FALSE) {
		return -3;
	}
	//do {
	//	string sdbuf;
	//	cout<<"Recv "<<sock.recvbuf()<<"Bytes\n";
	//	cout << sock.getBuf();
	//	getline(cin,sdbuf);
	//	//if(sdbuf=="LOGOUT"||sdbuf=="logout") break;
	//	sock.sendbuf(sdbuf);
	//
	//} while (1);
	string str;
	cout << "Please input your UserName: ";
	getline(cin,str);
	sock.setUserName(str);
	cout << "Please input your Password: ";
	getline(cin, str);
	sock.setPassword(str);
	cout<<"Receive "<<sock.recvbuf()<<"Bytes\n";
	cout << sock.getRecv();
	sock.login();
	cout << "Receive " << sock.recvbuf() << "Bytes\n";
	cout << sock.getRecv();
	sock.list();
	cout << "Receive " << sock.recvbuf() << "Bytes\n";
	cout << sock.getRecv();
	while (1)
	{
		string str1;
		getline(cin, str1);
		sock.sendbuf(str1);
		cout << "Receive " << sock.recvbuf() << "Bytes\n";
		cout << sock.getRecv()<< "\n";
		if (str1 == "exit") break;
	}
	system("pause");
    return 0;
}
