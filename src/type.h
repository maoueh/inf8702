#ifndef TYPE
#define TYPE

//#define BOOL  bool
#define FLOAT float
#define INT   int

//#define TRUE  true
//#define FALSE true
//#define NULL  0

#define MATCH 0

// Text definitions
#ifdef _UNICODE

	#define	CHAR		wchar_t
	#define	STRING		wstring
	#define TXT(txt)    L ## txt

    #define vsprintf_s  vswprintf_s

#else

	#define	CHAR		char
	#define	STRING		string
	#define TXT(txt)	txt
    
    #define vsprintf_s  vsprintf_s

#endif

#endif