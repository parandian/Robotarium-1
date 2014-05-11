#include "Network.h"

cNetwork::cNetwork(void)
{
}

cNetwork::~cNetwork(void)
{
}

bool cNetwork::startThread(sSceneState* sStates)
{
	states = sStates;
	m_Thread = boost::thread(&cNetwork::start, this);
	return 1;
}

bool cNetwork::commence()
{
	redirect2Console();
	std::cout << "netMan>> Network Manager Initialized!" << std::endl;
	if (!setupWinSock())
	{
		std::cout << "netMan>> Failed Setting up WinSock!" << std::endl;
		return 0;
	}
	std::cout << "netMan>> WinSock Initialized Successfully!" << std::endl;
	if (!startConnection())
	{
		std::cout << "netMan>> Failed Starting Connection!" << std::endl;
		return 0;
	}
	std::cout << "netMan>> Connection Started Successfully!" << std::endl;
	std::cout << "netMan>> Starting Transaction!" << std::endl;
	if (!startTransaction())
	{
		std::cout << "netMan>> Failed Starting Transaction! :p" << std::endl;
		return 0;
	}

	return 1;
}
bool cNetwork::start()
{
	if(!commence())
	{
		std::cout << "netMan>> netMan is Shutting Down..." << std::endl;
	}

	// TODO! shutdown code!
	std::cout << "netMan>> LaFin!" << std::endl;
	return 1;
}

bool cNetwork::setupWinSock()
{
	WORD version;
	int error;
	version = MAKEWORD( 2, 2 );
	error = WSAStartup( version, &wsaData );

	if (error != NO_ERROR)
	{
		return 0;
	}

	return 1;
}

bool cNetwork::startConnection()
{
	client = socket(AF_INET, SOCK_STREAM, IPPROTO_TCP);

	if (client == INVALID_SOCKET) {
        wprintf(L"socket function failed with error: %ld\n", WSAGetLastError());
        WSACleanup();
        return 1;
    }

	sin.sin_family = AF_INET; //TCP-IP
	
	sin.sin_addr.s_addr = inet_addr("192.168.5.247");
	
	sin.sin_port = htons(123); // Remote Port

	std::cout << "netMan>> Trying to Start Connection....!" << std::endl;
	if ( connect(client, (sockaddr *)&sin, sizeof sin ) == SOCKET_ERROR )
	{
		return 0;
	}
	return 1;
}

bool cNetwork::startTransaction()
{
	int RetVal = SOCKET_ERROR; 
	double *q1, *q2, *q3;

	do
	{
		boost::this_thread::sleep( boost::posix_time::milliseconds(1) );
		RetVal = send(client, (char *)states->robotState.jointPos, 3*sizeof(double), 0);
		if ((RetVal == 0)||(RetVal == WSAECONNRESET)||(RetVal == WSAECONNABORTED))
		{
			printf("netMan>> Connection closed at other end.");
			return 0;
		}

		RetVal = recv(client, rxBuff, RetVal, 0);

		if ( RetVal > 0 )
		{
			states->remoteJoints[0] = *((double *)(rxBuff));
			states->remoteJoints[1] = *((double *)(rxBuff + sizeof(double)));
			states->remoteJoints[2] = *((double *)(rxBuff + 2*sizeof(double)));
			//q2 = (double *)(rxBuff + sizeof(double));
			//q3 = (double *)(rxBuff + 2*sizeof(double));
			//printf("~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~~\n q_1 := %f , q_2 := %f , q_3 := %f \n", 
			//	*q1, *q2, *q3);
		}
		else if ( RetVal == 0 )
			printf("netMan>> Connection Closed!\n");
		else
			printf("netMan>> 'recv' Failed: %d\n", WSAGetLastError());
	}while(RetVal > 0);
	boost::this_thread::sleep(boost::posix_time::milliseconds(10));
	return 1;
}