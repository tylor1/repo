#include "stdafx.h"
#include "iniaccessor.h"
#include "..\utils\api.h"

#define MAX_BUF 2048
#define MAX_ALLSECTIONS 2048 //ȫ���Ķ��� 
#define MAX_SECTION 260 //һ���������� 
#define MAX_ALLKEYS 6000 //ȫ���ļ��� 
#define MAX_KEY 260 //һ���������� 


CINIAccessor::CINIAccessor()
{
	TCHAR szBuf[MAX_PATH] = _T("");
	GetAppName(szBuf);
	m_sAppName = szBuf;

	CString iniFile =  m_sAppName + _T(".ini");
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

int CINIAccessor::GetKeyValues(CStringArray& arrKey,CStringArray& arrValue, LPCTSTR lpSection) 
{ 
	int i;  
	int iPos=0; 
	CString strKeyValue; 
	int iMaxCount; 
	TCHAR chKeyNames[MAX_ALLKEYS]={0};	// �ܵ���������ַ��� 
	TCHAR chKey[MAX_KEY]={0};	// �������һ������ 
	
	GetPrivateProfileSection(lpSection,chKeyNames,MAX_ALLKEYS,m_sIniFile); 
	
	for(i=0;i<MAX_ALLKEYS;i++) 
	{ 
		if (chKeyNames[i]==0) 
			if (chKeyNames[i]==chKeyNames[i+1]) 
				break; 
	} 
	
	iMaxCount=i+1;	// Ҫ��һ��0��Ԫ�ء����ҳ�ȫ���ַ����Ľ������֡� 
	arrKey.RemoveAll();	// ���ԭ���� 
	arrValue.RemoveAll(); 
	
	for(i=0;i<iMaxCount;i++) 
	{ 
		chKey[iPos++]=chKeyNames[i]; 
		if(chKeyNames[i]==0) 
		{ 
			strKeyValue=chKey; 
			arrKey.Add(strKeyValue.Left(strKeyValue.Find("="))); 
			arrValue.Add(strKeyValue.Mid(strKeyValue.Find("=")+1)); 
			memset(chKey,0,MAX_KEY); 
			iPos=0; 
		} 
		
	} 

	return (int)arrKey.GetSize(); 
} 

