#include "stdafx.h"
#include "iniaccessor.h"
#include "..\utils\api.h"

#define MAX_BUF 2048

CINIAccessor::CINIAccessor()
{
	TCHAR szBuf[MAX_PATH] = _T("");
	GetAppName(szBuf);
	m_sAppName = szBuf;

	CString iniFile = CString("Config\\") + m_sAppName + _T(".ini");
	CString fullPath;
	PrefixAppDir(iniFile, fullPath);
	m_sIniFile = fullPath;
}

CINIAccessor::~CINIAccessor()
{
}

bool CINIAccessor::WriteString(LPCTSTR szSection, LPCTSTR szKey, LPCTSTR szValue)
{
	m_strmap[szKey] = szValue;
	return TRUE == WritePrivateProfileString(szSection, szKey, szValue, m_sIniFile);
}

CString& CINIAccessor::GetString(LPCTSTR szSection, LPCTSTR szKey, LPCTSTR szDefault)
{
	TCHAR szBuf[MAX_BUF] = _T("");
	int iSize = GetPrivateProfileString(szSection, szKey, szDefault, szBuf, MAX_BUF, m_sIniFile);
	szBuf[iSize] = 0;

	m_strmap[szKey] = CString(szBuf);
	
	return m_strmap[szKey];
}

bool CINIAccessor::WriteInt(LPCTSTR szSection, LPCTSTR szName, int iValue)
{
	TCHAR szT[16];
	_stprintf(szT, _T("%d"), iValue);
	
	return TRUE == WritePrivateProfileString(szSection, szName, szT, m_sIniFile);
}

int CINIAccessor::GetInt(LPCTSTR szSection, LPCTSTR szName, int iDefault)
{
	return GetPrivateProfileInt(szSection, szName, iDefault, m_sIniFile);
}

