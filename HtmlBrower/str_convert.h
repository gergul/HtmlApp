#ifndef _str_convert_
#define _str_convert_

int UnicodeToUtf8Len(const wchar_t *in);
int UnicodeToUtf8( char *out, int outSize, const wchar_t *in );

int Utf8ToUnicodeLen(const char *in);
int Utf8ToUnicode( wchar_t *out, int outSize, const char *in );

int UnicodeToAnsiLen( const wchar_t *in );
int UnicodeToAnsi( char *out, int outSize, const wchar_t *in );

int AnsiToUnicodeLen( const char *in );
int AnsiToUnicode( wchar_t *out, int outSize, const char *in );


void AnsiToUtf8( char **out, const char *in );
void Utf8ToAnsi( char **out, const char *in );

typedef struct JSTR_BUFFER
{
	int nALen;
	char *pABuffer;
	int nWLen;
	wchar_t *pWBuffer;
} JSTR_BUFFER;
JSTR_BUFFER *InitHelperBuffer(int capacity);
const char *AnsiToUtf8Helper(JSTR_BUFFER *jb, const char *in);
const char *Utf8ToAnsiHelper(JSTR_BUFFER *jb, const char *in);
void FreeHelperBuffer(JSTR_BUFFER *jb);

#endif