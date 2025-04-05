#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include <conio.h> // _getch() 사용

int _tmain(int argc, LPTSTR argv[]) {
    _tprintf(_T("[Child Pipe]\n"));
    _tprintf(_T("argc : %d\n"), argc);
    /* 테스트 코드
    for (int i = 0; i < argc; ++i) {
        _tprintf(_T("argv[%d] : %s\n"), i, argv[i]);
    }
    */


    // 인자 개수가 맞지 않으면 사용법 출력 후 종료
    if (argc != 3) {
        _fputts(_T("Usage: anopipe_child <handle> <message size>\n"), stdout);
        _tprintf(_T("Press any key to exit..."));
        _getch();   // 콘솔 창이 바로 종료되지 않도록 대기
        return 1;
    }

    // 명령줄 인수를 통해 핸들과 메시지 크기를 가져옴  
    // (핸들은 부모 프로세스에서 상속받은 값이어야 함)
    HANDLE hReadPipe = (HANDLE)_ttoi(argv[1]);
    DWORD messageSize = (DWORD)_ttoi(argv[2]);

    TCHAR buffer[1024] = { 0 };
    DWORD bytesRead = 0;

    // 파이프로부터 데이터 읽기  
    if (ReadFile(hReadPipe, buffer, messageSize, &bytesRead, NULL)) {
        buffer[bytesRead / sizeof(TCHAR)] = _T('\0');   // 읽은 바이트 수에 따라 문자열 종료 문자 추가 (각 TCHAR가 sizeof(TCHAR) 바이트)

        _tprintf(_T("hReadPipe : %u\n"), (unsigned)hReadPipe);
        _tprintf(_T("bytesWritten : %u\n"), messageSize);
        _tprintf(_T("string recv: %s, read in bytes : %u\n"), buffer, bytesRead);
    }
    else {
        _fputts(_T("Failed to read from pipe.\n"), stdout);
    }

    CloseHandle(hReadPipe); // 핸들 닫기

    _tprintf(_T("Press any key to exit..."));
    _getch(); // 콘솔 창이 바로 종료되지 않도록 대기

    return 0;
}