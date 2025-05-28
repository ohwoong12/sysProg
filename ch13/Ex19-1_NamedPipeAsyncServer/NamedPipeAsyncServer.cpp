#define _CRT_SECURE_NO_WARNINGS

#include <stdio.h>
#include <tchar.h>
#include <windows.h>

#define BUF_SIZE 1024

int CommToClient(HANDLE);

int _tmain(int argc, TCHAR* argv[])
{
	TCHAR name[] = _T("\\\\.\\pipe\\simple_pipe");
	LPTSTR pipeName = name;
	HANDLE hPipe;
	while (1) {
		hPipe = CreateNamedPipe(
			pipeName,
			PIPE_ACCESS_DUPLEX | FILE_FLAG_OVERLAPPED, // ��ø I/O mode
			PIPE_TYPE_MESSAGE | PIPE_READMODE_MESSAGE | PIPE_WAIT,
			PIPE_UNLIMITED_INSTANCES,
			BUF_SIZE, // ��� ���� ������
			BUF_SIZE, // �Է� ���� ������
			20000, // Client�� WaitNamedPipe()�� ����instance�� ��ٸ��� �ð�
			NULL);		if (hPipe == INVALID_HANDLE_VALUE) {
			_tprintf(_T("CreatePipe failed!"));
			return -1;
		}

		// ���� Ȯ���� ���� ���� ���
		_tprintf(_T("Server is waiting for Client's request!!\n\n"));

		BOOL isSuccess;
		isSuccess = ConnectNamedPipe(hPipe, NULL);

		// GetLastError()�� ERROR_PIPE_CONNECTED�̸�
		// FALSE�� ���ϵǴ��� ����-Ŭ���̾�Ʈ������ ���� ����Ǿ����� �ǹ�
		if (isSuccess == FALSE && (GetLastError() == ERROR_PIPE_CONNECTED))
			isSuccess = TRUE;
		if (isSuccess)
			CommToClient(hPipe);
		else
			CloseHandle(hPipe);
	}
	return 1;
}

int CommToClient(HANDLE hPipe)
{
	TCHAR fileName[MAX_PATH];
	TCHAR dataBuf[BUF_SIZE];
	char cBuf[BUF_SIZE];
	BOOL isSuccess;
	DWORD fileNameSize;

	isSuccess = ReadFile( hPipe, fileName, MAX_PATH * sizeof(TCHAR), &fileNameSize, NULL);
	if (!isSuccess || fileNameSize == 0) {
		_tprintf(_T("Pipe read message error!\n"));
		return -1;
	}

	HANDLE hFile = CreateFile(fileName, GENERIC_READ, FILE_SHARE_READ, NULL, OPEN_EXISTING, FILE_ATTRIBUTE_NORMAL, NULL);
	OVERLAPPED overlappedInst;
	memset(&overlappedInst, 0, sizeof(overlappedInst));
	overlappedInst.hEvent = CreateEvent(
		NULL, // default security attribute
		TRUE, // manual-reset event
		TRUE, // initial state - Signaled
		NULL); // unnamed event object

	DWORD bytesWritten = 0;
	DWORD bytesRead = 0;
	DWORD bytesWrite = 0;
	DWORD bytesTransfer = 0;

	//_tprintf(_T("fileName received: [%s]\n"), fileName);

	while (1) {
		isSuccess = ReadFile(hFile, cBuf, BUF_SIZE, &bytesRead, NULL);
		if (!isSuccess) {
			_tprintf(_T("File read error! \n"));
			break;
		}
		else if (bytesRead == 0) {
			_tprintf(_T("End of file. No more data to read\n"));
			break;
		}
		for (DWORD i = 0; i < bytesRead; i++) {
			dataBuf[i] = cBuf[i];
		}		bytesWrite = bytesRead;
		// ��� ��ȯ�ϱ� ������ ��ȯ �������� bytesWritten ���� 0�� �� ����
		isSuccess = WriteFile(hPipe, dataBuf, bytesWrite * sizeof(TCHAR), &bytesWritten, &overlappedInst);
		if (!isSuccess && GetLastError() != ERROR_IO_PENDING) {
			_tprintf(_T("Pipe write message error! \n"));
			break;
		}
		//------------------------------------
		// �ٸ� �۾��� �� �� �ִ� ��ȸ
		//------------------------------------
		WaitForSingleObject(overlappedInst.hEvent, INFINITE);
		GetOverlappedResult(hPipe, &overlappedInst, &bytesTransfer, FALSE);
		_tprintf(_T("Transferred data size : %u \n"), bytesTransfer);
	}
	FlushFileBuffers(hPipe);
	DisconnectNamedPipe(hPipe);
	CloseHandle(hPipe);
	return 1;
}