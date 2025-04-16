/*
	Ex7-4 PartAdder.exe 1 5와 Ex7-4 PartAdder.exe 6 10 이라는 프로그램을 각각 실행
	1+2+3+4+5
	6+7+8+9+10
	=55
	
	자식 프로세스가 종료되면, 부모 프로세스가 GetExitCodeProcess를 통해 각각의 합을 받아 최종 합계 출력
*/

#include<stdio.h>
#include<tchar.h>
#include<Windows.h>

int _tmain(int argc, TCHAR* argv[]) {
	STARTUPINFO si1 = { 0, };
	STARTUPINFO si2 = { 0, };

	PROCESS_INFORMATION pi1;
	PROCESS_INFORMATION pi2;

	DWORD return_val1;
	DWORD return_val2;

	TCHAR command1[] = _T("Ex7-4_PartAdder.exe 1 5");
	TCHAR command2[] = _T("Ex7-4_PartAdder.exe 6 10");

	DWORD sum = 0;

	si1.cb = sizeof(si1);	// 구조체의 크기를 초기화
	si2.cb = sizeof(si2);

	CreateProcess(NULL, command1, NULL, NULL, TRUE, 0, NULL, NULL, &si1, &pi1);	// 프로세스 생성
	CreateProcess(NULL, command2, NULL, NULL, TRUE, 0, NULL, NULL, &si2, &pi2);

	CloseHandle(pi1.hThread);	// 프로세스가 이미 실행중이므로 스레드 핸들은 필요가 없기에 종료
	CloseHandle(pi2.hThread);

	WaitForSingleObject(pi1.hProcess, INFINITE);	// 자식 프로세스가 종료될 때까지 무한 대기
	WaitForSingleObject(pi2.hProcess, INFINITE);

	GetExitCodeProcess(pi1.hProcess, &return_val1);	// 자식 프로세스가 ExitProcess(합계)로 종료하면 그 값을 얻는 코드
	GetExitCodeProcess(pi2.hProcess, &return_val2);

	// 자식 프로세스에서 오류 발생 시 나오는 코드 -1을 반환받으면 작동하는 코드
	if (return_val1 == -1 || return_val2 == -1)
		return -1; // 함수 호출 오류 발생으로 종료

	// 둘 다 정상 종료시 합계 계산
	sum += return_val1;
	sum += return_val2;

	_tprintf(_T("Total : %d \n"), sum);	// 결과 출력

	CloseHandle(pi1.hProcess);	// 프로세스 핸들 닫아서 메모리 누수 방지
	CloseHandle(pi2.hProcess);

	_fgetchar();	// 바로 꺼지는거 방지

	return 0;
}
