/*
CompletionRoutineFile.cpp
���α׷� ���� : ���� ���� �Ϸ� �� �Ϸ� ��ƾ ���� (Ȯ�� I/O)
*/

#include <stdio.h>
#include <tchar.h>
#include <windows.h>

// ���������� ���Ͽ� �� ���ڿ� ������ ����
TCHAR strData[] = 
	_T("South Korean battery material companies are emerging as key players in Tesla's revamped supply chain \n")
	_T("Silicon cathode materials offer significantly higher capacity \n")
	_T("The 2170 cylindrical battery is currently Tesla's most widely used cell type \n")
	_T("Despite announcing ambitious plans during Battery Day 2020 to produce its own batteries \n")
	_T("Tesla has faced challenges in achieving mass production of the highperformance 4680 cells.");

/*
* �Ϸ� ��ƾ �Լ� ����
* WriteFileEx()�� �Ϸ�Ǹ� ȣ��� �ݹ� �Լ�
*/
VOID WINAPI FileIOCompletionRoutine(DWORD, DWORD, LPOVERLAPPED);

int _tmain(int argc, TCHAR * argv[])
{
	TCHAR fileName[] = _T("data.txt");

	// ���� ����(�񵿱� I/O�� �ڵ� ����)
	// data.txt�� ���� �������� �񵿱� ���(FILE_FLAG_OVERLAPPED)�� ��
	HANDLE hFile = CreateFile( fileName, GENERIC_WRITE, FILE_SHARE_WRITE, 0, CREATE_ALWAYS, FILE_FLAG_OVERLAPPED, 0);

	if (hFile == INVALID_HANDLE_VALUE) {
		_tprintf(_T("File creation failed! \n"));
		return -1;
	}

	// OVERLAPPED ����ü �غ�
	OVERLAPPED overlappedInst;
	memset(&overlappedInst, 0, sizeof(overlappedInst));
	overlappedInst.hEvent = (HANDLE)1234;	// ������ 1234��� ������ �� �ο�

	// �񵿱� ������� strData�� data.txt�� ���
	// �۾� �Ϸ�� FileIOCompletionRoutine() �ڵ� ȣ��
	WriteFileEx(hFile, strData, sizeof(strData), &overlappedInst, FileIOCompletionRoutine);
	
	SleepEx(100, TRUE);	// �����带 alertable ���·� 100ms ���� ����Ŵ, �̰� �ؾ��� I/O�� ������ �ݹ� �Լ��� ȣ���
	CloseHandle(hFile);
	return 1;
}

VOID WINAPI FileIOCompletionRoutine (DWORD errorCode, DWORD numOfBytesTransferred, LPOVERLAPPED overlapped)
{
	_tprintf(_T("*************File write result**************\n"));
	_tprintf(_T("Error code : %u \n"), errorCode);
	_tprintf(_T("Transferred bytes len : %u\n"), numOfBytesTransferred);
	_tprintf(_T("The other info: %u\n"), (DWORD)overlapped->hEvent);
}