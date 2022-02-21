

/* "Quark Windows console" v. 0.16.04.30.
   Console wrapper for quark.dll.
   Support Quark's console input/output via regular Windows console.
   Created by Alexandr (Shurko) Stadnichenko. Public domain. */




#include <windows.h>
#include <stdio.h>




int qwc_emit (void);


HINSTANCE quark_dll_hinstance = NULL ;

FARPROC quark_Evaluate = NULL ;
FARPROC quark_Init     = NULL ;
FARPROC quark_Done     = NULL ;
FARPROC quark_GetCode  = NULL ;
FARPROC quark_GetData  = NULL ;
FARPROC quark_GetStack = NULL ;
FARPROC quark_GetDepth = NULL ;

int result = 0x1234 ;
int stack_base = NULL ;
int * quark_tos = NULL ;

char str_to_eval [1024*4] = "" ;




// Push NULL placeholder on top of Quark data stack.

char qwc_script_push_0_on_tos [] = " \
0 \
" ;


// Note, first string " : emit [ CALL, ] DROP ; " expect qwc_emit() function pointer on top of data stack.
char initial_script1 [] = " \
: emit [ CALL, ] DROP ; \
' emit TO EMIT \
: BYE1 ; ' BYE1 TO BYE \
: CR 10 EMIT ; \
: type TYPE ; \
: cr CR ; \
" ;




int main(void){




	printf( "\n\n                               QUARK WIN CON\n\n" ) ;
	printf( "\n               Console wrapper for quark.dll. Build 2016-04-30." ) ;
	printf( "\n       Support Quark's console input/output via regular Windows console." ) ;
	printf( "\n           Created by Alexandr (Shurko) Stadnichenko. Public domain. \n\n" ) ;


	quark_dll_hinstance = LoadLibraryA("quark.dll") ;
	if ( quark_dll_hinstance == NULL ) { printf( "\n\n quark_dll_hinstance == NULL." ) ; } ;

	quark_Init     = GetProcAddress(quark_dll_hinstance, "Init") ;
	if ( quark_Init == NULL ) { printf( "\n\n quark_Init == NULL." ) ; } ;

	quark_Done     = GetProcAddress(quark_dll_hinstance, "Done") ;
	if ( quark_Done == NULL ) { printf( "\n\n quark_Done == NULL." ) ; } ;

	quark_Evaluate = GetProcAddress(quark_dll_hinstance, "Evaluate") ;
	if ( quark_Evaluate == NULL ) { printf( "\n\n quark_Evaluate == NULL." ) ; } ;

	quark_GetCode = GetProcAddress(quark_dll_hinstance, "GetCode") ;
	if ( quark_GetCode == NULL ) { printf( "\n\n quark_GetCode == NULL." ) ; } ;

	quark_GetData = GetProcAddress(quark_dll_hinstance, "GetData") ;
	if ( quark_GetData == NULL ) { printf( "\n\n quark_GetData == NULL." ) ; } ;

	quark_GetStack = GetProcAddress(quark_dll_hinstance, "GetStack") ;
	if ( quark_GetStack == NULL ) { printf( "\n\n quark_GetStack == NULL." ) ; } ;

	quark_GetDepth = GetProcAddress(quark_dll_hinstance, "GetDepth") ;
	if ( quark_GetDepth == NULL ) { printf( "\n\n quark_GetDepth == NULL." ) ; } ;




	quark_Init() ;
	stack_base = quark_GetStack() ;




	__asm{
		mov eax, offset qwc_script_push_0_on_tos
	} ;

	result = quark_Evaluate() ;

	if ( result != 0 ) {
		printf( "\n Error in qwc_script_push_0_on_tos on char number %d\n", result ) ;
	}
	
	quark_tos = (int*) (stack_base + (quark_GetDepth()-1)*4) ;
	* quark_tos = (int) qwc_emit ;
		
	__asm{
		mov eax, offset initial_script1
	} ;

	result = quark_Evaluate() ;

	if ( result != 0 ) {
		printf( "\n Error in initial_script1 on char number %d\n", result ) ;
	}




	for (;;){

		printf( "\n OK> " ) ;

		gets(str_to_eval) ;

		__asm{
			mov eax, offset str_to_eval
		} ;

		result = quark_Evaluate() ;

		if ( result != 0 ) {
			printf( "\n Error on char number %d\n", result ) ;
		}	
	
	} // "for" circle
	



//	quark_Done() ; // Cause of crash.
	return 0 ;
}




int qwc_emit (void) {

	quark_tos = (int*) (stack_base + (quark_GetDepth()-1)*4) ;

	printf( "%c", * quark_tos ) ;

	return 0 ;
}
