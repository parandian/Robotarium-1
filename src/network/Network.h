#ifndef __NETWORK__
#define __NETWORK__

#define _WINSOCKAPI_
#include <winsock2.h>
#include <windows.h>
#include <boost/thread.hpp>
#include "Framework.h"
#include "comndp.h"


#define DEFAULT_PORT "123"
#define RX_BUFF_LEN 64
struct sTxStruct
{
	char b2;
	char b3;
	char b4;
};

class cNetwork
{
public:
	cNetwork(void);
	virtual ~cNetwork(void);
	bool startThread(sSceneState* sStates);
	bool start(void);
	bool commence(void);
private:
	boost::thread m_Thread;
	sSceneState* states;
	WSADATA wsaData;
	SOCKET client;
	struct hostent host;
	struct sockaddr_in sin;
	bool setupWinSock();
	bool startConnection();
	bool startTransaction();
	
	char * txBuff;
	double txData[3];
	char rxBuff[RX_BUFF_LEN];
};

#endif