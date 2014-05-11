#define _WINSOCKAPI_
#include <windows.h>
#include "common/Application.h"

INT WINAPI WinMain( HINSTANCE hInst, HINSTANCE, LPSTR strCmdLine, INT )
{
    cApplication app;
	app.commence();
    return 0;
}
