#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <tchar.h>
#include <windows.h>

#define BUF_SIZE 1024
int commToClient(HANDLE);

int _tmain(int argc, TCHAR* argv[]) {
	LPCTSTR pipeName = _T("\\\\.\\pipe\\simple_pipe");
	HANDLE hPipe;

	while (1) {
		hPipe = CreateNamedPipe(pipeName, PIPE_ACCESS_DUPLEX, PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT
			,PIPE_UNLIMITED_INSTANCES, BUF_SIZE, BUF_SIZE, 20000, NULL);
		if (hPipe == INVALID_HANDLE_VALUE) {
			_tprintf(_T("CreatePipe failed"));
			return -1;
		}
		_tprintf(_T("Server is waiting for Client's request!! \n\n"));
		BOOL isSuccess = 0;
		isSuccess = ConnectNamedPipe(hPipe, NULL) ? TRUE : FALSE;
		if (isSuccess)
			commToClient(hPipe);
		else
			CloseHandle(hPipe);
	}
	return 1;
}

int commToClient(HANDLE hPipe)
{
	TCHAR fileName[MAX_PATH];
	TCHAR dataBuf[BUF_SIZE];
	char cBuf[BUF_SIZE];
	BOOL isSuccess;
	DWORD fileNameSize;

	isSuccess = ReadFile(hPipe, fileName, MAX_PATH * sizeof(TCHAR), &fileNameSize, NULL);
	
	if (!isSuccess || fileNameSize == 0) {
		_tprintf(_T("Pipe read message error!\n"));
		return -1;
	}

	FILE* filePtr = _tfopen(fileName, _T("r"));
	if (filePtr == NULL) {
		_tprintf(_T("File open fault!\n"));
		return -1;
	
	}
	
	DWORD bytesWritten = 0;
	DWORD bytesRead = 0;
	
	while (!feof(filePtr)) {
		bytesRead = fread(cBuf, 1, BUF_SIZE, filePtr);
		for (UINT i = 0; i < bytesRead; i++)
			dataBuf[i] = cBuf[i];
		WriteFile(hPipe, dataBuf, bytesRead * sizeof(TCHAR), &bytesWritten, NULL);
		if (bytesRead * sizeof(TCHAR) != bytesWritten) {
			_tprintf(_T("Pipe write message error! \n"));
			break;
		}
	}
	
	FlushFileBuffers(hPipe);
	DisconnectNamedPipe(hPipe);
	CloseHandle(hPipe);
	return 1;
}