
// com.cpp: определяет экспортированные функции для приложения DLL.

#include "stdafx.h"
#include "all-include.h"



STDAPI  DllGetClassObject ( __in REFCLSID rclsid, __in REFIID riid, __deref_out LPVOID FAR* pSomeInterfaceCF ) {

	HRESULT hr = 0 ;

	printf( "\n\n Start DllGetClassObject." ) ;

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

STDAPI DllCanUnloadNow ( void ) {

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
