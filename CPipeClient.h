#pragma once
#include "CPipeCommon.h"
#include <Windows.h>
#include <iostream>
#include <string>

// Single instance one-way outbound client

class CPipeClient
{
	HANDLE m_hPipe;
	BOOL write(DWORD size);

public:
	DWORD m_BytesWritten;
	DWORD m_TotalBytesWritten;
	BYTE* m_pBuffer;
	DWORD m_BufferSize;
	std::string m_pipeName;
	
	CPipeClient(LPCSTR pipeName, DWORD pipeSize);
	~CPipeClient();
	BOOL send(BYTE* data, DWORD size);
};

