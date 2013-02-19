/**********************************************************************
 * ������:	DrvExam
 * �ļ���:	api.h
 * �汾��:	1.0
 * ����:	
 * ����:	
 * ��������:	2012-03-29
 * ��Ȩ���� (C) 2011 ����±�Ƽ����޹�˾
 *********************************************************************/

class INet;

/**********************************************************************
 * ˵��: �Ӷ�̬���������ģ��
 **********************************************************************/
INet * LoadNetFromModule(const TCHAR* fileName);

void GetAppName(TCHAR * szName);
bool GetAppDirectory(TCHAR* szDir);
bool GetFilePath(const TCHAR* szFile, TCHAR* szPath);
bool GetFileName(const TCHAR* fullPath, CString& fileName);

bool RemoveLastSlash(TCHAR* szDir);
void PrefixAppDir(const TCHAR* path, CString& fullPath);

void Log(const TCHAR* buffer);
