/**********************************************************************
 * ������:	DrvExam
 * �ļ���:	common.h
 * �汾��:	1.0
 * ����:	
 * ����:	
 * ��������:	2012-03-26
 * ��Ȩ���� (C) 2011 ����±�Ƽ����޹�˾
 *********************************************************************/

#ifndef COMMON_H
#define COMMON_H

#if !defined NOIMPORT
	#ifdef DEVELOPER
		#define IMPORT __declspec(dllexport)
	#else
		#define IMPORT __declspec(dllimport)
	#endif
#else
	#define IMPORT
#endif

/**********************************************************************
 * ˵��: ����
 **********************************************************************/
const int KNetRetryTime	= 3;

const TCHAR KDBServer[]	= _T("dbsvr");
const TCHAR KControlServer[]	= _T("controlsvr");


/**********************************************************************
 * ˵��: ��
 **********************************************************************/

#define SAFECALL(pointer, function)\
	if (0 != pointer)\
		pointer->function

#endif

