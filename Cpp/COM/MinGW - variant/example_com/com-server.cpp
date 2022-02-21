

#include "./headers/all-include.h"




HRESULT __stdcall DllGetClassObject ( REFCLSID rclsid, REFIID riid, LPVOID FAR* pSomeInterfaceCF ) {

	HRESULT hr = 0 ;

	printf( " \n\nStart Start DllGetClassObject." ) ;

	if ( rclsid != CLSID_ExampleClass ) {

		printf( "\n\n DllGetClassObject: CLASS_E_CLASSNOTAVAILABLE" ) ;
		return CLASS_E_CLASSNOTAVAILABLE ;
	}

	ExampleClassFactory * pECFInst = new ExampleClassFactory ;

	if ( pECFInst == NULL ) {

		printf( "\n\n DllGetClassObject: E_OUTOFMEMORY" ) ;
		return E_OUTOFMEMORY ;
	}

	hr = pECFInst -> QueryInterface ( (REFIID) riid, (LPVOID FAR*) pSomeInterfaceCF ) ;

	return hr ;
}




HRESULT __stdcall DllCanUnloadNow ( void ) {

	printf( "\n\n Start DllCanUnloadNow." ) ;

	if ( cObjCounter > 0 || cLockCounter > 0  ) {

		printf( "\n\n DllCanUnloadNow: S_FALSE, obj-counter = 0x%x, lock-counter = 0x%x", cObjCounter, cLockCounter) ;
		return S_FALSE ;
		}
	else
		{

		printf( "\n\n DllCanUnloadNow: S_OK" ) ;
		return S_OK ;
		}
}




BOOL DllMain ( HINSTANCE hModule, DWORD ul_reason_for_call, LPVOID lpReserved ) {

	switch (ul_reason_for_call) {
	case DLL_PROCESS_ATTACH:

		printf( "\n\n Start DllMain by reason DLL_PROCESS_ATTACH." ) ;

	case DLL_THREAD_ATTACH:

		printf( "\n\n Start DllMain by reason DLL_THREAD_ATTACH." ) ;

	case DLL_THREAD_DETACH:

		printf( "\n\n Start DllMain by reason DLL_THREAD_DETACH." ) ;

	case DLL_PROCESS_DETACH:

		printf( "\n\n Start DllMain by reason DLL_PROCESS_DETACH." ) ;

		break;
	}
	return TRUE;
}



