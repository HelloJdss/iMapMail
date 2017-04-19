#ifndef __Wsa_H__
#define __Wsa_H__

#include "stdafx.h"

class Wsa
{
public:
	Wsa();
	bool isValid();
	~Wsa();

private:
	WSADATA wsaData;
	int nRC;
	bool valid;
};


#endif // !__Wsa_H__
