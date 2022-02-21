

/* "Quark Windows console" v. 0.16.05.01.
   Console wrapper for quark.dll.
   Support Quark's console input/output via regular Windows console.
   Created by Alexandr (Shurko) Stadnichenko. Public domain. */




#include "stdafx.h"
#include "qwcdll.h"
#include <stdio.h>
#include <jni.h>    //    <-- You must know were is it.




void	qwc_emit (void);
void	gameengine_api_proc_1 (void);




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

JNIEnv * global_env ;




// Push NULL placeholder on top of Quark data stack.

char qwc_script_push_0_on_tos [] = " \
0 \
" ;




// Main Qwc initial script.
// Note, first string " : emit [ CALL, ] DROP ; " expect qwc_emit() function pointer on top of data stack.

char initial_script_1 [] = " \
: (emit) [ CALL, ] DROP ; \
' (emit) TO EMIT \
: emit EMIT ; \
' NOOP TO BYE \
: CR 10 EMIT ; \
: cr CR ; \
: type TYPE ; \
" ;





// Main engine initial script.
// Note, first string " : ENG-API-PROC-1 [ CALL, ] DROP ; " expect gameengine_api_proc_1 function pointer on top of data stack.

char engine_initial_script_1 [] = " \
: ENG-API-PROC-1 [ CALL, ] ; \
" ;




extern "C" JNIEXPORT void JNICALL Java_Qwcdll_qwc(JNIEnv * env, jclass cl){

	global_env = env ;


	printf( "\n\n                               QUARK WIN CON\n\n" ) ;
	printf( "\n               Console wrapper for quark.dll. Build 2016-05-01." ) ;
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
		mov eax, offset initial_script_1
	} ;

	result = quark_Evaluate() ;

	if ( result != 0 ) {
		printf( "\n Error in initial_script_1 on char number %d\n", result ) ;
	}




	__asm{
		mov eax, offset qwc_script_push_0_on_tos
	} ;

	result = quark_Evaluate() ;

	if ( result != 0 ) {
		printf( "\n Error in qwc_script_push_0_on_tos on char number %d\n", result ) ;
	}
	
	quark_tos = (int*) (stack_base + (quark_GetDepth()-1)*4) ;
	* quark_tos = (int) gameengine_api_proc_1 ;
		
	__asm{
		mov eax, offset engine_initial_script_1
	} ;

	result = quark_Evaluate() ;

	if ( result != 0 ) {
		printf( "\n Error in engine_initial_script_1 on char number %d\n", result ) ;
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
}




void qwc_emit (void) {

	quark_tos = (int*) (stack_base + (quark_GetDepth()-1)*4) ;

	printf( "%c", * quark_tos ) ;
}




void gameengine_api_proc_1 (void) {

	jclass class_FUser	= global_env -> FindClass("FUser") ;
	jmethodID id_JApiProc	= global_env -> GetStaticMethodID ( class_FUser, "api_proc_1", "()V" ) ;
	jobject obj_ret		= global_env -> CallStaticObjectMethod ( class_FUser, id_JApiProc ) ;
}



