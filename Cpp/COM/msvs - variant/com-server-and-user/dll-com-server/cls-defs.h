

#undef INTERFACE
#define INTERFACE ExampleClassFactory

// DECLARE_INTERFACE_ ( ExampleClassFactory, IClassFactory ) {

class ExampleClassFactory : public IClassFactory {

public:

STDMETHOD  ( QueryInterface ) ( THIS_ REFIID riid, LPVOID FAR* ppv ) ;
STDMETHOD_ ( ULONG, AddRef  ) ( THIS ) ;
STDMETHOD_ ( ULONG, Release ) ( THIS ) ;

STDMETHOD  ( CreateInstance ) ( THIS_ LPUNKNOWN pUnkOuter, REFIID riid, LPVOID FAR* ppvObject ) ;
STDMETHOD  ( LockServer ) ( THIS_ BOOL ) ;

// public:

 ExampleClassFactory () ;
~ExampleClassFactory () ;

ULONG cECFREFcounter ;

} ; // Declared ExampleClassFactory.

#undef INTERFACE




#undef INTERFACE
#define INTERFACE IExampleClass

DECLARE_INTERFACE_ ( IExampleClass, IUnknown ) {

STDMETHOD  ( ExampleMethod  ) ( THIS ) PURE ;

} ; // Declared IExampleClass.

#undef INTERFACE




#undef INTERFACE
#define INTERFACE ExampleClass

// DECLARE_INTERFACE_ ( ExampleClass, IExampleClass ) {

class ExampleClass : public IExampleClass {

public:

STDMETHOD  ( QueryInterface ) ( THIS_ REFIID riid, LPVOID FAR* ppv ) ;
STDMETHOD_ ( ULONG, AddRef  ) ( THIS ) ;
STDMETHOD_ ( ULONG, Release ) ( THIS ) ;

STDMETHOD  ( ExampleMethod  ) ( THIS ) ;

 ExampleClass () ;
~ExampleClass () ;

ULONG cECREFcounter ;

} ; // Declared ExampleClass.

#undef INTERFACE
