#ifndef INIACCESSOR_H
#define INIACCESSOR_H


#include <afxtempl.h>

class CINIAccessor
{
public:
	CINIAccessor();
	~CINIAccessor();

	bool WriteString(LPCTSTR szSection, LPCTSTR szKey, LPCTSTR szValue);
	CString& GetString(LPCTSTR szSection, LPCTSTR szKey, LPCTSTR szDefault);

	bool WriteInt(LPCTSTR szSection, LPCTSTR szKey, int  iValue);
	int  GetInt(LPCTSTR szSection, LPCTSTR szKey, int iDefault);

	int GetKeyValues(CStringArray& arrKey,CStringArray& arrValue, LPCTSTR lpSection);
protected:

	CString m_sAppName;

	CString m_sIniFile;

	CMap<CString, LPCTSTR, CString, CString&> m_strmap;
};

#endif