
// dllmain.cpp: ?????????? ????? ????? ??? ?????????? DLL.

#include "stdafx.h"
#include <stdio.h>



BOOL APIENTRY DllMain ( HMODULE hModule, DWORD  ul_reason_for_call, LPVOID lpReserved ) {

	switch (ul_reason_for_call) {
	case DLL_PROCESS_ATTACH:

		printf( " \n\n Start DllMain by reason DLL_PROCESS_ATTACH." ) ;

	case DLL_THREAD_ATTACH:

		printf( " \n\n Start DllMain by reason DLL_THREAD_ATTACH." ) ;

	case DLL_THREAD_DETACH:

		printf( " \n\n Start DllMain by reason DLL_THREAD_DETACH." ) ;

	case DLL_PROCESS_DETACH:

		printf( " \n\n Start DllMain by reason DLL_PROCESS_DETACH." ) ;

		break;
	}
	return TRUE;
}

