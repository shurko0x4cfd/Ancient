



// ----- Implementation of ExampleClass class. -----


ExampleClass:: ExampleClass () {

	printf ( "\n\n EampleClass constructor." ) ;
	cECREFcounter = 0 ;
	}

ExampleClass::~ExampleClass () { printf ( "\n\n xampleClass destructor." ) ; }

STDMETHODIMP
ExampleClass::QueryInterface ( REFIID riid, LPVOID FAR* ppv ) {

	printf ( "\n\n Start ExampleClass QueryInterface" ) ;

	*ppv = NULL ;

	if ( riid == IID_IUnknown ) {

		*ppv = (IUnknown*) this ;
		printf ( "\n\n QueryInterface (ExampleClass): geted IUnknown." ) ;
	}

	if ( riid == IID_IExampleClass ) {
		*ppv = (IExampleClass*) this ;
		printf ( "\n\n QueryInterface(ExampleClass): geted IExampleClass." ) ;
	}

	if ( *ppv == NULL ) {

		printf ( "\n\n QueryInterface(ExampleClass): E_NOINTERFACE." ) ;
		return E_NOINTERFACE ;
	}

	((IUnknown*) *ppv) -> AddRef () ;

	return S_OK ;
}


STDMETHODIMP_ ( ULONG )
ExampleClass::AddRef () {

	printf ( "\n\n Start ExampleClass.AddRef." ) ;
	return ++cECREFcounter ;
}


STDMETHODIMP_ ( ULONG )
ExampleClass::Release () {

	printf ( "\n\n Start ExampleClass.Release." ) ;

	if( --cECREFcounter > 0x0 ) { return cECREFcounter ; }

	printf ( "\n\n Start ExampleClass: delete this." ) ;

	delete this ;
	return 0x0 ;
}


STDMETHODIMP
ExampleClass::ExampleMethod () {

	printf ( "\n\n Start ExampleMethod." ) ;
	return S_OK ;
}


// ----- ExampleClass class implemented. -----




extern "C" __declspec(dllexport) ExampleClass * CreateExampleClassObject ( void ) {

	printf ( "\n\n Start CreateExampleClassObject." ) ;

	ExampleClass * pECInstance = NULL ;
	pECInstance = new ExampleClass () ;

	if ( pECInstance != NULL )
		{
		pECInstance -> AddRef () ;
		}
	else
		{
		delete pECInstance ;
		}

        return ( ExampleClass * ) pECInstance ;
}




// ----- Implementation of ExampleClassFactory class. -----


ExampleClassFactory:: ExampleClassFactory () {

	printf ( "\n\n ExampleClassFactory constructor." ) ;
	cECFREFcounter = 0 ;
}

ExampleClassFactory::~ExampleClassFactory () { printf ( "\n\n ExampleClassFactory destructor." ) ; }


STDMETHODIMP
ExampleClassFactory::QueryInterface ( REFIID riid, LPVOID * FAR ppv ) {


	printf ( "\n\n Start ExampleClassFactory QueryInterface" ) ;

	*ppv = NULL ;

	if ( riid == IID_IUnknown ) {

		*ppv = (IUnknown*) this ;
		printf ( "\n\n QueryInterface (ExampleClassFactory): geted IUnknown." ) ;
	}

	if ( riid == IID_IClassFactory ) {

		*ppv = ( IClassFactory * ) this ;
		printf ( "\n\n QueryInterface (ExampleClassFactory): geted IExampleClassFactory." ) ;
	}

	if ( *ppv == NULL ) {

		printf ( "\n\n QueryInterface (ExampleClassFactory): E_NOINTERFACE." ) ;
		return E_NOINTERFACE ; }

	( ( IClassFactory * ) * ppv ) -> AddRef () ;

	return S_OK ;
}


STDMETHODIMP_ ( ULONG )
ExampleClassFactory::AddRef () {

	printf ( "\n\n Start ExampleClassFactory AddRef." ) ;
	return ++cECFREFcounter ;
}


STDMETHODIMP_ ( ULONG )
ExampleClassFactory::Release () { 

	printf ( "\n\n Start ExampleClassFactory Release." ) ;

	if( --cECFREFcounter > 0x0 ) { return cECFREFcounter ; }

	printf ( "\n\n ExampleClassFactory: delete this." ) ;

	delete this ;
	return 0 ;
}


STDMETHODIMP
ExampleClassFactory::CreateInstance ( LPUNKNOWN pUnkOuter, REFIID riid, LPVOID FAR* ppvObject ) {

	printf( "\n\n Start CreateInstance." ) ;

	if ( pUnkOuter != 0 ) {

		printf( "\n\n ExampleClassFactory::CreateInstance : pUnkOuter != 0 . Return CLASS_E_NOAGGREGATION." ) ;
		return CLASS_E_NOAGGREGATION ;
		}

	ExampleClass * pECInst = CreateExampleClassObject () ;

	if ( pECInst == 0 )
		{

		printf( "\n\n ExampleClassFactory::CreateInstance : pECInst == 0 . Return E_OUTOFMEMORY." ) ;
		return E_OUTOFMEMORY ;
		}
	else
		{

		HRESULT hr = pECInst -> QueryInterface ( (REFIID) riid, (LPVOID FAR*) ppvObject ) ;

		if ( SUCCEEDED ( hr ) ) { ++cObjCounter ; }

		pECInst -> Release () ;

		return S_OK ;
		}
}


STDMETHODIMP
ExampleClassFactory::LockServer ( BOOL flag ) {

	printf( "\n\n Start ExampleClassFactory::LockServer." ) ;

	if ( flag )
		{
		printf( "\n\n LockServer (ExampleClassFactory) : ++" ) ;
		++cLockCounter ;
		}
	else
		{
		printf( "\n\n LockServer (ExampleClassFactory) : --" ) ;
		--cLockCounter ;
		}

	return NOERROR ;
}


// ----- ExampleClassFactory class implemented. -----



