#include "CPipeClient.h"

BOOL CPipeClient::write(DWORD size)
{
    if (m_pBuffer) {
        BOOL result = WriteFile(
            m_hPipe,
            m_pBuffer,
            size,
            &m_BytesWritten,
            NULL
        );
        return result;
    }
    return false;
}

CPipeClient::CPipeClient(LPCSTR pipeName, DWORD pipeSize)
{
    m_BufferSize = pipeSize;
    m_pBuffer = (BYTE*) malloc(pipeSize);
    m_pipeName = PIPE_DIR;
    m_pipeName.append(pipeName);
    WaitNamedPipeA(m_pipeName.c_str(), NMPWAIT_WAIT_FOREVER);
    m_hPipe = CreateFileA(
        m_pipeName.c_str(),
        GENERIC_WRITE,
        FILE_SHARE_READ | FILE_SHARE_WRITE,
        NULL,
        OPEN_EXISTING,
        FILE_ATTRIBUTE_NORMAL,
        NULL
    );

    if (m_hPipe == NULL || m_hPipe == INVALID_HANDLE_VALUE)
    {
        std::cout << "Failed to connect to pipe server." << std::endl;
        return;
    }
}

CPipeClient::~CPipeClient()
{
    if (m_pBuffer) {
        free(m_pBuffer);
    }
    if (m_hPipe != 0 && m_hPipe != INVALID_HANDLE_VALUE) {
        CloseHandle(m_hPipe);
    }
}

BOOL CPipeClient::send(BYTE* data, DWORD size)
{
    if (size > m_BufferSize) {
        return FALSE;
    }
    if (!memcpy_s(m_pBuffer, m_BufferSize, data, size)) {
       return write(size);
    }
    return FALSE;
}
