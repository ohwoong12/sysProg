/*
CompletionRoutineFile.cpp
프로그램 설명 : 파일 쓰기 완료 후 완료 루틴 실행 (확장 I/O)
*/

#include <stdio.h>
#include <tchar.h>
#include <windows.h>

// 전역변수로 파일에 쓸 문자열 데이터 선언
TCHAR strData[] = 
	_T("South Korean battery material companies are emerging as key players in Tesla's revamped supply chain \n")
	_T("Silicon cathode materials offer significantly higher capacity \n")
	_T("The 2170 cylindrical battery is currently Tesla's most widely used cell type \n")
	_T("Despite announcing ambitious plans during Battery Day 2020 to produce its own batteries \n")
	_T("Tesla has faced challenges in achieving mass production of the highperformance 4680 cells.");

/*
* 완료 루틴 함수 선언
* WriteFileEx()가 완료되면 호출될 콜백 함수
*/
VOID WINAPI FileIOCompletionRoutine(DWORD, DWORD, LPOVERLAPPED);

int _tmain(int argc, TCHAR * argv[])
{
	TCHAR fileName[] = _T("data.txt");

	// 파일 열기(비동기 I/O용 핸들 생성)
	// data.txt를 쓰기 전용으로 비동기 모드(FILE_FLAG_OVERLAPPED)로 엶
	HANDLE hFile = CreateFile( fileName, GENERIC_WRITE, FILE_SHARE_WRITE, 0, CREATE_ALWAYS, FILE_FLAG_OVERLAPPED, 0);

	if (hFile == INVALID_HANDLE_VALUE) {
		_tprintf(_T("File creation failed! \n"));
		return -1;
	}

	// OVERLAPPED 구조체 준비
	OVERLAPPED overlappedInst;
	memset(&overlappedInst, 0, sizeof(overlappedInst));
	overlappedInst.hEvent = (HANDLE)1234;	// 디버깅용 1234라는 임의의 값 부여

	// 비동기 방식으로 strData를 data.txt에 기록
	// 작업 완료시 FileIOCompletionRoutine() 자동 호출
	WriteFileEx(hFile, strData, sizeof(strData), &overlappedInst, FileIOCompletionRoutine);
	
	SleepEx(100, TRUE);	// 스레드를 alertable 상태로 100ms 동안 대기시킴, 이걸 해야지 I/O가 끝나고 콜백 함수가 호출됨
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