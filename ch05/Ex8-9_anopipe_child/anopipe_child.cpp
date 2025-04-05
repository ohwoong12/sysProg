#define _CRT_SECURE_NO_WARNINGS
#include <stdio.h>
#include <tchar.h>
#include <windows.h>
#include <conio.h> // _getch() ���

int _tmain(int argc, LPTSTR argv[]) {
    _tprintf(_T("[Child Pipe]\n"));
    _tprintf(_T("argc : %d\n"), argc);
    /* �׽�Ʈ �ڵ�
    for (int i = 0; i < argc; ++i) {
        _tprintf(_T("argv[%d] : %s\n"), i, argv[i]);
    }
    */


    // ���� ������ ���� ������ ���� ��� �� ����
    if (argc != 3) {
        _fputts(_T("Usage: anopipe_child <handle> <message size>\n"), stdout);
        _tprintf(_T("Press any key to exit..."));
        _getch();   // �ܼ� â�� �ٷ� ������� �ʵ��� ���
        return 1;
    }

    // ����� �μ��� ���� �ڵ�� �޽��� ũ�⸦ ������  
    // (�ڵ��� �θ� ���μ������� ��ӹ��� ���̾�� ��)
    HANDLE hReadPipe = (HANDLE)_ttoi(argv[1]);
    DWORD messageSize = (DWORD)_ttoi(argv[2]);

    TCHAR buffer[1024] = { 0 };
    DWORD bytesRead = 0;

    // �������κ��� ������ �б�  
    if (ReadFile(hReadPipe, buffer, messageSize, &bytesRead, NULL)) {
        buffer[bytesRead / sizeof(TCHAR)] = _T('\0');   // ���� ����Ʈ ���� ���� ���ڿ� ���� ���� �߰� (�� TCHAR�� sizeof(TCHAR) ����Ʈ)

        _tprintf(_T("hReadPipe : %u\n"), (unsigned)hReadPipe);
        _tprintf(_T("bytesWritten : %u\n"), messageSize);
        _tprintf(_T("string recv: %s, read in bytes : %u\n"), buffer, bytesRead);
    }
    else {
        _fputts(_T("Failed to read from pipe.\n"), stdout);
    }

    CloseHandle(hReadPipe); // �ڵ� �ݱ�

    _tprintf(_T("Press any key to exit..."));
    _getch(); // �ܼ� â�� �ٷ� ������� �ʵ��� ���

    return 0;
}