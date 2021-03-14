#include "CPipeServer.h"

CPipeServer::CPipeServer(LPCSTR pipeName, DWORD pipeSize)
{
    m_BytesRead = 0;
    m_TotalBytesRead = 0;
    m_pBuffer = nullptr;
    m_BufferSize = pipeSize;
    
    m_pipeName = PIPE_DIR;
    m_pipeName.append(pipeName);

    if(m_pipeName.length() > MAX_PIPE_PATH)
    {
        std::cout << "Error: pipe name too long." << std::endl;
        return;
    }
    
    m_hPipe = CreateNamedPipeA(
        m_pipeName.c_str(),
        PIPE_ACCESS_INBOUND,
        PIPE_TYPE_BYTE,
        1,
        0,
        0,
        0,
        nullptr);

    if (m_hPipe == NULL || m_hPipe == INVALID_HANDLE_VALUE) {
        std::cout << "Error with Pipe Creation." << std::endl;
        return;
    }

    m_pBuffer = (BYTE*) calloc(m_BufferSize, 0);

    if(!m_pBuffer)
    {
        std::cout << "Failed to allocate buffer." << std::endl;
        CloseHandle(m_hPipe);
        return;
    }
}

CPipeServer::~CPipeServer(){
	if (m_pBuffer) {
        free(m_pBuffer);
    }
    if (m_hPipe != 0 && m_hPipe != INVALID_HANDLE_VALUE) {
        CloseHandle(m_hPipe);
    }
}

BOOL CPipeServer::listen()
{
    std::cout << "Waiting for client..." << std::endl;

    BOOL result = ConnectNamedPipe(m_hPipe, NULL);
    if (!result) {
        std::cout << "Failed to make connection on named pipe." << std::endl;
        CloseHandle(m_hPipe);
        return result;
    }
    return result;
}

BOOL CPipeServer::read()
{
    if (m_pBuffer)
    {
        BOOL result = ReadFile(m_hPipe, m_pBuffer, m_BufferSize, &m_BytesRead, nullptr);
        if (result)
        {
            m_TotalBytesRead += m_BytesRead;
            return result;
        }
        else
        {
            std::cout << "Failed to read data from the pipe." << std::endl;
            std::cout << "Error Code: " << GetLastError();
            return result;
        }
    }
    return false;
}

void CPipeServer::processPacket()
{
    //Default debug packet processing
    m_pBuffer[m_BytesRead - 1] = 0;
    std::cout << m_BytesRead << " : " << m_pBuffer << std::endl;
}

void CPipeServer::serverLoop()
{
    while (Read())
    {
        ProcessPacket();
    }
}
