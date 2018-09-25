#include<Windows.h>
#include "str_convert.h"


int UnicodeToUtf8Len(const wchar_t *in)
{
	return WideCharToMultiByte(CP_UTF8, 0, (LPCWSTR)in, -1, NULL, 0, NULL, NULL);
}


int UnicodeToUtf8( char *out, int outSize, const wchar_t *in )
{
	out[outSize - 1] = '\0';
	return WideCharToMultiByte(CP_UTF8, 0, (LPCWSTR)in, -1, (LPSTR)out, outSize, NULL, NULL);
}

int Utf8ToUnicodeLen(const char *in)
{
	return MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)in, -1, NULL, 0);
}

int Utf8ToUnicode( wchar_t *out, int outSize, const char *in )
{
	out[outSize - 1] = '\0';
	return MultiByteToWideChar(CP_UTF8, 0, (LPCSTR)in, -1, (LPWSTR)out, outSize);
}

int UnicodeToAnsiLen(const wchar_t *in)
{
	return WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)in, -1, NULL, 0, NULL, NULL);
}

int UnicodeToAnsi( char *out, int outSize, const wchar_t *in )
{
	//int nAnsiLen = WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)in, -1, NULL, 0, NULL, NULL);
	//char *pAnsiBuffer = (char *)malloc(nAnsiLen*sizeof(char));
	out[outSize - 1] = '\0';
	return WideCharToMultiByte(CP_ACP, 0, (LPCWSTR)in, -1, (LPSTR)out, outSize, NULL, NULL);
}

int AnsiToUnicodeLen(const char *in)
{
	return MultiByteToWideChar(CP_ACP, 0, (LPCSTR)in, -1, NULL, 0);
}

int AnsiToUnicode( wchar_t *out, int outSize, const char *in )
{
	//int nUnicodeLen = MultiByteToWideChar(CP_ACP, 0, (LPCSTR)in, -1, NULL, 0);
	//wchar_t *pUnicodeBuffer = (wchar_t *)malloc(nUnicodeLen*sizeof(wchar_t));
	out[outSize - 1] = '\0';
	return MultiByteToWideChar(CP_ACP, 0, (LPCSTR)in, -1, (LPWSTR)out, outSize);
}



void AnsiToUtf8( char **out, const char *in )
{
	int size = AnsiToUnicodeLen(in);
	wchar_t *w = (wchar_t *)malloc(size * sizeof(wchar_t));
	if (AnsiToUnicode(w, size, in) > 0)
	{
		size = UnicodeToUtf8Len(w);
		*out = (char *)malloc(size);
		size = UnicodeToUtf8(*out, size, w);
	}
	free(w);
}

void Utf8ToAnsi( char **out, const char *in )
{
	int size = Utf8ToUnicodeLen(in);
	wchar_t *w = (wchar_t *)malloc(size * sizeof(wchar_t));
	if (Utf8ToUnicode(w, size, in))
	{
		size = UnicodeToAnsiLen(w);
		*out = (char *)malloc(size);
		size = UnicodeToAnsi(*out, size, w);
	}
	free(w);
}

JSTR_BUFFER *InitHelperBuffer(int capacity)
{
	JSTR_BUFFER *jb = (JSTR_BUFFER *)malloc(sizeof(JSTR_BUFFER));
	memset(jb, 0, sizeof(JSTR_BUFFER));
	if (capacity != 0)
	{
		jb->nALen = capacity;
		jb->nWLen = capacity;
		jb->pABuffer = (char *)malloc(jb->nALen);
		jb->pWBuffer = (wchar_t *)malloc(jb->nWLen * sizeof(wchar_t));
	}

	return jb;
}

const char * AnsiToUtf8Helper(JSTR_BUFFER *jb, const char *in)
{
	int wsize = AnsiToUnicodeLen(in);
	int asize;

	if (jb->pWBuffer == NULL)
	{//Î´ÉêÇë
		jb->nWLen = wsize;
		jb->pWBuffer = (wchar_t *)malloc(jb->nWLen * sizeof(wchar_t));
	}
	else if (wsize > jb->nWLen)
	{//²»¹»³¤
		jb->nWLen = wsize;
		jb->pWBuffer = (wchar_t *)realloc(jb->pWBuffer, jb->nWLen);
	}
	wsize = AnsiToUnicode(jb->pWBuffer, wsize, in);

	asize = UnicodeToUtf8Len(jb->pWBuffer);
	if (jb->pABuffer == NULL)
	{//Î´ÉêÇë
		jb->nALen = asize;
		jb->pABuffer = (char *)malloc(jb->nALen);
	}
	else if (asize > jb->nALen)
	{//²»¹»³¤
		jb->nALen = asize;
		jb->pABuffer = (char *)realloc(jb->pABuffer, jb->nALen);
	}
	asize = UnicodeToUtf8(jb->pABuffer, asize, jb->pWBuffer);

	return jb->pABuffer;
}

const char * Utf8ToAnsiHelper(JSTR_BUFFER *jb, const char *in)
{
	int wsize = Utf8ToUnicodeLen(in);
	int asize;

	if (jb->pWBuffer == NULL)
	{//Î´ÉêÇë
		jb->nWLen = wsize;
		jb->pWBuffer = (wchar_t *)malloc(jb->nWLen * sizeof(wchar_t));
	}
	else if (wsize > jb->nWLen)
	{//²»¹»³¤
		jb->nWLen = wsize;
		jb->pWBuffer = (wchar_t *)realloc(jb->pWBuffer, jb->nWLen);
	}
	wsize = Utf8ToUnicode(jb->pWBuffer, wsize, in);

	asize = UnicodeToAnsiLen(jb->pWBuffer);
	if (jb->pABuffer == NULL)
	{//Î´ÉêÇë
		jb->nALen = asize;
		jb->pABuffer = (char *)malloc(jb->nALen);
	}
	else if (asize > jb->nALen)
	{//²»¹»³¤
		jb->nALen = asize;
		jb->pABuffer = (char *)realloc(jb->pABuffer, jb->nALen);
	}
	asize = UnicodeToAnsi(jb->pABuffer, asize, jb->pWBuffer);

	return jb->pABuffer;
}

void FreeHelperBuffer(JSTR_BUFFER *jb)
{
	if (NULL != jb->pABuffer)
	{
		free(jb->pABuffer);
		jb->pABuffer = NULL;
		jb->nALen = 0;
	}

	if (NULL != jb->pWBuffer)
	{
		free(jb->pWBuffer);
		jb->pWBuffer = NULL;
		jb->nWLen = 0;
	}
}

