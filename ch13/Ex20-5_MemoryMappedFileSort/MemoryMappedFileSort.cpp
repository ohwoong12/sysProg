#include <stdio.h>
#include <tchar.h>
#include <windows.h>

void SortIntData(int* pSortArr, int num);

int _tmain(int argc, TCHAR* argv[]) {
	// 1단계 : 파일 핸들 생성
	// 파일 핸들 있어야지 메모리 매핑 가능
	// CraeteFile()로 test.dat 파일 생성
	HANDLE hFile = CreateFile(_T("test.dat"), GENERIC_READ | GENERIC_WRITE, 0, NULL, CREATE_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);

	if (hFile == INVALID_HANDLE_VALUE)
		_tprintf(_T("File create failed! \n"));

	// 2단계 : 파일 연결 오브젝트 생성
	// 파일 내용을 메모리에 연결하기 위해 커널 오브젝트 생성
	// 최대 크기: 10KB
	// 읽기 쓰기 권한으로 10KB 메모리 매핑 생성
	// 이름 부여하지 않고 비공유 형태
	HANDLE hMapFile = CreateFileMapping(hFile, NULL, PAGE_READWRITE, 0, 1024 * 10, NULL);
	if (hMapFile == NULL) {
		_tprintf(_T("Could not create map of file \n"));
	}

	
	// 3단계 : 가상 메모리에 연결
	// 매핑된 메모리를 포인터로 연결
	// 리턴된 pWrite는 int* 배열처럼 사용 가능
	// 이 메모리를 통해 파일 내용을 배열처럼 다룸
	int* pWrite = (int*)MapViewOfFile(hMapFile, FILE_MAP_ALL_ACCESS, 0, 0, 0);
	if (pWrite == NULL)
		_tprintf(_T("Could not map view of file"));

	// 메모리 공간에 직접 데이터 저장
	pWrite[0] = 1, pWrite[1] = 3, pWrite[2] = 0;
	pWrite[3] = 2, pWrite[4] = 4, pWrite[5] = 5;
	pWrite[6] = 8, pWrite[7] = 6, pWrite[8] = 7;
	SortIntData(pWrite, 9); // SortIntData()로 버블 정렬 수행 -> 정렬 결과는 메모리에 저장 -> 파일에도 자동 반영

	_tprintf(_T("%d %d %d \n"), pWrite[0], pWrite[1], pWrite[2]);
	_tprintf(_T("%d %d %d \n"), pWrite[3], pWrite[4], pWrite[5]);
	_tprintf(_T("%d %d %d \n"), pWrite[6], pWrite[7], pWrite[8]);

	UnmapViewOfFile(pWrite);	// 메모리 연결 해제
	CloseHandle(hMapFile);		// 핸들 닫기
	CloseHandle(hFile);

	_tprintf(_T("\nEnd of process! \n"));
	return 1;
}

// bubble sort
void SortIntData(int* pSortArr, int num) {
	int temp;
	for (int i = 0; i < num; i++) {
		for (int j = 0; j < num - 1; j++) {
			if (pSortArr[j] > pSortArr[j + 1]) {
				temp = pSortArr[j + 1];
				pSortArr[j + 1] = pSortArr[j];
				pSortArr[j] = temp;
			}
		}
	}
}