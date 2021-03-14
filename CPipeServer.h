#pragma once
#include <Windows.h>
#include <iostream>
#include <string>
#include "CPipeCommon.h"

// Single instance one-way inbound server
class CPipeServer
{
	HANDLE m_hPipe;
	BOOL read();

	// Please override this function
	virtual void processPacket();
public:
	DWORD m_BytesRead;
	DWORD m_TotalBytesRead;
	BYTE* m_pBuffer;
	DWORD m_BufferSize;
	std::string m_pipeName;

	CPipeServer(LPCSTR pipeName, DWORD pipeSize);
	~CPipeServer();
	BOOL listen();
	void serverLoop();
	
};

