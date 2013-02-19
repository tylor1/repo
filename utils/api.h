/**********************************************************************
 * 工程名:	DrvExam
 * 文件名:	api.h
 * 版本号:	1.0
 * 功能:	
 * 作者:	
 * 创建日期:	2012-03-29
 * 版权所有 (C) 2011 重庆奥彬科技有限公司
 *********************************************************************/

class INet;

/**********************************************************************
 * 说明: 从动态库加载网络模块
 **********************************************************************/
INet * LoadNetFromModule(const TCHAR* fileName);

void GetAppName(TCHAR * szName);
bool GetAppDirectory(TCHAR* szDir);
bool GetFilePath(const TCHAR* szFile, TCHAR* szPath);
bool GetFileName(const TCHAR* fullPath, CString& fileName);

bool RemoveLastSlash(TCHAR* szDir);
void PrefixAppDir(const TCHAR* path, CString& fullPath);

void Log(const TCHAR* buffer);
