
#include "stdafx.h"
#include "api.h"
#include "..\common\INet.h"

INet * LoadNetFromModule(const TCHAR* fileName)
{
	CString fullPath;
	PrefixAppDir(fileName, fullPath);

	HMODULE dllModule = LoadLibrary(fullPath);

	if (!dllModule)
		return 0;

	FARPROC netInstanceProc = GetProcAddress(dllModule, "NetInstance");

	if (!netInstanceProc)
		return 0;

	INet * net = (INet*) netInstanceProc();

	return net;
}

void GetAppName(TCHAR * szName)
{
	TCHAR szModuleFileName[MAX_PATH];
	if(!GetModuleFileName(NULL, szModuleFileName, MAX_PATH))
		return;
	TCHAR* p = _tcsrchr(szModuleFileName, _T('\\'));
	if(!p)
		return;
	
	int nLen = _tcslen(szModuleFileName) - 5 - (p - szModuleFileName);
	_tcsncpy(szName, p + 1,  nLen);	

	szName[nLen] = 0;
}

bool GetAppDirectory(TCHAR * szDir)
{
	TCHAR szApp[MAX_PATH] = _T("");
	if(!GetModuleFileName(NULL, szApp, MAX_PATH))
		return false;
	
	GetFilePath(szApp, szDir);
	
	return RemoveLastSlash(szDir);
}

bool GetFilePath(const TCHAR* szFile, TCHAR* szPath)
{
	*szPath = 0;

	if (!szFile)
		return false;

	/** find the last "/" */
	int iLen = lstrlen(szFile);

	for (int i = iLen - 1; i > -1; i -- )
	{
		if ( '\\' == szFile[i])
		/** we found the end-pos of the path. */
			break;
	}

	if ( 0 > i )
		return false;

	_tcsncpy(szPath, szFile, i);
	szPath[i] = 0;

	/** "F:\" is return as "F:", last slash is never returned. */
	return true;
}

bool GetFileName(const TCHAR* fullPath, CString& fileName)
{
	if( !fullPath || !_tcslen(fullPath) )
		return false;

	fileName = fullPath;

	int lastSlash1  = fileName.ReverseFind(_T('\\'));
	int lastSlash2  = fileName.ReverseFind(_T('/'));
	
	int lastSlash = max(lastSlash1, lastSlash2);

	if (lastSlash > -1)
		fileName = fileName.Mid(lastSlash + 1);

	return true;
}

bool RemoveLastSlash(TCHAR* szDir)
{
	if (0 == szDir || 0 == *szDir)
		return false;

	int iSize = lstrlen(szDir);

	if ('\\' == szDir[iSize -1])
	{
		szDir[iSize -1] = 0;
	}

	return true;
}

void PrefixAppDir(const TCHAR* path, CString& fullPath)
{
	TCHAR appDir[MAX_PATH] = _T("");
	GetAppDirectory(appDir);
	RemoveLastSlash(appDir);
	fullPath.Format(_T("%s\\%s"), appDir, path);
}

void Log(const TCHAR* buffer)
{	
	CString time = CTime::GetCurrentTime().Format("%Y-%m-%d %H:%M:%S");

	CString file;
	TCHAR szBuf[MAX_PATH] = _T("");
	GetAppName(szBuf);
	file = szBuf;

	CString logFile =  file + _T(".log");
	CString fullPathFile;
	PrefixAppDir(logFile, fullPathFile);

	FILE *fp=_tfopen(fullPathFile,_T("a+"));
	_ftprintf(fp,_T("[%s] %s\n"), time, buffer);
	fclose(fp);
}

