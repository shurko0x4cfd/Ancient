
#ifdef QWCDLL_EXPORTS
#define QWCDLL_API __declspec(dllexport)
#else
#define QWCDLL_API __declspec(dllimport)
#endif

