

#include <windows.h>	// Req for Struct, Interface (in objbase.h).
#include <initguid.h>
#include <stdio.h>


#include "./headers/guid-defs.h"
#include "./headers/cls-defs.h"




int main(void){

	HRESULT hr = 0 ;
	VOID * pIClassFactory = NULL ;
	LPUNKNOWN pUnk = NULL ;

	printf( "\n\n COM user started." ) ;

	hr = CoInitialize ( NULL ) ;

	if ( ! SUCCEEDED ( hr ) ) {

		printf( "\n\n CoInitialize unsucceeded !" ) ;
		return FALSE ;
		}


// CoCreateInstance

	hr = CoGetClassObject ( CLSID_ExampleClass, CLSCTX_INPROC_SERVER, NULL, IID_IClassFactory, (VOID**) &pIClassFactory ) ; 

	if ( ! SUCCEEDED ( hr ) ) {

		char buffer [120] ;
		FormatMessage ( FORMAT_MESSAGE_FROM_SYSTEM, NULL, hr, LANG_SYSTEM_DEFAULT, buffer, 120, NULL ) ;

		printf( "\n\n 'CoGetClassObject(...)' unsucceeded !" ) ;
		MessageBoxA ( 0x0, buffer, "Title", MB_ICONINFORMATION ) ;

		return FALSE ;
		}



	VOID * ppvObject = NULL ;

	( (ExampleClassFactory*) pIClassFactory ) -> CreateInstance ( NULL, IID_IExampleClass, (VOID**) &ppvObject ) ;

	( (IExampleClass*)       ppvObject      ) -> ExampleMethod () ;

	( (IExampleClass*)       ppvObject      ) -> Release () ;
	( (ExampleClassFactory*) pIClassFactory ) -> Release () ;

	CoUninitialize () ;

	printf( "\n\n End. Bye-bye. " ) ;
	MessageBoxA ( 0x0, "Press Ok to finish.", "Title", MB_ICONINFORMATION ) ;

        return TRUE ;
}










